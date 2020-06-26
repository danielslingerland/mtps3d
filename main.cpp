
#include <iostream>
//#include "vector.h"
#include "mt.h"
#include "FileWriter.h"

// calculate shortest dist. from point to line
double shortDistance(vector line_point1, vector line_point2, vector point)
{
    vector AB = line_point2 - line_point1;
    vector BC = point - line_point2;
    vector AC = point - line_point1;

    if((AB^BC) > 0.0) return (point-line_point2).magnitude();
    if((AB^AC) < 0.0) return (point-line_point1).magnitude();
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
    FileWriter state = FileWriter("state");
    FileWriter side = FileWriter("side");
    FileWriter length = FileWriter("length");
    state.writeParameters();
    side.writeParameters();
    length.writeParameters();

    int incubation_time = 1000000;
    int states[1000];
    int sides[1000];
    double lengthss[1000];
    int k = 0;
    //run timesteps
    for(int t = 0; t < (int) T_MAX*T_STEP; t++){
        if (t%incubation_time == 0){
            std::cout << polarity(mitus) << "\n";
            std::cout << lengths(mitus) << "\n";
        }
        if (t > incubation_time){
            if( k >= 1000){
                state.writeIntArray(states, 1000);
                side.writeIntArray(sides, 1000);
                length.writeDoubleArray(lengthss, 1000);
                k=0;
            }
            sides[k] = mitus[0].get_side();
            states[k] = mitus[0].get_state();
            lengthss[k] = mitus[0].get_length();
            k++;
        }
        for(int i = 0; i < N_MICROTUBULES; i++){
            mitus[i].stochastic_state_change();
        }

        for(int i = 0; i < N_MICROTUBULES; i++){
            mitus[i].grow_shrink(T_STEP);
        }

        for(int i = 0; i < N_MICROTUBULES; i++){
            if(mitus[i].get_state() == GROWING) {
                double closest_distance = BIND_DISTANCE;
                for (int j = 0; j < N_MICROTUBULES; j++) {
                    if (mitus[i].get_side() == mitus[j].get_side()) continue;
                    double distance = shortDistance(mitus[j].get_pos(), mitus[j].get_end(), mitus[i].get_end());
                    if (distance < BIND_DISTANCE && distance < closest_distance) {
                        closest_distance = distance;
                        double bind_pos = sqrt(pow((mitus[i].get_end() - mitus[j].get_pos()).magnitude(), 2) -
                                               pow(closest_distance, 2));
                        mitus[i].set_bind_pos(bind_pos);
                        mitus[i].set_host(j);
                        mitus[i].set_state(BOUND);
                        mitus[j].add_guest();

                    }
                }
            }else if(mitus[i].get_state() == BOUND){
                if(mitus[mitus[i].get_host()].get_length() < mitus[i].get_bind_pos()){
                    mitus[i].set_state(SHRINKING);
                    mitus[i].set_host(-1);
                    mitus[mitus[i].get_host()].min_guest();
                }
            }

        }


    }

    return 0;
}