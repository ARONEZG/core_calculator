#pragma once
#include "lexer.h"
#include "node.h"
#include <vector>
#include <stdexcept>


class Parser {
public:
    explicit Parser(Lexer& lexer) : _lexer(lexer) {
        _currentToken = _lexer.getNextToken();
    }

std::unique_ptr<Node> parse() {
    return parseExpression();
}

private:
    Token _currentToken;
    Lexer& _lexer;

    void eatToket(TokenType expected) {

        if (_currentToken.type != expected) {
            throw std::runtime_error("invalid token");
        }

        _currentToken = _lexer.getNextToken();
    }

    std::unique_ptr<Node> parseExpression() {
        auto node = term();
        while (_currentToken.type == TokenType::OPERATOR && (_currentToken.symbol == '+' || _currentToken.symbol == '-')) {
            char op = _currentToken.symbol;
            eatToket(_currentToken.type);
            node = std::make_unique<OperationNode>(std::move(node), term(), op);
        }
        return node;
    }

    std::unique_ptr<Node> term() {
        auto node = factor();
        while(_currentToken.type == TokenType::OPERATOR && (_currentToken.symbol == '*' || _currentToken.symbol == '/')) {
            char op = _currentToken.symbol;
            eatToket(_currentToken.type);
            node = std::make_unique<OperationNode>(std::move(node), factor(), op);
        }
        return node;
    }

    std::unique_ptr<Node> factor() {
        if (_currentToken.type == TokenType::NUMBER) {
            auto node = std::make_unique<NumberNode>(_currentToken.value);
            eatToket(_currentToken.type);
            return node;
        } else if (_currentToken.type == TokenType::OPERATOR) {
            auto number_minus = std::make_unique<NumberNode>(-1);
            eatToket(_currentToken.type);
            auto node = term();
            return std::make_unique<OperationNode>(std::move(number_minus), std::move(node), '*');
        } else {
            eatToket(TokenType::PAREN_OPEN);
            auto node = parseExpression();
            eatToket(TokenType::PAREN_CLOSE);
            return node;
        }
    }
};