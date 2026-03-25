SET SERVEROUTPUT ON;
DECLARE
	num NUMBER;
BEGIN
	num:=&num;

	IF num > 0 THEN
		DBMS_OUTPUT.PUT_LINE('Number is Positive');
	ELSIF num < 0 THEN
		DBMS_OUTPUT.PUT_LINE('Number is Negative');
	ELSE
		DBMS_OUTPUT.PUT_LINE('Number is 0');
	END IF;
END;