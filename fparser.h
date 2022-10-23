// Начало файла fparce.h
// По материалам статей
// "Парсер формул с помощью метода рекурсивного спуска"
// https://habr.com/ru/post/122397/
// "Еще раз про разбор выражений методом рекурсивного спуска"
// https://habr.com/ru/post/489534/
#ifndef FPARCE_H 
#define FPARCE_1

#include <iostream>
#include <cstring>
#include <cmath>

// using namespace std;

// Приоритеты математический операций
//  - Функции и переменные; (cos(x), sin(x), tan(x), exp(x))
//  - Скобки;
//  - Умножение/деление;
//  - Сложение и вычитание;  
// Разбор выражения идёот от нижнего приоритета к высшему
        
struct Result {
    // текущий результат вычислений
    double acc; 
    // остаток разбираемой строки
    std::string rest;
};                   

class FParser {
    private:
//        struct Result {
//            // текущий результат вычислений
//            double acc; 
//            // остаток разбираемой строки
//            std::string rest;
//        };                   
    
        // Переменная в терминах математического выражения
        double x;

        bool is_digits(const char& str);
        Result calc_function(const std::string&, Result);
        Result parse_number(const std::string&);
        Result parse_arithmetic(const std::string&);
        Result parse_multiplication(const std::string&);
        Result parse_brackets(const std::string&);
        Result parse_function(const std::string&);
        std::string process_string(const std::string&);

    public:
        FParser(const double&);;
        ~FParser() {};
        double parse(std::string&);
};

#endif 
