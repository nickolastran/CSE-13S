# Creates the example output
echo "EXACT POSITIVE EDGE BOUND" >> expected.txt

# Runs the program
./calc 3 512 > output.txt 

# Ensures exit code is one
if [ $? -eq 1 ]; then
    echo "invalid exit code" $?
    rm output.txt
    rm expected.txt
    exit 1
fi

# Ensures differences *are* found
diff output.txt expected.txt
if [ $? -eq 0 ]; then
    echo "Exactly a positive bound inserted!"
    rm output.txt
    rm expected.txt
    exit 1
fi

# Prints a message on success
echo "Test finds that putting exactly 512 as an integer: PASS"

# Cleans up files created
rm output.txt
rm expected.txt
exit 0
