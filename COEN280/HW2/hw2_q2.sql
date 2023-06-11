/*  Stephen Tambussi
    COEN280 - Spring 2023
    HW2 - Question 2
*/

-- Insert 10 tuples into Employee and show result
INSERT INTO Employee VALUES('Steve', 100, 100, 300000, 5, 100);
INSERT INTO Employee VALUES('Kim', 95, 150, 250000, 5, 100);
INSERT INTO Employee VALUES('Brandon', 40, 800, 200000, 4, 100);
INSERT INTO Employee VALUES('Tim', 55, 950, 200000, 3, 40);
INSERT INTO Employee VALUES('Brett', 35, 300, 100000, 4, 40);
INSERT INTO Employee VALUES('Dave', 25, 500, 200000, 2, 100);
INSERT INTO Employee VALUES('Kevin', 50, 900, 150000, 3, 55);
INSERT INTO Employee VALUES('Jeff', 20, 450, 100000, 2, 25);
INSERT INTO Employee VALUES('Jack', 15, 250, 100000, 1, 20);
INSERT INTO Employee VALUES('Jim', 10, 200, 100000, 1, 15);

SELECT * FROM Employee;

-- Insert 5 tuples into Department and show result
set define off; -- allows & character to be used without prompting for input
INSERT INTO Department VALUES('Executive', 5, 100);
INSERT INTO Department VALUES('Marketing', 4, 40);
INSERT INTO Department VALUES('R&D', 3, 55);
INSERT INTO Department VALUES('Legal', 2, 25);
INSERT INTO Department VALUES('HR', 1, 15);

SELECT * FROM Department;

-- Add foreign key constraint to Employee table where DNO references DeptNo in Department table
ALTER TABLE Employee ADD CONSTRAINT dno_foreignKey FOREIGN KEY (DNO) REFERENCES Department(DeptNo);

-- Insert 6 tuples into DeptLocations and show result
INSERT INTO DeptLocations VALUES(5, 'Santa Clara');
INSERT INTO DeptLocations VALUES(4, 'San Diego');
INSERT INTO DeptLocations VALUES(3, 'Fremont');
INSERT INTO DeptLocations VALUES(3, 'Santa Clara');
INSERT INTO DeptLocations VALUES(2, 'San Jose');
INSERT INTO DeptLocations VALUES(1, 'Los Angeles');

SELECT * FROM DeptLocations;

-- Insert 5 tuples into Project and show result
INSERT INTO Project VALUES('Smartphone', 1, 'Fremont', 3);
INSERT INTO Project VALUES('Laptop', 2, 'Santa Clara', 3);
INSERT INTO Project VALUES('TV', 3, 'Santa Clara', 3);
INSERT INTO Project VALUES('Computer Chip', 4, 'Fremont', 3);
INSERT INTO Project VALUES('New Slogan', 5, 'San Diego', 4);

SELECT * FROM Project;

-- Insert 5 tuples into Works_On and show result
INSERT INTO Works_On VALUES(100, 1, '19-AUG-20', 50);
INSERT INTO Works_On VALUES(100, 5, '05-AUG-15', 50);
INSERT INTO Works_On VALUES(40, 5, '01-AUG-15', 60);
INSERT INTO Works_On VALUES(25, 4, '03-JUN-21', 40);
INSERT INTO Works_On VALUES(95, 3, '18-DEC-20', 45);

SELECT * FROM Works_On;