/*  Stephen Tambussi
    COEN280 - Spring 2023
    This program inserts data for testing.
*/

INSERT INTO Branch VALUES(1, 5556661000, 'Washington', 'Santa Clara', 95050);

INSERT INTO Manager VALUES(123, 'Dan', 8005002000, '19-AUG-10', 'Manager', 1);

INSERT INTO Supervisor VALUES(234, 'Joe', 8005002001, '19-AUG-11', 'Supervisor', 1, 123);
INSERT INTO Supervisor VALUES(567, 'David', 8005002002, '19-JUN-11', 'Supervisor', 1, 123);

INSERT INTO PropertyOwner VALUES('Bill', 'Elm Street', 'Santa Clara', 95050, 8002005000);
INSERT INTO PropertyOwner VALUES('Tim', 'Elk Ave', 'San Jose', 95055, 8002005001);

INSERT INTO RentalProperty VALUES(10, '500 El Camino Real', 'Santa Clara', 95050,
                            2, 1000, 'available', '19-AUG-20', 234, 'Bill');
INSERT INTO RentalProperty VALUES(9, '100 Ocean Drive', 'Santa Cruz', 08053,
                            5, 5000, 'available', '19-AUG-22', 234, 'Bill');
INSERT INTO RentalProperty VALUES(8, '50 Westmont Street', 'Haddon Heights', 08030,
                            3, 2000, 'available', '15-DEC-23', 234, 'Bill');

INSERT INTO RentalProperty VALUES(7, '40 Westmont Street', 'Haddon Heights', 08030,
                            3, 2200, 'available', '17-DEC-23', 567, 'Tim');
INSERT INTO RentalProperty VALUES(6, '30 Westmont Street', 'Haddon Heights', 08030,
                            4, 3000, 'available', '20-DEC-23', 567, 'Tim');

INSERT INTO LeaseAgreement VALUES(10, 'Steve', '19-AUG-20', '19-JUN-21', 1111111111, 2222222222,
                            500);
INSERT INTO LeaseAgreement VALUES(9, 'Dylan', '1-DEC-22', '21-JUL-23', 1111111112, 2222222223,
                            600);