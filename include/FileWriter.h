//
// Created by Michael Staneker on 18.12.20.
//

#ifndef BASICSPH_FILEWRITER_H
#define BASICSPH_FILEWRITER_H

#include <iostream>
#include <fstream>
#include <string>

class FileWriter {

private:
    std::ofstream mFile;

public:

    FileWriter(std::string fileName);

    template <typename T> void write(T data) {
        mFile << data << std::endl;
    }

    template<class T> FileWriter &operator<<(const T &msg) {
        mFile << msg << std::endl;
        return *this;
    }

    ~FileWriter();

};


#endif //BASICSPH_FILEWRITER_H
