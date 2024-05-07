#include <math.h>
#include <stdio.h>

/*
* Declaring a variable of some type.
*/
int     i1;
double  d1;
char   *p1;   // pointer to a char
char  **pp1; // pointer to a pointer to a char

/*
* Declaring (giving a name to) a type:  prepend "typedef" of a variable
* declaration (and change the name).
*
* The variable declarations above are not needed for these typedefs to work.
* They are here only to help understand the example.
*/
typedef int     int_t;
typedef double  double_t;
typedef char   *p_t;      // pointer-to-a-char type
typedef char  **pp_t;    // pointer-to-a-pointer-to-a-char type

/*
* Using one of our new types.
*/
int_t       i2;
double_t    d2;
p_t         p2;
pp_t        pp2;

int main(void) {
    return 0;
}
