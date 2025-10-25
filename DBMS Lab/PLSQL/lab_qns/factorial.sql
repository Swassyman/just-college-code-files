SET SERVEROUTPUT ON;

CREATE OR REPLACE PROCEDURE FINDFACTORIAL(N IN NUMBER) AS
    fact NUMBER := 1;
    temp NUMBER := N;
BEGIN
    WHILE temp > 0 LOOP
        fact := fact * temp;
        temp := temp - 1;
    END LOOP;

    DBMS_OUTPUT.PUT_LINE(fact || ' is factorial');
END;
/

BEGIN
  FINDFACTORIAL(5);
END;
/