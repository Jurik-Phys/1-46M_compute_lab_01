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



