SET SERVEROUTPUT ON;
DECLARE
	num NUMBER;
	digit NUMBER;
	result NUMBER;
	temp NUMBER;
BEGIN
	num := 153;
	temp := num;
	result := 0;

	WHILE temp > 0 LOOP
		digit := MOD(temp, 10);
		result := result + (digit*digit*digit);
		temp := TRUNC(temp/10);
	END LOOP;

	IF num=result THEN
		DBMS_OUTPUT.PUT_LINE('Armstrong');
	ELSE 
		DBMS_OUTPUT.PUT_LINE('Not Armstrong');
	END IF;
END;