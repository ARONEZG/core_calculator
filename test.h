#pragma once
#include <string>
#include "converter.h"
#include <iostream>
#include <vector>

std::ostream& operator<<(std::ostream& stream, const std::vector<std::string>& expr) {
    int i = 0;
    for (const auto& token : expr) {
        stream << "[" << i << "]: " << token << ";" << std::endl;
    }

    return stream;
}


std::vector<std::string> checkTrim(const std::string& expr) {
    std::cout << "Исходное выражение: <" << expr << ">" << std::endl;
    auto result =  ExpressionConverter::TrimSpases(expr);
    std::cout << "Полученное выражение: <" << result << std::endl;
    return result;
}