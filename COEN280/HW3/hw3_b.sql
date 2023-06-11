/*  Stephen Tambussi
    COEN280 - Spring 2023
    HW3 - Problem B
*/

-- Clear everything
CLEAR SCREEN
CLEAR BREAKS 
CLEAR COLUMNS

-- the size of one page
SET PAGESIZE 14
-- the size of a line
SET LINESIZE 150

SET HEADING ON

-- Get today's date and store into current_date variable as Char
COLUMN TODAY NEW_VALUE current_date 
SELECT TO_CHAR(SYSDATE, 'fmMonth DD, YYYY') TODAY
FROM DUAL;

COLUMN PropertyNumber FORMAT 9999 JUSTIFY center HEADING 'Property Number'
COLUMN RenterName FORMAT A20 JUSTIFY center HEADING 'Renter Name' WORD_WRAP
COLUMN Address FORMAT A30 JUSTIFY center HEADING 'Address' WORD_WRAP
COLUMN LeaseEnd FORMAT A12 JUSTIFY center HEADING 'End Date'

TTITLE CENTER 'Leases Expiring in 2 Months or Less' SKIP LEFT 'Current Date: ' &current_date SKIP 2

BTITLE CENTER 'StrawberryField Rental Management Inc.'

SPOOL expiring_leases_output.txt

SELECT p.PropertyNumber, p.Street || ', ' || p.City || ', ' || p.ZipCode AS Address,
       l.RenterName,
       TO_CHAR(l.LeaseEnd, 'DD-MON-YYYY') AS LeaseEnd
FROM LeaseAgreement l
JOIN RentalProperty p ON l.PropertyNumber = p.PropertyNumber
WHERE MONTHS_BETWEEN(SYSDATE, l.LeaseEnd) <= 2;

SET TERMOUT OFF
SET TRIMSPOOL ON
SET VERIFY OFF

SPOOL OFF