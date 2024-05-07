# Creates the example output
echo "TOO BIG" >> expected.txt

# Runs the program
./calc 3 513 > output.txt 

# Ensures exit code is Zero
if [ $? -eq 0 ]; then
    echo "invalid exit code" $?
    rm output.txt
    rm expected.txt
    exit 1
fi

# Ensures differences *are* found
diff output.txt expected.txt
if [ $? -eq 1 ]; then
    echo "Integer used was TOO BIG!"
    rm output.txt
    rm expected.txt
    exit 1
fi

# Prints a message on success
echo "Test finds that puts a value higher than 512: PASS"

# Cleans up files created
rm output.txt
rm expected.txt
exit 0
