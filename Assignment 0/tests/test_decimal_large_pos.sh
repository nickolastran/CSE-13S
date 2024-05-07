# Creates the example output
echo "BAD INPUT" >> expected.txt

# Runs the program
./calc 513.5 5 > output.txt 

# Ensures exit code is non-one
if [ $? -ne 1 ]; then
    echo "invalid exit code" $?
    rm output.txt
    rm expected.txt
    exit 1
fi

# Ensures differences *are* found
diff output.txt expected.txt
if [ $? -ne 0 ]; then
    echo "Add two values please!"
    rm output.txt
    rm expected.txt
    exit 1
fi

# Prints a message on success
echo "Test finds that putting zero values: PASS"

# Cleans up files created
rm output.txt
rm expected.txt
exit 0
