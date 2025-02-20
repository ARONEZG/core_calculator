#pragma once

#include <memory>
#include <stdexcept>

class Node {
public:
    explicit Node() = default;
    virtual ~Node() = default;

    virtual double evaluate() = 0;

    enum class Type {
        OPERATOR,
        NUMBER,
        RIGHT_SC,
        LEFT_SC,
        END,
    } type;
};


class NumberNode: public Node {
public:
    explicit NumberNode(double value) : Node(), _value(value) {
        type = Type::NUMBER;
    }

    double evaluate() override {
        return _value;
    }
private:
    double _value;
};

class OperationNode: public Node {
public:
    explicit OperationNode(std::unique_ptr<Node> left, std::unique_ptr<Node> right, char op);

    double evaluate() override {
        auto left_value = _left->evaluate();
        auto right_value = _right->evaluate();

        switch(_op) {
            case '+':
                return left_value + right_value;
            case '-':
                return left_value - right_value;
            case '/':
                return left_value / right_value;
            case '*':
                return left_value * right_value;
        }


        throw std::runtime_error("Не распознан оператор");
    }

private:
    std::unique_ptr<Node> _left;
    std::unique_ptr<Node> _right;
    char _op;
};