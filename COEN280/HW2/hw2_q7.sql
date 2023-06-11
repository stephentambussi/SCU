/*  Stephen Tambussi
    COEN280 - Spring 2023
    HW2 - Question 7
*/

-- Show the tables to be used for this query
SELECT * FROM Employee;
SELECT * FROM Works_On;

SELECT e.EmpName, SUM(w.Hours) AS TotalHours
FROM Employee e
INNER JOIN Works_On w ON e.SSN = w.EmpSSN
GROUP BY e.EmpName
ORDER BY TotalHours DESC
FETCH FIRST 1 ROW ONLY;
