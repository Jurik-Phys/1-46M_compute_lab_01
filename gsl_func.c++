// Начало файла gsl_func.c++
#include "gsl_func.h"

double Convert::target(double x, void*) {
    return m_target(x);  // invoke the currently wrapped function
}

// here's your "convert" function
gsl_function_type* Convert::convert(double (*fn)(double)) {
        m_target = fn;
        return &target;
}

double (*Convert::m_target)(double) = 0;  // initialise the static member
