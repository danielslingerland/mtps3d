//
// Created by danie on 26-6-2020.
//

#ifndef MTPS3D_FILEWRITER_H
#define MTPS3D_FILEWRITER_H

#include<string>
#include <iostream>
#include <fstream>
#include <ctime>
#include "mt.h"

class FileWriter {
private:
    std::string filename;
public:
    FileWriter(std::string fname);
    void writeParameters();
    void writeString(std::string note);
    void writeDouble(double data);
    void writeDoubleArray(double data[], int n_data);
    void writeIntArray(int data[], int n_data);

};



#endif //MTPS3D_FILEWRITER_H
