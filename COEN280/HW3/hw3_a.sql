/*  Stephen Tambussi
    COEN280 - Spring 2023
    HW3 - Problem A
*/

-- Clear everything
CLEAR SCREEN
CLEAR BREAKS 
CLEAR COLUMNS

ACCEPT propertyNum NUMBER FORMAT '9999' PROMPT 'Enter Rental Property Number: '

ACCEPT renterName CHAR FORMAT 'A20' PROMPT 'Enter your name: '

-- the size of one page
SET PAGESIZE 14
-- the size of a line
SET LINESIZE 150

SET HEADING ON

COLUMN PropertyNumber FORMAT 9999 JUSTIFY center HEADING 'Property Number'
COLUMN Address FORMAT A30 JUSTIFY center HEADING 'Address' WORD_WRAP
COLUMN RenterName FORMAT A20 JUSTIFY center HEADING 'Renter Name' WORD_WRAP
COLUMN RenterHomePhone FORMAT A11 JUSTIFY center HEADING 'Home Phone'
COLUMN RenterWorkPhone FORMAT A11 JUSTIFY center HEADING 'Work Phone'
COLUMN LeaseStart FORMAT A12 JUSTIFY center HEADING 'Start Date'
COLUMN LeaseEnd FORMAT A12 JUSTIFY center HEADING 'End Date'
COLUMN MonthlyRent FORMAT $99,999.99 JUSTIFY center HEADING 'Monthly Rent'
COLUMN DepositAmount FORMAT $99,999.99 JUSTIFY center HEADING 'Deposit Amount'

TTITLE CENTER 'Lease Agreement for ' &renterName SKIP 2

BTITLE CENTER 'StrawberryField Rental Management Inc.'

SPOOL lease_agreement_output.txt

SELECT p.PropertyNumber, p.Street || ', ' || p.City || ', ' || p.ZipCode AS Address,
       l.RenterName, l.RenterHomePhone, l.RenterWorkPhone,
       TO_CHAR(l.LeaseStart, 'DD-MON-YYYY') AS LeaseStart,
       TO_CHAR(l.LeaseEnd, 'DD-MON-YYYY') AS LeaseEnd,
       p.MonthlyRent, l.DepositAmount
FROM LeaseAgreement l
JOIN RentalProperty p ON l.PropertyNumber = p.PropertyNumber
WHERE l.RenterName = '&renterName' and l.PropertyNumber = &propertyNum;

SET TERMOUT OFF
SET TRIMSPOOL ON
SET VERIFY OFF

SPOOL OFF