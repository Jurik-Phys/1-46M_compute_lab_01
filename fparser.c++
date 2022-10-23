// Начало файла parse.с++

// По материалам статей
// "Парсер формул с помощью метода рекурсивного спуска"
// https://habr.com/ru/post/122397/
// "Еще раз про разбор выражений методом рекурсивного спуска"
// https://habr.com/ru/post/489534/

#include <iostream>
#include <cstring>
#include <cmath>
#include "fparser.h"

// Приоритеты математический операций
//  - Функции и переменные; (cos(x), sin(x), tan(x), exp(x))
//  - Скобки;
//  - Умножение/деление;
//  - Сложение и вычитание;  
// Разбор выражения идёот от нижнего приоритета к высшему

    
bool FParser::is_digits(const char& str){
    // const char* to string
    std::string t_str;
    t_str = str;

    if ( t_str.find_first_not_of("0123456789.") == std::string::npos ){
        // не найден символ, отличный от "0123456789."
        // т.е., рассматривемое число - одно из заданного набора
        return true;
    }
    else {
        return false;
    }
}

// Список известных математических функций
Result FParser::calc_function(const std::string& func, Result current){

    Result result;
    result.rest = current.rest.substr(1, current.rest.length()); 

    if ( func == std::string("sin") ){
        result.acc = sin(current.acc);
        return result;
    }
    if ( func == std::string("cos") ){
        result.acc  = cos(current.acc);
        return result;
    }
    if ( func == std::string("tan") ){
        result.acc = sin(current.acc);
        return result;
    }
    if ( func == std::string("exp") ){
        result.acc = exp(current.acc);
        return result;
    }
    // std::cout << "Неизвестная функция: " << func << "\n";
    return current;
}

// Разбор чисел в строке
Result FParser::parse_number(const std::string& s){
    int i = 0;
    int dot_count = 0;

    double parsed_number = 0; 
    std::string parsed_string, rest_string; 

    Result num_result;

    // Debug
    // std::cout << "Parse number \n";
    // std::cout << "NUM(s): " << s << "\n";
    // std::cout << "NUM: s[0]: " << s[0] << "\n";

    if ( s[0] == std::string("x")[0] ){
        i = 1;
        parsed_number = x;
        // Debug
        // std::cout << "x = " << parsed_number << "\n";
        
        rest_string   = s.substr(i, s.length() - i );

        num_result.acc  = parsed_number;
        num_result.rest = rest_string;
    }

    else{
        // Определение количества символов в разбираемом числе или переменной "x" 
        for ( std::string::const_iterator ptr = s.begin(); ptr < s.end(); ptr++){
            if ( ( ptr == s.begin() ) && ( *ptr == std::string("-")[0] )){
                i++;
                continue;
            }

            if ( is_digits(*ptr) == true ) {
                // Debug 
                // std::cout << "PTR (Число): " << *ptr << "\n";
                if ( ( *ptr == std::string(".")[0] ) && ( ++dot_count > 1 ) ) {
                    std::cout << "Ошибка формата числа. Более одной точки \n";
                    break;
                }
                i++;
            } 
            else{
                break;
            }
        }
        if ( i == 0 ){
            std::cout << "Числа не найдены" << "\n";
        }

        parsed_string = s.substr(0,i);
        parsed_number = atof(parsed_string.c_str());
        rest_string   = s.substr(i, s.length() - i );

        num_result.acc  = parsed_number;
        num_result.rest = rest_string;
    }
    return num_result;
}

// Парсинг арифметических операций (+/-)
Result FParser::parse_arithmetic(const std::string& s){

    // Debug
    // std::cout << "Arithmetic input: " << s << "\n";

    // Запуск парсинга выражения более высокого уровня 
    Result current = parse_multiplication(s);

    double acc; 

    // Debug
    // std::cout << "Arithmetic ЧИСЛО: " << current.acc << "\n";
    // std::cout << "Arithmetic ХВОСТ: " << current.rest << "\n";
    // int iteration = 0;

    while ( current.rest.length() > 0 ){
        // Debug 
        // std::cout << "ARITHMETIC ITERATION: " << ++iteration << "\n";
        // std::cout << "ARITHMETIC OPERATION: " << current.rest[0] << "\n"; 
        if ( ( current.rest[0] != std::string("+")[0] ) && ( current.rest[0] != std::string("-")[0]) ){
            // Debug
            // std::cout << "Arithmetic: Неизвестная операция \n";
            break;
        }

        char sign = current.rest[0]; 
        // Debug
        // std::cout << "Арифметическая опреация: " << sign << "\n";

        std::string next = current.rest.substr( 1, current.rest.length());
        // Debug
        // std::cout << "Next string: " << next << "\n";

        acc = current.acc;
        current = parse_multiplication(next);

        // Debug
        // std::cout << " * ARIHMETHIC CURRENT: " << current.acc << "\n";
        if ( sign == std::string("+")[0] ){
            acc += current.acc;
            // Debug
            // std::cout << "ACC = " << acc << "\n";
        }
        else{
            acc -= current.acc;
        }
        current.acc = acc;
    }
    
    Result next;
    next.acc =  current.acc;
    next.rest = current.rest;
    return next;
}

