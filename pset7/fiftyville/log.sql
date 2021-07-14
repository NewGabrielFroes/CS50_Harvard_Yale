-- Keep a log of any SQL queries you execute as you solve the mystery.
SELECT description, id FROM crime_scene_reports
WHERE day = 28 AND month = 7 AND street = 'Chamberlin Street';

SELECT activity, license_plate, id, hour, minute FROM courthouse_security_logs
WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10;

SELECT * FROM phone_calls WHERE year = 2020 AND month = 7 AND day = 28;

SELECT * FROM passengers WHERE flight_id = 36;

SELECT * FROM atm_transactions
WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = 'Fifer Street';

SELECT * FROM flights WHERE year = 2020 AND month = 7 AND day = 29;

SELECT * FROM airports WHERE id = 8 AND id = 4;

SELECT * people WHERE license_plate = '94KL13X';