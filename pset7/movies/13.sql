SELECT DISTINCT(name) FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE movies.id IN (SELECT movies.id FROM people
JOIN stars ON people.id = stars.person_id
JOIN movies ON stars.movie_id = movies.id
WHERE name = 'Kevin Bacon' AND birth = '1958') AND name != 'Kevin Bacon'
ORDER BY title;


