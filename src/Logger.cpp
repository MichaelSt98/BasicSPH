//
// Created by Michael Staneker on 18.12.20.
//

#include "../include/Logger.h"

Logger::Logger(typelog type) {
    msglevel = type;
    Color::Modifier def(Color::FG_DEFAULT);
    if(LOGCFG.headers) {
        std::cout << getColor(type);
        operator << (getLabel(type));
        std::cout << def;
    }
}

Logger::~Logger() {
    if(opened) {
        std::cout << std::endl;
    }
    opened = false;
}

inline std::string Logger::getLabel(typelog type) {
    std::string label;
    switch(type) {
        case DEBUG: label = "[DEBUG] "; break;
        case INFO:  label = "[INFO ] "; break;
        case WARN:  label = "[WARN ] "; break;
        case ERROR: label = "[ERROR] "; break;
    }
    return label;
}

inline Color::Modifier Logger::getColor(typelog type) {
    Color::Modifier color(Color::FG_DEFAULT);
    switch(type) {
        case DEBUG: color.code = Color::FG_DARK_GRAY; break;
        case INFO:  color.code = Color::FG_LIGHT_GREEN; break;
        case WARN:  color.code = Color::FG_YELLOW; break;
        case ERROR: color.code = Color::FG_RED; break;
    }
    return color;
}
