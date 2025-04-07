SET SERVEROUTPUT ON;

DECLARE
    lower_rad NUMBER;
    upper_rad NUMBER;
    diff NUMBER;
    area NUMBER;
    circumference NUMBER;
BEGIN
    lower_rad := &lower_rad;
    upper_rad := &upper_rad;
    diff := upper_rad - lower_rad;

    WHILE lower_rad <= upper_rad LOOP
        area := PI * lower_rad * lower_rad;
        circumference := 2 * PI * lower_rad;

        DBMS_OUTPUT.PUT_LINE('Radius: ' || lower_rad);
        DBMS_OUTPUT.PUT_LINE('Area: ' || area);
        DBMS_OUTPUT.PUT_LINE('Circumference: ' || circumference);
        DBMS_OUTPUT.PUT_LINE('----------------------------');
        
        lower_rad := lower_rad + 1;
    END LOOP;
END;
/
