usertocheck="$1"

while true; do
    if who | grep -w "$usertocheck" > /dev/null; then
        echo "$usertocheck is logged in."
        exit 0  
    else
        echo "$usertocheck is not logged in. Checking again in 30 seconds..."
        sleep 30
    fi
done
