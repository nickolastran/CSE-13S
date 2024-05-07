# Creates the example output
echo "TOO MANY VALUES" >> expected.txt

# Runs the program
./calc 1 2 3 > output.txt 

# Ensures exit code is Zero
if [ $? -eq 0 ]; then
    echo "invalid exit code" $?
    rm output.txt
    rm expected.txt
    exit 1
fi

# Ensures differences *are* found
diff output.txt expected.txt
if [ $? -eq 0 ]; then
    echo "Inserted too many values!"
    rm output.txt
    rm expected.txt
    exit 1
fi

# Prints a message on success
echo "Test finds that puts 3 or more values: PASS"

# Cleans up files created
rm output.txt
rm expected.txt
exit 0
