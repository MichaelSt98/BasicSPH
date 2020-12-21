//
// Created by Michael Staneker on 21.12.20.
//

#ifndef BASICSPH_FILEREADER_H
#define BASICSPH_FILEREADER_H


#include <ostream>
#include <fstream>

// manages an array of ints that is stored in a file

class FileReader
{
public:
    FileReader(char *fileName); // create array based on file with this name
    ~FileReader(void);
    bool getStatus(void); // true means "good", false means "bad"
    char getItem(int index); // get item at position specified by index

    // proper use requires properly invoking the destructor
    char& operator[](int index); // overload for both get and set

    friend std::ostream& operator<<(std::ostream& out, FileReader& fa);

private:
    std::fstream file; // stream to/from array file
    bool status; // file status

    std::streampos	fileSize(void);

    // enable use of operator[] to set values in array
    char getValue(int index); // get value from file
    void setValue(int index, char value); // set item at position specified by index

    char value; // operator[] returns reference to here

    // these variables support use of operator[] on the left side of an
    // assignment statement.
    // this requires proper invocation of the destructor, to deal with prevIndex
    int prevIndex;
    int prevValue;

};


#endif //BASICSPH_FILEREADER_H
