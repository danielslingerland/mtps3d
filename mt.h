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
    int host;
    void reset();

public:
    mt();
    void grow_shrink(double delta);
    int get_state();
    void set_state(int s);
    vector get_pos();
    vector get_end();
    int get_side();
    int get_host();
    double get_length();
    void set_host(int h);
    void stochastic_state_change();
};


#endif //MTPS3D_MT_H
