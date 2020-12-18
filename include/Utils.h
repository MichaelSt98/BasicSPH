//
// Created by Michael Staneker on 18.12.20.
//

#ifndef BASICSPH_UTILS_H
#define BASICSPH_UTILS_H

#include <ostream>
#include <iostream>

class Utils {

};

class ProgressBar {
public:
    ProgressBar(int bar_width);
    int bar_width = 100;
    void show_progress(float progress);
};

namespace Color {
    enum Code {
        FG_DEFAULT = 39,
        FG_BLACK = 30,
        FG_RED = 31,
        FG_GREEN = 32,
        FG_YELLOW = 33,
        FG_BLUE = 34,
        FG_MAGENTA = 35,
        FG_CYAN = 36,
        FG_LIGHT_GRAY = 37,
        FG_DARK_GRAY = 90,
        FG_LIGHT_RED = 91,
        FG_LIGHT_GREEN = 92,
        FG_LIGHT_YELLOW = 93,
        FG_LIGHT_BLUE = 94,
        FG_LIGHT_MAGENTA = 95,
        FG_LIGHT_CYAN = 96,
        FG_WHITE = 97,
        BG_RED = 41,
        BG_GREEN = 42,
        BG_BLUE = 44,
        BG_DEFAULT = 49
    };

    class Modifier {
    public:
        Code code;
        Modifier(Code pCode);
        friend std::ostream& operator<<(std::ostream& os, const Color::Modifier& mod);
    };
}


#endif //BASICSPH_UTILS_H
