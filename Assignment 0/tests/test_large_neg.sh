# Creates the example output
echo "TOO SMALL" >> expected.txt

# Runs the program
./calc -513 3 > output.txt 

# Ensures exit code is zero
if [ $? -eq 0 ]; then
    echo "invalid exit code" $?
    rm output.txt
    rm expected.txt
    exit 1
fi

# Ensures differences *are* found
diff output.txt expected.txt
if [ $? -eq 0 ]; then
    echo "Too small of integer!"
    rm output.txt
    rm expected.txt
    exit 1
fi

# Prints a message on success
echo "Test finds that putting small extreme integer PASS"

# Cleans up files created
rm output.txt
rm expected.txt
exit 0
