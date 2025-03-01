FILE="$1"
HASH_FILE="$FILE.hash"

if [ ! -f "$HASH_FILE" ]; then
    echo "Hash file not found, creating hash for $FILE."
    sha256sum "$FILE" > "$HASH_FILE"
    echo "Hash has been saved."
else
    echo "Checking integrity of $FILE..."
    current_hash=$(sha256sum "$FILE" | awk '{ print $1 }')
    saved_hash=$(awk '{ print $1 }' "$HASH_FILE")
    if [ "$current_hash" == "$saved_hash" ]; then
        echo "File integrity is intact. No changes detected."
    else
        echo "File has been modified! Integrity check failed."
    fi
fi
