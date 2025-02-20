#include "converter.h"
#include <vector>
#include <numeric>


using namespace std;

ExpressionConverter::ExpressionConverter(const string& s) {
    auto expr = TrimSpases(s);
    SetExpression(std::accumulate(expr.begin(), expr.end(), std::string("")));
}

std::vector<std::string>::iterator ExpressionConverter::begin() {
    return expression_.begin();
}

std::vector<std::string>::iterator ExpressionConverter::end() {
    return expression_.end();
}

void ExpressionConverter::SetExpression(const string& s) {
    auto begin = s.begin();
    for (auto it = s.begin(); it != s.end(); it++) {
        if (*it == '+' || *it ==  '-' || *it ==  '*' ||
            *it ==  '/' || *it ==  '(' || *it ==  ')') {
            if (!string(begin, it).empty()) {
                expression_.push_back(string(begin, it));
            }
            expression_.push_back(string());
            expression_.back().push_back(*it);
            begin = it + 1;
        }
    }

    if (expression_.empty()) {
        expression_.push_back(s);
    }

    for (auto it = s.end() - 1; it >= s.begin(); it--) {
        if (*it == '+' || *it ==  '-' || *it ==  '*' ||
            *it ==  '/' || *it ==  '(' || *it ==  ')') {
            if (!string(it + 1, s.end()).empty()) {
                expression_.push_back(string(it + 1, s.end()));
            }
            break;
        }
    }
}

std::vector<std::string> ExpressionConverter::TrimSpases(const string& s) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t index = start;
    size_t end = s.size();
    while (index < end - 1) {
        start = std::min(end - 1, s.find_first_not_of(' ', start));
        index = std::min(end, s.find_first_of(' ', start));
        result.emplace_back(s.substr(start, index - start));
        start = index;
    }
    return result;
}


std::vector<std::string> ExpressionConverter::getTokens(const std::vector<std::string> non_spaces) {
    auto whole_line = std::accumulate(non_spaces.begin(), non_spaces.end(), std::string(""));
    std::vector<std::string> tokens;
    size_t start = 0;
    size_t index = start;
    size_t end = whole_line.size();
    while (index < end) {
        index = std::min(end,findFirstNotNumber(whole_line.begin(), whole_line.end(), start));
        auto prefix = whole_line.substr(start, index - start);
        auto postfix = whole_line.substr(index, 1);

        if (!prefix.empty()) {
            tokens.emplace_back(prefix);
        }
        
        if (!postfix.empty()) {
            tokens.emplace_back(postfix);
        }

        start = index + 1;
    }
    return tokens;
}
