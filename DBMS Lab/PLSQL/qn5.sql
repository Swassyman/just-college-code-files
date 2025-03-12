SET SERVEROUTPUT ON;
DECLARE
	num NUMBER;
	rev NUMBER;
	digit NUMBER;
	temp NUMBER;
BEGIN
	FOR num IN 1..100 LOOP
		rev:=0;
		temp:=num;

		WHILE temp>0 LOOP
			digit := MOD(temp, 10);
			rev:= (rev*10) + digit;
			temp:= TRUNC(temp/10);
		END LOOP;

		IF num=rev THEN
			DBMS_OUTPUT.PUT_LINE(num);
		END IF;
	END LOOP;
END;
