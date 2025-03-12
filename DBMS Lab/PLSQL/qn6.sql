SET SERVEROUTPUT ON;
DECLARE 
	year NUMBER;
BEGIN
	year:=&year;

	IF MOD(year, 4)=0 AND MOD(year, 100)<>0 THEN
		DBMS_OUTPUT.PUT_LINE('Year is Leap Year');
	ELSIF MOD(year, 400)=0 THEN
		DBMS_OUTPUT.PUT_LINE('Year is Leap Year');
	ELSE
		DBMS_OUTPUT.PUT_LINE('Year is NOT Leap Year');
	END IF;
END;