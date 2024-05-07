#include <math.h>
#include <stdio.h>

/*
* How to declare a pointer to a function.
*/

/*
* Step 1: Write a function prototype.
*         This is a prototype for a function f().
*/
double f(double);

/*
* Step 2: Replace the function name with (*ptr) for some pointer name.
*
* You now have a pointer to a function, fp!
*/
double (*fp)(double);

/*
* Step 3: For a function-pointer type, prepend typedef and (change the name).
*         Now you have a type for a pointer to a function, func_ptr.
*
* Only this last step is needed in your source code.  I've left all three
* steps in this file to help explain them.
*/
typedef double (*func_ptr)(double);


int main(void) {
    func_ptr p = sin;
    double result = p(1.0);
    printf("%f\n", result);
    return 0;
}
