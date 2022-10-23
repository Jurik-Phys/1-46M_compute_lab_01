#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "lab_01.h"

TEST_CASE("Тестирование правильности вычисления подинтегрального выражения V2_1"){
    CHECK(Integrands::v2_1(0) == -1 );
    CHECK(Integrands::v2_1(1) == 0 );
}

TEST_CASE("Тестирование правильности вычисления подинтегрального выражения V2_2"){
    CHECK(Integrands::v2_2(0) == 0 );
    CHECK(Integrands::v2_2(3.14/2) - 0 < 0.00001 );
}

TEST_CASE("Тестирование правильности вычисления подинтегрального выражения V3_1"){
    CHECK(Integrands::v3_1(4) == 0.25 );
    CHECK(Integrands::v3_1(0) == 0.5 );
}

TEST_CASE("Тестирование правильности вычисления интегралла с диапазоном по-умолчанию"){
    Integrands f;
    ManualComputeIntegrall c_i;
    
    CHECK(abs(c_i.calculation(f.v2_1) - (-0.377645)) < 0.00001 );
    CHECK(abs(c_i.calculation(f.v2_2) - 0.381594)    < 0.00001 );
    CHECK(abs(c_i.calculation(f.v3_1) - 0.420145)    < 0.00001 );
}

TEST_CASE("Тестирование интеграллов V2_1, V2_2 заданных вручную (диапазон по-умолчанию)"){
    Integrands f;
    ManualComputeIntegrall c_i;
    GSLComputeIntegrall gsl_i;

    // V2_1
    std::string f_input = "(x + x*x - x*x*x - 1)/(1 + x*x)";
    f.set_manual(f_input);

    CHECK(abs(c_i.calculation(f.manual) - (-0.377645)) < 0.0001 );
    CHECK(abs(gsl_i.calculation(Convert::convert(&f.manual)) - (-0.377645)) < 0.00001 );
}

TEST_CASE("Тестирование интеграллов V2_2 заданных вручную (диапазон по-умолчанию)"){
    Integrands f;
    ManualComputeIntegrall c_i;
    GSLComputeIntegrall gsl_i;

    // V2_2
    std::string f_input = "cos(x)*cos(x)*cos(x)*sin(2*x)";
    f.set_manual(f_input);

    CHECK(abs(c_i.calculation(f.manual) - 0.381594) < 0.00001 );
    CHECK(abs(gsl_i.calculation(Convert::convert(&f.manual)) - 0.381582) < 0.00001 );
}
