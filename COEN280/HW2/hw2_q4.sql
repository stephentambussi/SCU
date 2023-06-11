/*  Stephen Tambussi
    COEN280 - Spring 2023
    HW2 - Question 4
*/

-- Show the tables to be used for this query
SELECT * FROM Employee;
SELECT * FROM Department;
SELECT * FROM Project;

SELECT p.ProjNumber, p.ProjectName, p.DeptNum, e.EmpName AS ManagerName, e.PhoneNo
FROM Project p
INNER JOIN Department d ON p.DeptNum = d.DeptNo
INNER JOIN Employee e ON d.ManagerSSN = e.SSN
WHERE p.location = 'Santa Clara';
