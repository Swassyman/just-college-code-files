SET SERVEROUTPUT ON;
DECLARE
	num NUMBER;
	counter NUMBER := 1;
BEGIN
	num := &num;

	while counter<=num LOOP
		DBMS_OUTPUT.PUT_LINE('Count: '|| counter);
		counter:= counter + 1;
	END LOOP;
END;