SELECT title, ratings.rating FROM movies
INER JOIN ratings ON (id = ratings.movie_id)
WHERE year = 2010 ORDER BY ratings.rating DESC, title;