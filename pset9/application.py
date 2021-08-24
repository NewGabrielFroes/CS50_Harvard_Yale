import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime, timezone, timedelta

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    purchases = db.execute("SELECT * FROM purchases WHERE user_id = ? GROUP BY quote", session["user_id"])
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
    total_cash_price = cash

    if not purchases:
        return render_template("index.html", cash=cash, total_cash_price=cash)
        
    repeat_purchases = db.execute(
        "SELECT quote, SUM(shares) FROM purchases WHERE quote in (SELECT quote FROM purchases GROUP BY quote HAVING Count(*) > 1) GROUP BY quote")
    repeat_quote = []

    for repeat_purchase in repeat_purchases:
        repeat_purchase["price"] = lookup(repeat_purchase["quote"])["price"]
        repeat_purchase["total"] = repeat_purchase["SUM(shares)"] * lookup(repeat_purchase["quote"])["price"]
        total_cash_price += repeat_purchase["total"]
        repeat_quote.append(repeat_purchase["quote"])

    for purchase in purchases:
        for repeat_purchase in repeat_purchases:
            if purchase["quote"] in repeat_purchase["quote"]:
                purchase["shares"] = repeat_purchase["SUM(shares)"]
                purchase["total"] = repeat_purchase["total"]
                purchase["price"] = repeat_purchase["price"]

    for purchase in purchases:
        if purchase["shares"] <= 0:
            purchases.remove(purchase)
            continue
        if purchase["quote"] not in repeat_quote:
            price_quote = lookup(purchase["quote"])["price"]
            total_cash_price += price_quote * purchase["shares"]
            purchase["price"] = price_quote
            purchase["total"] = price_quote * purchase["shares"]

    return render_template("index.html", purchases=purchases, cash=cash, total_cash_price=total_cash_price)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        quote = request.form.get("symbol")  # stonks
        shares = request.form.get("shares")  # shares 

        time_zone = timezone(timedelta(hours=-3))
        transacted = datetime.now().astimezone(time_zone).strftime("%Y-%m-%d %H:%M:%S")   # Fuso horaio são paulo

        if quote == None:
            return apology("missing symbol", 400)
        elif shares == None:
            return apology("missing shares", 400)

        if not shares.isdigit() or int(shares) <= 0:
            return apology("shares is not available", 400)

        result_quote = lookup(quote)

        if result_quote == None:
            return apology("invalid symbol", 400)

        cash_user = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]
        total = result_quote["price"] * float(shares)

        if cash_user < total:
            return apology("can't afford")

        cash_user = cash_user - total
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_user, session["user_id"])

        quote = quote.upper()

        db.execute("INSERT INTO purchases (user_id, quote, name, price, shares, total, transacted) VALUES(?, ?, ?, ?, ?, ?, ?)",
                   session["user_id"], quote, result_quote["name"], result_quote["price"], shares, total, transacted)
        flash("Bought!")
        return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    transactions = db.execute("SELECT quote, price, shares, transacted FROM purchases WHERE user_id = ?", session["user_id"])
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        quote = request.form.get("symbol")
        if not quote:
            return apology("missing symbol", 400)

        result_quote = lookup(quote)
        print(result_quote)

        if result_quote == None:
            return apology("invalid symbol", 400)

        result_quote["price"] = usd(result_quote["price"])
        return render_template("quote.html", quote=result_quote)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        if not request.form.get("username"):
            return apology("must provide username", 400)

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        if len(rows) != 0:
            return apology("your username is not available")

        if not request.form.get("password"):
            return apology("must provide password", 400)

        if not request.form.get("confirmation"):
            return apology("must provide password (again)", 400)

        if request.form.get("password") != request.form.get("confirmation"):
            return apology("your passwords do not match")

        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", request.form.get(
            "username"), generate_password_hash(request.form.get("password")))

        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        session["user_id"] = rows[0]["id"]
        flash("Registered!")
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    quotes_available = db.execute("SELECT quote FROM purchases GROUP BY quote")
    shares_available = db.execute(
        "SELECT quote, SUM(shares) FROM purchases WHERE quote in (SELECT quote FROM purchases GROUP BY quote HAVING Count(*) >= 1) GROUP BY quote")
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    if request.method == "POST":
        quote = request.form.get("symbol")
        shares = request.form.get("shares")
        transacted = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

        print(transacted)
        if not quote:
            return apology("missing symbol", 400)
        elif not shares:
            return apology("missing shares", 400)

        if not shares.isdigit() or int(shares) <= 0:
            return apology("shares is not available", 400)

        result_quote = lookup(quote)
        shares = int(shares)

        if result_quote == None:
            return apology("invalid symbol", 400)

        for share in shares_available:
            if quote == share["quote"]:
                if shares <= int(share["SUM(shares)"]):
                    shares = int(share["SUM(shares)"]) - (int(share["SUM(shares)"]) + shares)
                    total = result_quote["price"] * shares
                    cash = cash + (total*-1)
                    db.execute("INSERT INTO purchases (user_id, quote, name, price, shares, total, transacted) VALUES(?, ?, ?, ?, ?, ?, ?)",
                               session["user_id"], quote, result_quote["name"], result_quote["price"], shares, total, transacted)
                    db.execute("UPDATE users SET cash = ? WHERE id = ?", cash, session["user_id"])
                    flash("Sold!")
                    return redirect("/")
                else:
                    return apology("too many shares")

    else:
        for share in shares_available:
            if share["SUM(shares)"] <= 0:
                shares_available.remove(share)
                continue
        return render_template("sell.html", options=shares_available)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
