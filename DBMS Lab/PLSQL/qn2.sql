SET SERVEROUTPUT ON;

DECLARE
	num NUMBER;
BEGIN
	num:=&num;

	for i in 1..num LOOP
		DBMS_OUTPUT.PUT_LINE('Count: ' || i);
	END LOOP;
END;
