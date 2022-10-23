// Начало файла lab_01.h
#ifndef LAB_01_H // 
#define LAB_01_H 1

#include <cmath>
#include <iostream>
#include <gsl/gsl_integration.h>
#include "gsl_func.h"

using namespace std;

class ComputeTraining {
    protected:
        int lim_a, lim_b, n;
    public:
        ComputeTraining();
        virtual ~ComputeTraining() = 0; 

        // https://www.experts-exchange.com/articles/3843/How-to-add-properties-to-standard-C-classes.html 
        void set_lo_lim(const int& p_a);
        void set_hi_lim(const int& p_b);
        void set_n(const int& p_n); 
};

class ManualComputeIntegrall : public ComputeTraining {
    public:
    ManualComputeIntegrall();
    ~ManualComputeIntegrall(); 

    double calculation(double f(double), const double& p_a, const double& p_b, const int& p_n);
    double calculation(double f(double));
};

class GSLComputeIntegrall : public ComputeTraining {
    public:
    GSLComputeIntegrall();
    ~GSLComputeIntegrall();
    double calculation(gsl_function_type* f);
};

class Integrands{
    private:
        static std::string manual_integrands;
    public:
        Integrands();
        static double v2_1(double p_x);
        static double v2_2(double p_x);
        static double v3_1(double p_x);
        static double manual(double p_x);
        static   void set_manual(std::string);
};
#endif
