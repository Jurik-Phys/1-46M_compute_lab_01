// Начало файла lab_01.с++

#include "lab_01.h"

// https://stackoverflow.com/a/25762852
ComputeTraining::ComputeTraining() { cout << "ComputeTraining Constructor" << "\n"; }
ComputeTraining::~ComputeTraining() { cout << "[~] ComputeTraining Destructor" << "\n"; }

// https://www.experts-exchange.com/articles/3843/How-to-add-properties-to-standard-C-classes.html 
void ComputeTraining::set_lo_lim(const int& p_a){ lim_a = p_a; };
void ComputeTraining::set_hi_lim(const int& p_b){ lim_b = p_b; };
void ComputeTraining::set_n(const int& p_n){ n = p_n; };

// ==>> MANUAL COMPUTE INTEGRALL << == //

ManualComputeIntegrall::ManualComputeIntegrall(){
    cout << "ManualComputeIntegrall Constructor" << "\n";
    set_lo_lim(0);
    set_hi_lim(1);
    set_n(100);
}

ManualComputeIntegrall::~ManualComputeIntegrall() {
    cout << "[~] ManualComputeIntegrall Destructor" << "\n";
}

double ManualComputeIntegrall::calculation(double f(double), const double& p_a, const double& p_b, const int& p_n){
    double integrall = 0;
    double h = ( p_b - p_a ) / p_n; 

    for ( int k = 0; k < p_n; k++ ){
        integrall += f(p_a + h/2 + k*h);
    }
    return integrall*h;
}

double ManualComputeIntegrall::calculation(double f(double)){
    double integrall = 0;
    double h =  ( lim_b - lim_a ) / double(n); 
    for ( int k = 0; k < n; k++ ){
        integrall += f(lim_a + h/2 + k*h);
    }
    // don't forget to multiply the integral by "h"
    return integrall*h;
}

// ==>> GSL COMPUTE INTEGRALL << == //

GSLComputeIntegrall::GSLComputeIntegrall(){
    cout << "GSLComputeIntegrall Constructor" << "\n";
    set_lo_lim(0);
    set_hi_lim(1);
    set_n(100);
}

GSLComputeIntegrall::~GSLComputeIntegrall() {
    cout << "[~] GSLComputeIntegrall Destructor" << "\n";
}

double GSLComputeIntegrall::calculation(gsl_function_type* f){
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


// ==>> SET OF INTEGRANDS << == //


double Integrands::v2_1(double p_x){
    return (p_x + pow(p_x, 2) - pow(p_x, 3) - 1) / (1.0 + pow(p_x, 2));
}
    
double Integrands::v2_2(double p_x){
        return pow(cos(p_x), 3) * sin(2*p_x);
}

double Integrands::v3_1(double p_x){
        return 1.0 / ( 1.0 + sqrt(2*p_x + 1.0 ));
}
