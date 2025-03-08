lines=()

while read line; do
    lines+=("$line")
done < "$1"

for ((i=${#lines[@]}-1; i>=0; i--)); do
    words=()
    for word in ${lines[i]}; do
        words+=("$word")
    done
    for ((j=${#words[@]}-1; j>=0; j--)); do
        echo -n "${words[$j]} "
    done
    echo
done
