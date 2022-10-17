// Начало файла gsl_func.h
// https://overcoder.net/q/588378/создать-функцию-из-другой
// https://coliru.stacked-crooked.com/a/8accb5db47a0c51d

#ifndef GSL_FUNC_H
#define GSL_FUNC_H

#include <iostream>

using namespace std;

typedef double gsl_function_type(double, void*);  // typedef to make things a bit more readable...

// static class to wrap single-parameter function in GSL-compatible interface
// this really just serves as a namespace - there are no non-static members,
// but using a class lets us keep the details private
class Convert
{
    Convert() = delete;  // don't allow construction of this class    
    
    // pointer to the function to be invoked
    static double (*m_target)(double);
    
    // this is the function we'll actually pass to GSL
    static double target(double x, void*); 

public:
    // here's your "convert" function
    static gsl_function_type* convert(double (*fn)(double)); 
};


#endif
