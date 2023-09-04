-- INSERT INTO admins VALUES(
--     6, "kakakak123", 094
-- );

-- INSERT INTO employees VALUES(
--     9, 091, "maipanyakkhun"
-- );

-- INSERT INTO person(full_name, email, dob) VALUES(
--     "ashmal tatta", "tatta@gmail.com", "2001-10-19"
-- );

-- INSERT INTO departments VALUES(
--     091, 0
-- );
-- UPDATE departments SET num_of_emps=1 WHERE d_id=91 -

-
-- SELECT QUERIES --
SELECT full_name, pass_word 
FROM person, admins 
WHERE admins.id=person.id;

SELECT id, departments.d_id, num_of_emps
FROM departments, admins
WHERE admins.d_id=departments.d_id;

-- JOIN QUERIES --
SELECT admins.id, full_name, email, pass_word FROM admins
INNER JOIN person
ON admins.id=person.id;

SELECT admins.id, departments.d_id, num_of_emps
FROM admins INNER JOIN departments
ON departments.d_id=admins.d_id;

-- AGGREGATION --
SELECT id, full_name, COUNT(id)
FROM person
GROUP BY id;

-- GROUP BY/HAVING CLAUSE
SELECT COUNT(d_id), num_of_emps
FROM departments
GROUP BY num_of_emps
HAVING num_of_emps>1;


