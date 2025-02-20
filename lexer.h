#pragma once
#include "node.h"
#include "converter.h"

enum class TokenType { NUMBER, OPERATOR, PAREN_OPEN, PAREN_CLOSE, END };

struct Token {
    TokenType type;
    double value;
    char symbol;
};

class Lexer {
public:
explicit Lexer(const std::string& expression) {
    auto result = ExpressionConverter::TrimSpases(expression);
    result = ExpressionConverter::getTokens(result);
    result.push_back("");
    _expr = std::move(result);
    _current_iter = _expr.begin();
}

Token getNextToken() const {
    const auto& token = *_current_iter;
    if (_current_iter != _expr.end()) {
        std::advance(_current_iter, 1);
    }
    bool is_digit = std::isdigit(token[0]);

    if (is_digit) {
        return {TokenType::NUMBER, std::stod(token), 'n'};
    }

    if (token.empty()) {
        return {TokenType::END, 0, 'e'};
    }

    switch(token[0]) {
        case '+':
            return {TokenType::OPERATOR, 0, '+'};
        case '-':
            return {TokenType::OPERATOR, 0, '-'};
        case '*':
            return {TokenType::OPERATOR, 0, '*'};
        case '/':
            return {TokenType::OPERATOR, 0, '/'};
        case '(':
            return {TokenType::PAREN_OPEN, 0, '('};
        case ')':
            return {TokenType::PAREN_CLOSE, 0, ')'};
    }

    throw std::runtime_error("something wrong");
}

private:
    std::vector<std::string> _expr;
    mutable std::vector<std::string>::iterator _current_iter;
};