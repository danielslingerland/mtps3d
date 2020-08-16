//
// Created by danie on 10-6-2020.
//

#include "mt.h"

mt::mt(){}
mt::mt(double x, double y, double z){
    X_MAX = x;
    Y_MAX = y;
    Z_MAX = z;
    reset();
}

bool mt::grow_shrink(double delta){
    if(state == GROWING){

        vector new_end = end+dir*(delta*V_GROW);
        //if(new_end.x < X_MAX and new_end.x > 0 and new_end.y < Y_MAX and new_end.y > 0 and new_end.z < Z_MAX and new_end.z > 0) {
            length += delta*V_GROW;
            end = new_end;
        //}

    }else if(state == SHRINKING){
        length -= delta*V_SHRINK;
        if(length > 0){
            end = end-dir*(delta*V_GROW);
        }else{
            reset();
            return true;
        }

    }
    return false;

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
    n_guests = 0;
    length = 0.0;
    host = -1;
    state = GROWING;
    double x = dasl::mt_rng()*X_MAX;
    double y = dasl::mt_rng()*Y_MAX;
    double z = dasl::mt_rng()*Z_MAX;
    pos = vector(x, y, z);
    double angle = dasl::norm_rng()*(1.0/6.0)*M_PI;
    double derec = dasl::mt_rng()*2.0*M_PI;

    if(dasl::mt_rng() > P_RIGHT){
        angle += M_PI;
    }
    double abs_angle = abs(angle+0.5*M_PI);
    while(abs_angle-2*M_PI > 0){
        abs_angle -= 2*M_PI;
    }
    if(abs_angle < M_PI){
        side = RIGHT;
    }else{
        side = LEFT;
    }

    x = cos(angle);
    y = cos(derec)*sin(angle);
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

vector mt::get_dir(){
    return dir;
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
double mt::get_bind_pos() {
    return bind_pos;
}
void mt::set_bind_pos(double bp){
    bind_pos = bp;
}
void mt::add_guest() {
    n_guests += 1;
}
void mt::min_guest(){
    n_guests -= 1;
}

void mt::set_side(int s){
    side = s;

}