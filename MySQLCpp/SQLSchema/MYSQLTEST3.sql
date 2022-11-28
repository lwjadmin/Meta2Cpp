USE SAKILA;

SELECT 
	*
FROM sakila.film
where 
	rental_duration > 4 and 
    rental_rate > 1.00 and 
    length <= 80 
order by film_id asc
limit 0,5;
    
SELECT SUM(length) FROM sakila.film;

select * from sakila.film
where description like '%tale%';

