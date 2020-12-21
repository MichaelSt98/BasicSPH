#include "../include/FileWriter.h"

FileWriter::FileWriter(std::string fileName) {
    mFile.open(fileName.c_str());
}

FileWriter::~FileWriter() {
    mFile.close();
}