CREATE OR REPLACE FUNCTION ARMSTRONG(N IN NUMBER)
RETURN NUMBER IS
    digit NUMBER;
    temp NUMBER := N;
    result NUMBER := 0;
BEGIN
    WHILE temp > 0 LOOP
        digit := MOD(temp, 10);
        result := result + POWER(digit, 3);
        temp := TRUNC(temp / 10);
    END LOOP;

    RETURN result;
END;
/

SET SERVEROUTPUT ON;
DECLARE
    num NUMBER := 153;
    result NUMBER;
BEGIN
    result := ARMSTRONG(num);
    IF num = result THEN
        DBMS_OUTPUT.PUT_LINE('Armstrong');
    ELSE 
        DBMS_OUTPUT.PUT_LINE('Not Armstrong');
    END IF;
END;
/
