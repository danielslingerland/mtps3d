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
    double bind_pos{};
    int n_guests;
    double X_MAX;
    double Y_MAX;
    double Z_MAX;

    void reset();

public:
    mt();
    mt(double x, double y, double z);
    bool grow_shrink(double delta);
    int get_state();
    void set_state(int s);
    vector get_pos();
    vector get_end();
    vector get_dir();
    int get_side();
    void set_side(int s);
    int get_host();
    double get_length();
    void set_host(int h);
    void stochastic_state_change();
    double get_bind_pos();
    void set_bind_pos(double bp);
    void add_guest();
    void min_guest();
    bool reachable[N_MICROTUBULES];
};


#endif //MTPS3D_MT_H
