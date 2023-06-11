/*  Stephen Tambussi
    COEN280 - Spring 2023
    HW2 - Question 6
*/

-- Show the tables to be used for this query
SELECT * FROM Project;
SELECT * FROM Works_On;

SELECT p.ProjectName, p.ProjNumber, p.location
FROM Project p
INNER JOIN Works_On w ON p.ProjNumber = w.ProjNumber
WHERE w.start_date = (
  SELECT MIN(start_date)
  FROM Works_On
);
