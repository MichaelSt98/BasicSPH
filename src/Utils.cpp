#include "../include/Utils.h"

ProgressBar::ProgressBar(int bar_width) : bar_width { bar_width } {}

void ProgressBar::show_progress(float progress) {
    std::cout << "[";
    int pos = bar_width * progress;
    for (int i = 0; i < bar_width; ++i) {
        if (i < pos) std::cout << "=";
        else if (i == pos) std::cout << ">";
        else std::cout << " ";
    }
    std::cout << "] " << int(progress * 100.0) << " %\r";
    std::cout.flush();
}

Color::Modifier::Modifier(Code pCode) : code(pCode) {}

std::ostream& Color::operator<<(std::ostream& os, const Color::Modifier& mod) {
    return os << "\033[" << mod.code << "m";
}