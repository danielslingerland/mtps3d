
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

int main()
{
    // Taking point C as (2, 2, 2)
    // Line Passes through A(4, 2, 1)
    // and B(8, 4, 2).
    vector line_point1(4, 2, 1), line_point2(8, 4, 2);
    vector point(2, 2, 2);

    std::cout << "Shortest Distance is : " << shortDistance(line_point1, line_point2, point);

    //create MTS
    mt mitus[N_MICROTUBULES];
    for(int i = 0; i < N_MICROTUBULES; i++){
        mitus[i] = mt();
    }

    //run timesteps
    for(int t = 0; t < (int) T_MAX*T_STEP; t++){

        for(int i = 0; i < N_MICROTUBULES; i++){
            mitus[i].grow_shrink(T_STEP);
        }

        for(int i = 0; i < N_MICROTUBULES; i++){
            if(mitus[i].get_state() != GROWING) continue;
            for(int j = 0; j < N_MICROTUBULES; j++){
                if(shortDistance(mitus[j].get_pos(), mitus[j].get_end(), mitus[i].get_end()) < BIND_DISTANCE){
                    mitus[i].set_host(j);
                    mitus[i].set_state(BOUND);
                    std::cout << "bound\n";
                    break;
                }
            }

        }


    }
    return 0;
}