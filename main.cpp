
#include <iostream>
//#include "vector.h"
#include "mt.h"

// calculate shortest dist. from point to line
double shortDistance(vector line_point1, vector line_point2, vector point)
{
    vector AB = line_point2 - line_point1;
    vector AC = point - line_point1;
    double area = vector(AB * AC).magnitude();
    double CD = area / AB.magnitude();
    return CD;
}

double polarity(mt* MTS){
    double length[2] = {0, 0};
    for(int i = 0; i < N_MICROTUBULES; i++){
        length[MTS[i].get_side()] += MTS[i].get_length();
    }
    return (length[RIGHT]-length[LEFT])/(length[RIGHT]+length[LEFT]);
}

double lengths(mt* MTS){
    double length = 0;
    for(int i = 0; i < N_MICROTUBULES; i++){
        length += MTS[i].get_length();
    }
    return length/N_MICROTUBULES;
}

int main()
{

    //create MTS
    mt mitus[N_MICROTUBULES];
    for(int i = 0; i < N_MICROTUBULES; i++){
        mitus[i] = mt();
    }

    //run timesteps
    for(int t = 0; t < (int) T_MAX*T_STEP; t++){
        if (t%1000 == 0){
            std::cout << polarity(mitus) << "\n";
            std::cout << lengths(mitus) << "\n";
        }
        for(int i = 0; i < N_MICROTUBULES; i++){
            mitus[i].stochastic_state_change();
        }

        for(int i = 0; i < N_MICROTUBULES; i++){
            mitus[i].grow_shrink(T_STEP);
        }

        for(int i = 0; i < N_MICROTUBULES; i++){
            if(mitus[i].get_state() != GROWING) continue;
            for(int j = 0; j < N_MICROTUBULES; j++){
                if(mitus[i].get_side() == mitus[j].get_side()) continue;
                if(shortDistance(mitus[j].get_pos(), mitus[j].get_end(), mitus[i].get_end()) < BIND_DISTANCE){
                    mitus[i].set_host(j);
                    mitus[i].set_state(BOUND);
                    //std::cout << shortDistance(mitus[j].get_pos(), mitus[j].get_end(), mitus[i].get_end()) << " bound\n";
                    break;
                }
            }

        }


    }
    return 0;
}