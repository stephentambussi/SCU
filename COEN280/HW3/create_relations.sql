/*  Stephen Tambussi
    COEN280 - Spring 2023
    This program creates the tables for the StrawberryField's Rental
    Management System from the ER diagrams.
*/

-- FOR TESTING: completely reset/delete all tables and start from scratch
DROP TABLE Branch CASCADE CONSTRAINTS PURGE;
DROP TABLE Manager CASCADE CONSTRAINTS PURGE;
DROP TABLE Supervisor CASCADE CONSTRAINTS PURGE;
DROP TABLE Staff CASCADE CONSTRAINTS PURGE;
DROP TABLE PropertyOwner CASCADE CONSTRAINTS PURGE;
DROP TABLE RentalProperty CASCADE CONSTRAINTS PURGE;
DROP TABLE LeaseAgreement CASCADE CONSTRAINTS PURGE;

/*  Scratch Work

    <name> = primary key
    *name* = foreign key

    Branch(<BranchNumber>, Phone, Street, City, ZipCode)

    -- JobDesignation is redundant
    Manager(<EmployeeID>, EmpName, Phone, StartDate, JobDesignation, *BranchNumber*)
    Supervisor(<EmployeeID>, EmpName, Phone, StartDate, JobDesignation, *BranchNumber*, *EmployeeID*)
    Staff(<EmployeeID>, EmpName, Phone, StartDate, JobDesignation, *BranchNumber*)

    -- Use trigger to only allow supervisor to manage 3 or less properties
    RentalProperty(<PropertyNumber>, Address(Composite), NumOfRooms, MonthlyRent, Status, DateAvailable, *SupervisorID*, *OwnerName*)

    PropertyOwner(<OwnerName>, PermanentAddress(Composite), PhoneNumber)

    LeaseAgreement(<PropertyNumber>, <RenterName>, LeaseStart, LeaseEnd, RenterHomePhone, 
                    RenterWorkPhone, DepositAmount
                    )

*/

CREATE TABLE Branch 
(
    BranchNumber INTEGER PRIMARY KEY,
    Phone INTEGER NOT NULL UNIQUE,
    Street varchar2(30),
    City varchar2(30),
    ZipCode INTEGER
);

CREATE TABLE Manager 
(
    EmployeeID INTEGER PRIMARY KEY,
    EmpName varchar(30),
    Phone INTEGER NOT NULL UNIQUE,
    StartDate date,
    JobDesignation varchar(30),
    BranchNumber INTEGER REFERENCES Branch(BranchNumber)
);

CREATE TABLE Supervisor 
(
    EmployeeID INTEGER PRIMARY KEY,
    EmpName varchar(30),
    Phone INTEGER NOT NULL UNIQUE,
    StartDate date,
    JobDesignation varchar(30),
    BranchNumber INTEGER REFERENCES Branch(BranchNumber),
    ManagerID INTEGER REFERENCES Manager(EmployeeID)
);

CREATE TABLE Staff 
(
    EmployeeID INTEGER PRIMARY KEY,
    EmpName varchar(30),
    Phone INTEGER NOT NULL UNIQUE,
    StartDate date,
    JobDesignation varchar(30),
    BranchNumber INTEGER REFERENCES Branch(BranchNumber)
);

CREATE TABLE PropertyOwner
(
    OwnerName varchar2(30) PRIMARY KEY,
    Street varchar2(30),
    City varchar2(30),
    ZipCode INTEGER,
    PhoneNumber INTEGER NOT NULL UNIQUE
);

/*  Constraints:
    - Supervisor can only manage 3 properties or less (use trigger)
    - With new lease, change Status to unavailable
    - With new lease, increase rent by 10% (20% if only 6 months)
*/
CREATE TABLE RentalProperty
(
    PropertyNumber INTEGER PRIMARY KEY,
    Street varchar2(30),
    City varchar2(30),
    ZipCode INTEGER,
    NumOfRooms INTEGER,
    MonthlyRent INTEGER,
    Status varchar2(30),
    DateAvailable date,
    SupervisorID INTEGER REFERENCES Supervisor(EmployeeID),
    OwnerName varchar2(30) REFERENCES PropertyOwner(OwnerName)
);

/*  Constraints:
    - lease should be >= 6 months and <= 12 months 
    - 6 month lease = 10% increase in rent
*/
CREATE TABLE LeaseAgreement
(
    PropertyNumber INTEGER REFERENCES RentalProperty(PropertyNumber),
    RenterName varchar2(30),
    LeaseStart date,
    LeaseEnd date, 
    RenterHomePhone INTEGER,
    RenterWorkPhone INTEGER,
    DepositAmount INTEGER,
    PRIMARY KEY (PropertyNumber, RenterName),
    CONSTRAINT lease_duration CHECK(
        MONTHS_BETWEEN(LeaseEnd, LeaseStart) >= 6 
        and MONTHS_BETWEEN(LeaseEnd, LeaseStart) <= 12
        )
);

-- Supervisor property constraint
-- TODO: resolve this, make a constraint?
-- CREATE TRIGGER Supervisor_PropertyLimit
--     BEFORE INSERT OR UPDATE ON RentalProperty
--     FOR EACH ROW
--     DECLARE
--         m_count INTEGER;
--     BEGIN
--         SELECT COUNT(*)
--         INTO m_count
--         FROM RentalProperty
--         WHERE SupervisorID = :New.SupervisorID;
--         IF (m_count > 3)
--         THEN
--             raise_application_error(-20001, 'Supervisor can only manage 3 or less properties');
--         END IF;
--     END;
-- /
-- New Lease, RentalProperty update
CREATE TRIGGER PropertyStatus_Update
    AFTER INSERT ON LeaseAgreement
    FOR EACH ROW
    BEGIN
        UPDATE RentalProperty
        SET Status = 'unavailable'
        WHERE PropertyNumber = :New.PropertyNumber;
    END;
/

-- Rent increase trigger
CREATE OR REPLACE TRIGGER update_rentalproperty_rent
    AFTER INSERT ON LeaseAgreement
    FOR EACH ROW
    DECLARE
        v_rent_increase NUMBER;
    BEGIN
        SELECT MonthlyRent * 0.1
        INTO v_rent_increase
        FROM RentalProperty
        WHERE PropertyNumber = :New.PropertyNumber;

        UPDATE RentalProperty
        SET MonthlyRent = MonthlyRent + v_rent_increase
        WHERE PropertyNumber = :New.PropertyNumber;

        IF MONTHS_BETWEEN(:New.LeaseEnd, :New.LeaseStart) = 6 THEN
            UPDATE RentalProperty
            SET MonthlyRent = MonthlyRent + v_rent_increase
            WHERE PropertyNumber = :New.PropertyNumber;
        END IF;
    END;
/