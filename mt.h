//
// Created by danie on 10-6-2020.
//

#ifndef MTPS3D_MT_H
#define MTPS3D_MT_H


#include "vector.h"
#include "RNG.h"
#include "constanten.h"
#include <math.h>
class mt {
private:
    vector pos;
    vector end;
    vector dir;
    double length;
    int state;
    int side;

public:
    mt();

};


#endif //MTPS3D_MT_H
