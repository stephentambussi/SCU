/*  Stephen Tambussi
    COEN280 - Spring 2023
    HW2 - Question 3
*/

-- Show the tables to be used for this query
SELECT * FROM Employee;
SELECT * FROM Department;

set define off;
SELECT e.EmpName, e.PhoneNo, s.EmpName AS SupervisorName
FROM Employee e
LEFT JOIN Employee s ON e.SupervisorSSN = s.SSN
INNER JOIN Department d ON e.DNO = d.DeptNo AND d.DeptName = 'R&D'
ORDER BY e.EmpName;
