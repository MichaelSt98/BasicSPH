#include <iostream>
#include <iomanip>
#include "../include/FileReader.h"

// flags for opening a file that already exists
static const std::ios::openmode  	readWriteMode = std::ios::in | std::ios::out | std::ios::binary;

// flags for creating a file that does not yet exist
static const std::ios::openmode		createMode = std::ios::out | std::ios::binary;

FileReader::FileReader(char *fileName) :
        prevIndex(0),
        prevValue(0),
        value(0)
{
    file.open(fileName, createMode); // create file
    file.close(); // close so we can re-open
    file.open(fileName, readWriteMode); // open file in read/write mode
    status = file.is_open() && file.good(); // record stream status
}

FileReader::~FileReader(void)
{
    std::cout << "~FileReader" << std::endl;
    std::cout << *this;
    // write out previously set value to file if necessary
    // "the last slice of banana"
    if (value != prevValue)
        setValue(prevIndex, value);

    file.close();
    std::cout << std::endl << std::endl;
}

bool FileReader::getStatus(void)
{
    return status;
}

char FileReader::getValue(int index)
{
    char	v;
    bool	eof = false;

    file.seekg(index * sizeof(v));
    file.read((char *) &v, sizeof(v));
    if (file.eof()) {
        file.clear(); // clear eof and fail error bits
        v = 0; // default value for Windows file system
        eof = true;
    }
    std::cout << std::setw(7) << std::right << (int) v << " <- file[" << index << "]";
    if (eof)
        std::cout << "     (eof)";
    std::cout << std::endl;
    return v;
}

void FileReader::setValue(int index, char value)
{
    file.seekp(index * sizeof(value));
    file.write((char *) &value, sizeof(value));
    std::cout << "file[" << index << "] <- " << (int) value << std::endl;
}

// This operator[] works on the lefthand side of an assignment by
// storing values from the previous time it was called. This allows
// it to discover if it was called on the lefthand side by comparing
// the data in the 'value' data member to what it put into 'value'
// the previous time. If that has changed, then the previous call
// was on the lefthand side and the file needs to be updated.
char& FileReader::operator[](int index)
{
    std::cout << *this;
    // write out previously set value to file if necessary
    if (value != prevValue)
        setValue(prevIndex, value);

    value = getValue(index);

    // record current values for next time
    prevIndex = index;
    prevValue = value;
    std::cout << std::endl;
    return value;
}

std::streampos FileReader::fileSize(void)
{
    file.seekg(0, std::ios::end); // seek to end of file
    return file.tellg(); // find out where that is
}

std::ostream& operator<<(std::ostream& out, FileReader& fa)
{
    std::streamoff	size = fa.fileSize() / sizeof(char);
    bool		first = true;

    out << "{value " << (int) fa.value
        << ", prevValue " << fa.prevValue
        << ", prevIndex " << fa.prevIndex
        << "}" << std::endl;
    return out;
}
