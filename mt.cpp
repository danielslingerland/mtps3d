//
// Created by danie on 10-6-2020.
//

#include "mt.h"


mt::mt(){
    reset();
}

void mt::grow_shrink(double delta){
    if(state == GROWING){
        length += delta*V_GROW;
        end = end+dir*(delta*V_GROW);

    }else if(state == SHRINKING){
        length -= delta*V_SHRINK;
        if(length > 0){
            end = end-dir*(delta*V_GROW);
        }else{
            reset();
        }

    }

}

void mt::stochastic_state_change(){
    double rand = dasl::mt_rng();
    if(state == GROWING){
        if(rand < P_CATASTROPHE){
            state = SHRINKING;
        }
    }else if(state == SHRINKING){
        if(rand < P_RESCUE){
            state = GROWING;
        }

    }else if(state == BOUND){
        if(rand < P_UNBIND){
            state = SHRINKING;
            host = -1;
        }

    }

}

void mt::reset(){
    length = 0.0;
    host = -1;
    state = GROWING;
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

int mt::get_state(){
    return state;
}
void mt::set_state(int s){
    state = s;
}

vector mt::get_pos(){
    return pos;
}
vector mt::get_end(){
    return end;
}
int mt::get_side(){
    return side;
}
int mt::get_host(){
    return host;
}
void mt::set_host(int h) {
    host = h;
}
double mt::get_length(){
    return length;
}