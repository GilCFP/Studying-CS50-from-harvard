SELECT title FROM movies
WHERE id IN
(SELECT DISTINCT movie_id FROM stars WHERE
(movie_id IN (SELECT movie_id FROM (SELECT movie_id FROM stars WHERE person_id IN(SELECT id FROM people WHERE name LIKE "Johnny Depp")))
AND
person_id IN(SELECT id FROM people WHERE name LIKE "Helena Bonham Carter" )))