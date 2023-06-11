/*  Stephen Tambussi
    COEN280 - Spring 2023
    HW3 - Problem C
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

COLUMN AvailableProperties FORMAT 9999 JUSTIFY center HEADING 'Number of Properties Available'
COLUMN LeasedProperties FORMAT 9999 JUSTIFY center HEADING 'Number of Properties Leased'
COLUMN AvgRent FORMAT $99,999.99 JUSTIFY center HEADING 'Average Monthly Rent'

TTITLE CENTER 'StrawberryField Rental Management Inc.' SKIP LEFT 'Property Data as of ' &current_date SKIP 2

SPOOL avg_rent_output.txt

SELECT COUNT(CASE WHEN Status = 'available' THEN 1 END) AS AvailableProperties,
       COUNT(CASE WHEN Status = 'unavailable' THEN 1 END) AS LeasedProperties,
       AVG(MonthlyRent) AS AvgRent
FROM RentalProperty;

SET TERMOUT OFF
SET TRIMSPOOL ON
SET VERIFY OFF

SPOOL OFF