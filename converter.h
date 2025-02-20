#pragma once

#include <string>
#include <vector>

inline bool isOperator(char symbol) {
    return symbol == '+'
        || symbol == '-' 
        || symbol == '/' 
        || symbol == '*' 
        || symbol == '(' 
        || symbol == ')';
}

class ExpressionConverter {
public:
    explicit ExpressionConverter(const std::string& s);

    std::vector<std::string>::iterator begin();

    std::vector<std::string>::iterator end();


    static std::vector<std::string> TrimSpases(const std::string& s);
    static std::vector<std::string> getTokens(const std::vector<std::string> non_spaces);

    template<typename iter, typename size>
    static size_t findFirstNotNumber(iter begin, iter end, size start) {
        for (auto it = begin + start; it != end; it++) {
            if (isOperator(*it)) {
                return std::distance(begin, it);
            }
        }
        return std::string::npos;
    }

    template<typename iter>
    static size_t findFirstNumber(iter begin, iter end) {
        for (auto it = begin; it != end; it++) {
            if (!isOperator(*it)) {
                return std::distance(begin, it);
            }
        }
        return std::string::npos;
    }
    
private:
    std::vector<std::string> expression_;

    void SetExpression(const std::string& s);
};
