// Начало файла lab_01.с++

#include <cstdlib>
#include <iostream>
#include <cmath>
#include <gsl/gsl_integration.h>
#include "doctest.h"

using namespace std;

class ComputeTraining {
    protected:
        int lim_a, lim_b, n;

    public:
        ComputeTraining();
        virtual ~ComputeTraining() = 0; 

        // https://www.experts-exchange.com/articles/3843/How-to-add-properties-to-standard-C-classes.html 
        void set_lo_lim(const int& p_a){ lim_a = p_a; };
        void set_hi_lim(const int& p_b){ lim_b = p_b; };
        void set_n(const int& p_n){ n = p_n; };
};

// https://stackoverflow.com/a/25762852
ComputeTraining::ComputeTraining() { cout << "ComputeTraining Constructor" << "\n"; }
ComputeTraining::~ComputeTraining() { cout << "[~] ComputeTraining Destructor" << "\n"; }

class ManualComputeIntegrall : public ComputeTraining {
    public:
    ManualComputeIntegrall(){
        cout << "ManualComputeIntegrall Constructor" << "\n";
        set_lo_lim(0);
        set_hi_lim(1);
        set_n(100);
    }
    ~ManualComputeIntegrall() {
        cout << "[~] ManualComputeIntegrall Destructor" << "\n";
    }

    // Manual integration 
    double calculation(double f(double), const double& p_a, const double& p_b, const int& p_n){
        double integrall = 0;
        double h = ( p_b - p_a ) / p_n; 

        for ( int k = 0; k < p_n; k++ ){
            integrall += f(p_a + h/2 + k*h);
        }
        return integrall*h;
    }

    // Manual integration (without ext. low and hight limit)
    double calculation(double f(double)){
        double integrall = 0;
        double h =  ( lim_b - lim_a ) / double(n); 
        for ( int k = 0; k < n; k++ ){
            integrall += f(lim_a + h/2 + k*h);
        }
        // don't forget to multiply the integral by "h"
        return integrall*h;
    }
};

typedef double gsl_function_type(double, void *);

// https://overcoder.net/q/588378/создать-функцию-из-другой
// https://coliru.stacked-crooked.com/a/8accb5db47a0c51d
class Convert{
    Convert() = delete;  // don't allow construction of this class 

    // pointer to the function to be invoked
    static double (*m_target)(double);

    // this is the function we'll actually pass to GSL
    static double target(double x, void*) {
        // invoke the currently wrapped function 
        return m_target(x);  
    }

    public:
    // here's your "convert" function
    static gsl_function_type* convert(double (*fn)(double)) {
        m_target = fn;
        return &target;
    }
};

// initialise the static member 
double (*Convert::m_target)(double) = 0;  

class GSLComputeIntegrall : public ComputeTraining {
    public:
    GSLComputeIntegrall(){
        cout << "GSLComputeIntegrall Constructor" << "\n";
        set_lo_lim(0);
        set_hi_lim(1);
        set_n(100);
    }
    ~GSLComputeIntegrall() {
        cout << "[~] GSLComputeIntegrall Destructor" << "\n";
    }

    double calculation(gsl_function_type* f){
        gsl_integration_workspace * w = gsl_integration_workspace_alloc(1000);
        double result, error;

        gsl_function F;
        F.function = f; 

        // https://www.gnu.org/software/gsl/doc/html/integration.html#qags-adaptive-integration-with-singularities
        // https://www.gnu.org/software/gsl/doc/html/integration.html#adaptive-integration-example
        gsl_integration_qags (&F, lim_a, lim_b, 0, 1e-7, 1000, w, &result, &error);

        // printf ("V2_2: GSL result          = % .18f\n", result);
        // printf ("exact result    = % .18f\n", expected);
        // printf ("V2_2: GSL estimated error = % .18f\n", error);
        // printf ("actual error    = % .18f\n", result - expected);
        // printf ("V2_2: GSL intervals       = %zu\n", w->size);

        gsl_integration_workspace_free (w);
        return result;
    }
};

class Integrands{
    public:

    static double v2_1(double p_x){
        return (p_x + pow(p_x, 2) - pow(p_x, 3) - 1) / (1.0 + pow(p_x, 2));
    }
    
    TEST_CASE( "Test integrands v2_1"  ) {
        CHECK( v2_1(0) == -1 );
        CHECK( v2_1(1) == 0  );
    }

    static double v2_2(double p_x){
        return pow(cos(p_x), 3) * sin(2*p_x);
    }


    static double v3_1(double p_x){
        return 1.0 / ( 1.0 + sqrt(2*p_x + 1.0 ));
    }


};

int main(int argc, char** argv){
    double a, b;
    int n;

    Integrands f;

    ManualComputeIntegrall c_i;
    GSLComputeIntegrall gsl_i;
    
    c_i.set_lo_lim(0);

    cout << "ManualComputeIntegrall. Method Compute (w/о param)  \n";
    cout << "deafult A = 0 \n";
    cout << "deafult B = 1 \n";
    cout << "deafult N = 100 \n";

    cout << "=> Variant №2, integrall №1: " << c_i.calculation(f.v2_1) << "\n";
    cout << "=> Variant №2, integrall №2: " << c_i.calculation(f.v2_2) << "\n";
    cout << "=> Variant №3, integrall №1: " << c_i.calculation(f.v3_1) << "\n";

    cout << "\n   ==>> GSL Library <<== \n\n";  
    
    cout << "=> Variant №2, integrall №1: " << gsl_i.calculation(Convert::convert(&f.v2_1)) << "\n";
    cout << "=> Variant №2, integrall №2: " << gsl_i.calculation(Convert::convert(&f.v2_2)) << "\n";
    cout << "=> Variant №3, integrall №1: " << gsl_i.calculation(Convert::convert(&f.v3_1)) << "\n";

    cout << "\n   ==>> Введите границы интегрирования <<== \n\n";  
    cout << "> Нижняя граница интегрирования (a): ";
 	cin >> a;
	cout << "> Верхняя граница интегрирования (b): ";
	cin >> b;
    cout << "> Число разбиений отрезка (N): ";
	cin >> n;
    
    c_i.set_lo_lim(a);
    c_i.set_hi_lim(b);
    c_i.set_n(n);
    
    gsl_i.set_lo_lim(a);
    gsl_i.set_hi_lim(b);
    gsl_i.set_n(n);
    
    cout << "\n=> Variant №2, integrall №1: " << c_i.calculation(f.v2_1) << "\n";
    cout << "=> Variant №2, integrall №2: " << c_i.calculation(f.v2_2) << "\n";
    cout << "=> Variant №3, integrall №1: " << c_i.calculation(f.v3_1) << "\n";
    
    cout << "\n   ==>> GSL Library <<== \n\n";  
    
    cout << "=> Variant №2, integrall №1: " << gsl_i.calculation(Convert::convert(&f.v2_1)) << "\n";
    cout << "=> Variant №2, integrall №2: " << gsl_i.calculation(Convert::convert(&f.v2_2)) << "\n";
    cout << "=> Variant №3, integrall №1: " << gsl_i.calculation(Convert::convert(&f.v3_1)) << "\n";
    
    return 0;
}
