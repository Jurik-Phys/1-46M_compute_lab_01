// Начало файла main.c++

#include <cstdlib>
#include "gsl_func.h"
#include "lab_01.h"


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
