SELECT title FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE name = 'Johnny Depp' OR name = 'Helena Bonham Carter'
GROUP BY title
HAVING COUNT(*) > 1;