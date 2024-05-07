#include "mathlib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

double Abs(double x) {
    if (x < 0) {
        return x * -1.0;
    }
    return x;
}

double Sqrt(double x) {
    if (x < 0) {
        return nan("nan");
    }
    double old = 0.0;
    double new = 1.0;

    while (Abs(old - new) > EPSILON) {
        old = new;
        new = 0.5 * (old + (x / old));
    }

    return new;
}

double Sin(double x) {
    x = fmod(x, M_PI * 2.0);
    double term = x;
    double result = 0.0;
    int i = 0;
    while (term > EPSILON || term < -EPSILON) {
        result += term;
        ++i;
        term *= -x * x / ((2 * i) * (2 * i + 1));
    }
    result += term;
    return result;
}

double Cos(double x) {
    x = fmod(x, M_PI * 2.0);
    double term = 1;
    double result = 0.0;
    int i = 0;
    while (term > EPSILON || term < -EPSILON) {
        result += term;
        ++i;
        term *= -x * x / ((2 * i) * (2 * i - 1));
    }
    result += term;
    return result;
}

double Tan(double x) {
    return Sin(x) / Cos(x);
}
