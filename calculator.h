#pragma once

#include "converter.h"

#include <string_view>
#include <deque>
#include <utility>
#include <cassert>
#include <QObject>

class Calculator : public QObject, private ExpressionConverter {
public:
    Calculator() = default;

    double Calculate(ExpressionConverter& p);

    void WriteHistory();

private:

    std::vector<std::pair<std::string, double>> history_;

    template<typename iterator>
    void PutIntoHistory(iterator begin, iterator end, double result);

    template<typename iterator>
    std::pair<iterator, iterator> CountBrackets(iterator begin, iterator end);

    template<typename iterator>
    double FillStack(iterator begin, iterator end);
};

template<typename iterator>
void Calculator::PutIntoHistory(iterator begin, iterator end, double result) {
    std::string s;
    for (auto it = begin; it != end; it++) {
        s += (*it + " ");
    }
    history_.push_back({std::move(s), result});
}

template<typename iterator>
std::pair<iterator, iterator> Calculator::CountBrackets(iterator begin, iterator end) {
    int left =  0, right = 0;
    iterator right_it;
    for (auto it = begin; it != end; it++) {
        if (*it == ")") {
            right++;
        }
        if (*it == "(") {
            left++;
        }
        if (right == left) {
            right_it = it;
            break;
        }
    }
    if (*right_it != ")") {
        right_it = end;
    }
    return {begin, right_it};
}

template<typename iterator>
double Calculator::FillStack(iterator begin, iterator end) {
    std::deque<double> numbers_;
    std::deque<std::string_view> operations_;
    for (auto it = begin; it < end; it++) {
        if (*it == "+" || *it == "-" ) {
            double d = 0;
            if (*(it + 1) == "(") {
                auto [left, right] = CountBrackets(it + 1, end);
                d = FillStack(left + 1, right);
                if (!numbers_.empty()) {
                    d = *it == "+" ?  d + numbers_.back() : numbers_.back() - d;
                    numbers_.pop_back();
                }
                d = *it == "+" ?  d : - d;
                numbers_.push_back(d);
                it = right;
                continue;
            }
            operations_.push_back(*it);
        } else if (*it == "*" || *it == "/") {
            double d = 0;
            if (*(it + 1) == "(") {
                auto [left, right] = CountBrackets(it + 1, end);
                d = FillStack(left + 1, right);
                d = *it == "*" ?  d * numbers_.back() : numbers_.back() / d;
                numbers_.pop_back();
                numbers_.push_back(d);
                it = right;
                continue;
            }
            d = *it == "*"
                    ? numbers_.back() * stod(*(it+1))
                    : numbers_.back() / stod(*(it+1));
            numbers_.pop_back();
            numbers_.push_back(d);
            it++;
        } else if (*it == "(") {
            auto [left, right] = CountBrackets(it, end);
            double d = FillStack(left + 1, right);
            numbers_.push_back(d);
            it = right;
        } else {
            if (*it == "(" || *it == ")") {
                continue;
            }
            numbers_.push_back(stod(*it));
        }
    }
    if (numbers_.size() == operations_.size()) {
        if (operations_.front() == "-") {
            double x = -numbers_.front();
            numbers_.pop_front();
            numbers_.push_front(x);
        }
        operations_.pop_front();
    }
    double result = numbers_.front();
    numbers_.pop_front();
    while (!numbers_.empty()) {
        result = operations_.front() == "+" ? result + numbers_.front() : result - numbers_.front();
        operations_.pop_front();
        numbers_.pop_front();
    }
    PutIntoHistory(begin, end, result);
    return result;

}