// Парсинг операций умножения/деления
Result FParser::parse_multiplication(const std::string& s){
    // Debug
    // std::cout << " -> Multiplication input: " << s << "\n";

    // Прежеде чем умножать проверка на наличие скобок
    // с разбором выражения в скобках 
    Result current = parse_brackets(s);

    // Debug
    // std::cout << "Multiplication: ЧИСЛО: " << current.acc << "\n";
    // std::cout << "Multiplication: ХВОСТ: " << current.rest << "\n";
    double acc; 

    // Debug
    // int iteration = 0;
    while ( current.rest.length() > 0 ){
        // Debug
        // std::cout << "Multiplication ITERATION: " << ++iteration << "\n";
        if ( ( current.rest[0] != std::string("*")[0] ) && ( current.rest[0] != std::string("/")[0]) ){
            // Debug
            // std::cout << "Multiplication: Неизвестная операция \n";
            break;
        }

        char sign = current.rest[0]; 
        // Debug
        // std::cout << "Мультипликативная опреация: " << sign << "\n";
        
        std::string next = current.rest.substr( 1, current.rest.length());
        // Debug
        // std::cout << "Next string: " << next << "\n";

        acc = current.acc;
        current = parse_brackets(next);

        if ( sign == std::string("*")[0] ){
            acc *= current.acc;
            // Debug
            // std::cout << "ACC = " << acc << "\n";
        }
        else{
            acc /= current.acc;
        }
        current.acc = acc;
    }
    return current;
}

// Парсинг наличия скобок
Result FParser::parse_brackets(const std::string& s){

    // Debug
    // std::cout << " --> Parse bracket input: " << s << "\n";
    if ( s[0] == std::string("(")[0] ){
        // Первый символ в строке - скобка;
        // Запуск парсинга строки без символа скобки
        Result braсket_result;
        braсket_result = parse_arithmetic(s.substr(1, s.length()));

        // Debug
        // std::cout << "AAA: " << braсket_result.rest << "\n";

        if ( ( braсket_result.rest.length() > 0 ) && ( braсket_result.rest[0] == std::string(")")[0] )){
            // Debug
            // std::cout << "240: " << braсket_result.rest.substr(1, braсket_result.rest.length()) << "\n"; 
            braсket_result.rest = braсket_result.rest.substr(1, braсket_result.rest.length());
        }
        else{
            std::cout << "Закрывающая скобка не найдена" << "\n";
        }
        return braсket_result;
    }
    // Debug
    // std::cout << " --> Стартовой открывающей скобки в выражении нет. Запуск pars_function(s) \n";
    return parse_function(s);
}

// Парсинг функции (текст + открывающая скобка)
Result FParser::parse_function(const std::string& s){
    std::string func;
    // Debug
    // std::cout << " ---> Parse function input: " << s << "\n";
    for ( std::string::const_iterator ptr = s.begin(); ptr < s.end(); ptr++){
        // Debug
        // std::cout << *ptr << "\n";
        if (( is_digits(*ptr) == false ) && ( isalpha(*ptr) != 0 )) {
            func += *ptr;
        } 
        else {
            if ( func.length() > 0 ){
                int i = s.find(func) + func.length(); 
                // Debug
                // std::cout << "Определена функция или переменная: " << func << "\n";
                // std::cout << "Строка: " << s << "\n"; 
                // std::cout << "Следующий символ в строке: " << s[i] << "\n"; 
                if ( s[i]  == std::string("(")[0] ) {
                    // Следующий символ за функцией или переменной - открывающая скобка, 
                    // значит то, что стоит перед ней - ФУНКЦИЯ
                    Result result;
                    // Debug
                    // std::cout << "Функция: " << s.substr(i+1, s.length()) << "\n";
                    result = parse_arithmetic(s.substr(i+1, s.length() )); 
                    return calc_function(func, result);
                } else {
                    // Следующий символ в строке - не открывающая скобка, 
                    // значит то, что стоит перед ней - ПЕРЕМЕННАЯ   
                    Result result;
                    result = parse_number(s.substr(i-1, s.length() ));
                    return result;
                }
            }
            else {
                // Debug
                // std::cout << "Найдено число" << "\n";
                Result result;
                result = parse_number(s);
                // Debug
                // std::cout << ">>> " << s << "\n";
                // std::cout << ">>> " << result.rest << "\n";
                return result;
            }
        }
    }
    // Debug
    // std::cout << "RUN PARSE_NUMBER \n";
    return parse_number(s);
}

std::string FParser::process_string(const std::string& s){
    std::string o_str;
    for ( std::string::const_iterator ptr = s.begin(); ptr < s.end(); ptr++){
        if ( *ptr != std::string(" ")[0] ){
                o_str.push_back(std::tolower(*ptr));
        }
    }
    return o_str;
}

// Constructor 
FParser::FParser(const double& input_x) { x = input_x; };
    
double FParser::parse(std::string& s){
    s = process_string(s);
    
    // Debug
    // std::cout << "Без пробелов: "  << s << "\n";
    // std::cout << "Переменная <x> = "  << x << "\n";
    
    Result result;
    result = parse_arithmetic(s);
    // Debug
    // std::cout << "RESULT ARITHMETICS: " << result.acc << "\n";
    return result.acc;
}
