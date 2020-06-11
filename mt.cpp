//
// Created by danie on 10-6-2020.
//

#include "mt.h"


mt::mt(){

    double x = dasl::mt_rng()*X_MAX;
    double y = dasl::mt_rng()*Y_MAX;
    double z = dasl::mt_rng()*Z_MAX;
    pos = vector(x, y, z);
    double angle = dasl::norm_rng()*(1/6)*M_PI;
    double derec = dasl::mt_rng()*2*M_PI;

    if(dasl::mt_rng() > 0.5){
        side = RIGHT;
    }else{
        side = LEFT;
        angle += M_PI;
    }

    x = cos(derec)*sin(angle);
    y = cos(angle);
    z = sin(derec)*sin(angle);
    dir = vector(x, y, z);
    end = pos;

}