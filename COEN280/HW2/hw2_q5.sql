/*  Stephen Tambussi
    COEN280 - Spring 2023
    HW2 - Question 5
*/

-- Show the tables to be used for this query
SELECT * FROM Department;
SELECT * FROM Employee;
SELECT * FROM DeptLocations;

SELECT d.DeptNo, d.DeptName, e.SSN, e.EmpName AS ManagerName
FROM Department d
INNER JOIN Employee e ON d.ManagerSSN = e.SSN
INNER JOIN DeptLocations dl ON d.DeptNo = dl.DeptNumber
GROUP BY d.DeptNo, d.DeptName, e.SSN, e.EmpName
HAVING COUNT(DISTINCT dl.location) > 1;