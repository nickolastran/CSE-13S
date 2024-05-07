# Creates the example output
echo "NOT ENOUGH INPUT" >> expected.txt

# Runs the program
./calc 3 > output.txt 

# Ensures exit code is zero
if [ $? -eq 0 ]; then
    echo "invalid exit code" $?
    rm output.txt
    rm expected.txt
    exit 1
fi

# Ensures differences *are* found
diff output.txt expected.txt
if [ $? -eq 1 ]; then
    echo "There is not enough input!"
    rm output.txt
    rm expected.txt
    exit 1
fi

# Prints a message on success
echo "Test finds that putting 1 integer = NOT ENOUGH INPUT: PASS"

# Cleans up files created
rm output.txt
rm expected.txt
exit 0
