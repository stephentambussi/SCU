/*  Stephen Tambussi
    COEN280 - Spring 2023
    HW2 - Question 1
*/

-- Completely reset/delete all tables and start from scratch
DROP TABLE Employee CASCADE CONSTRAINTS PURGE;
DROP TABLE Department CASCADE CONSTRAINTS PURGE;
DROP TABLE DeptLocations CASCADE CONSTRAINTS PURGE;
DROP TABLE Project CASCADE CONSTRAINTS PURGE;
DROP TABLE Works_On CASCADE CONSTRAINTS PURGE;

CREATE TABLE Employee
(
    EmpName varchar2(30),
    SSN INTEGER PRIMARY KEY,
    PhoneNo INTEGER NOT NULL UNIQUE,
    Salary INTEGER CHECK(Salary > 0),
    DNO INTEGER,
    SupervisorSSN INTEGER REFERENCES Employee(SSN)
);

CREATE TABLE Department
(
    DeptName varchar2(30),
    DeptNo INTEGER PRIMARY KEY,
    ManagerSSN INTEGER REFERENCES Employee(SSN)
);

-- Moved to hw2_q2.sql to make it easier to add tuples to the tables
-- ALTER TABLE Employee ADD CONSTRAINT dno_foreignKey FOREIGN KEY (DNO) REFERENCES Department(DeptNo);

CREATE TABLE DeptLocations
(
    DeptNumber INTEGER REFERENCES Department(DeptNo),
    location varchar2(30),
    PRIMARY KEY(DeptNumber, location)
);

CREATE TABLE Project
(
    ProjectName varchar2(30),
    ProjNumber INTEGER PRIMARY KEY,
    location varchar2(30),
    DeptNum INTEGER REFERENCES Department(DeptNo)
);

CREATE TABLE Works_On
(
    EmpSSN INTEGER REFERENCES Employee(SSN),
    ProjNumber INTEGER REFERENCES Project(ProjNumber),
    start_date date,
    Hours INTEGER
);
