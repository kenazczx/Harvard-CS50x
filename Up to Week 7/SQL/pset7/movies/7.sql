SELECT title, rating from movies JOIN ratings on movies.id = ratings.movie_id WHERE year = 2010 ORDER BY rating DESC, title ASC;

