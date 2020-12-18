//
// Created by Michael Staneker on 18.12.20.
//

#ifndef BASICSPH_LOGGER_H
#define BASICSPH_LOGGER_H

#include <iostream>
#include "Utils.h"

enum typelog {
    DEBUG,
    INFO,
    WARN,
    ERROR
};

struct structlog {
    bool headers = false;
    typelog level = WARN;
};

extern structlog LOGCFG;

class Logger {
public:
    Logger() {}
    Logger(typelog type);
    ~Logger();

    template<class T> Logger &operator<<(const T &msg) {
        if(msglevel >= LOGCFG.level) {
            std::cout << msg;
            opened = true;
        }
        return *this;
    }

private:
    bool opened = false;
    typelog msglevel = DEBUG;
    inline std::string getLabel(typelog type);
    inline Color::Modifier getColor(typelog type);
};

#endif //BASICSPH_LOGGER_H
