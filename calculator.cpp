#include "calculator.h"
#include <fstream>


double Calculator::Calculate(ExpressionConverter& p) {
    return FillStack(p.begin(), p.end());
}

void Calculator::WriteHistory() {
    std::ofstream fout("history.txt");
    for (const auto& el : history_) {
        fout << el.first << " = " << el.second << std::endl;
    }
    fout.close();
}
