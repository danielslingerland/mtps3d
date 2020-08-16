
#include <iostream>
//#include "vector.h"
#include "mt.h"
#include "FileWriter.h"

mt mitus[N_MICROTUBULES];
double X_MAX = 100;
double Y_MAX = 100;
double Z_MAX = 100;

// calculate shortest dist. from point to line
double shortDistance(vector line_point1, vector line_point2, vector point) {
    vector AB = line_point2 - line_point1;
    vector BC = point - line_point2;
    vector AC = point - line_point1;

    if ((AB ^ BC) > 0.0) return (point - line_point2).magnitude();
    if ((AB ^ AC) < 0.0) return (point - line_point1).magnitude();
    double area = vector(AB * AC).magnitude();
    double CD = area / AB.magnitude();
    return CD;
}

// dist3D_Line_to_Line(): get the 3D minimum distance between 2 lines
//    Input:  two 3D lines L1 and L2
//    Return: the shortest distance between L1 and L2
double dist3D_Line_to_Line(vector l1p1, vector l1p2, vector l2p1, vector l2p2) {
    vector u = l1p2 - l1p1;
    vector v = l2p2 - l2p1;
    vector w = l1p1 - l1p1;
    double a = (u ^ u);         // always >= 0
    double b = (u ^ v);
    double c = (v ^ v);         // always >= 0
    double d = (u ^ w);
    double e = (v ^ w);
    double D = a * c - b * b;        // always >= 0
    double sc, tc;

    // compute the line parameters of the two closest points
    if (D == 0) {          // the lines are almost parallel
        sc = 0.0;
        tc = (b > c ? d / b : e / c);    // use the largest denominator
    } else {
        sc = (b * e - c * d) / D;
        tc = (a * e - b * d) / D;
    }

    // get the difference of the two closest points
    vector dP = w + (u * sc) - (v * tc);  // =  L1(sc) - L2(tc)

    return dP.magnitude();   // return the closest distance
}

double polarity(mt *MTS) {
    double length[2] = {0, 0};
    for (int i = 0; i < N_MICROTUBULES; i++) {
        length[MTS[i].get_side()] += MTS[i].get_length();
    }
    return (length[RIGHT] - length[LEFT]) / (length[RIGHT] + length[LEFT]);
}

double lengths(mt *MTS) {
    double length = 0;
    for (int i = 0; i < N_MICROTUBULES; i++) {
        length += MTS[i].get_length();
    }
    return length / N_MICROTUBULES;
}

void reset_reachable(int changed){
    vector changed1 = mitus[changed].get_pos();
    vector changed2 = mitus[changed].get_dir()*changed1;

    for(int i = 0; i < N_MICROTUBULES; i++){
        if(mitus[changed].get_side() == mitus[i].get_side() or dist3D_Line_to_Line(changed1, changed2, mitus[i].get_pos(), mitus[i].get_end()) > BIND_DISTANCE){
            mitus[i].reachable[changed] = false;
        }else{
            mitus[i].reachable[changed] = true;
        }
    }

}

int main() {
    for(int z = 0; z < 10; z++) {
    for(int y = 0; y < 10; y++) {
    for(int x = 0; x < 10; x++) {
        X_MAX = 50*x;
        Y_MAX = 50*y;
        Z_MAX = 50*z;
        int n_bins = 301;
        int bins[n_bins];
        for (int b = 0; b < n_bins; b++) {
            bins[b] = 0;
        }
        //create MTS
        for (int i = 0; i < N_MICROTUBULES; i++) {
            mitus[i] = mt(X_MAX, Y_MAX, Z_MAX);

            mitus[i].grow_shrink(T_STEP);
        }
        for (int i = 0; i < N_MICROTUBULES; i++) {

            reset_reachable(i);
        }
        FileWriter pol = FileWriter("polarity");
        pol.writeParameters(X_MAX, Y_MAX, Z_MAX);




        //run timesteps
        for (int t = 0; t < (int) T_MAX * T_STEP; t++) {


//        if (t%incubation_time == 0){
//            std::cout << polarity(mitus) << "\n";
//            std::cout << lengths(mitus) << "\n";
//        }


            for (int i = 0; i < N_MICROTUBULES; i++) {
                mitus[i].stochastic_state_change();
            }

            for (int i = 0; i < N_MICROTUBULES; i++) {
                //bool mt_reset = mitus[i].grow_shrink(T_STEP);
                mitus[i].grow_shrink(T_STEP);
                //if (mt_reset) {
                //    reset_reachable(i);
                //}
            }

            for (int i = 0; i < N_MICROTUBULES; i++) {
                if (mitus[i].get_state() == GROWING) {
                    double closest_distance = BIND_DISTANCE;
                    for (int j = 0; j < N_MICROTUBULES; j++) {
                        //if (mitus[i].reachable[j] == false) continue;
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
                } else if (mitus[i].get_state() == BOUND) {
                    if (mitus[mitus[i].get_host()].get_length() < mitus[i].get_bind_pos()) {
                        mitus[i].set_state(SHRINKING);
                        mitus[mitus[i].get_host()].min_guest();
                        mitus[i].set_host(-1);

                    }
                }

            }
            bins[(int) ((polarity(mitus) + 1) * 0.5 * n_bins)]++;


        }
        FileWriter mts = FileWriter("end");
        mts.writeParameters(X_MAX, Y_MAX, Z_MAX);
        for (int i = 0; i < N_MICROTUBULES; i++) {
            mts.writeDouble(mitus[i].get_end().x); //0
            mts.writeDouble(mitus[i].get_end().y); //1
            mts.writeDouble(mitus[i].get_end().z); //2
            mts.writeDouble(mitus[i].get_pos().x); //3
            mts.writeDouble(mitus[i].get_pos().y); //4
            mts.writeDouble(mitus[i].get_pos().z); //5
            mts.writeDouble(mitus[i].get_dir().x); //6
            mts.writeDouble(mitus[i].get_dir().y); //7
            mts.writeDouble(mitus[i].get_dir().z); //8
            mts.writeDouble(mitus[i].get_length()); //9
        }
        pol.writeIntArray(bins, n_bins);
    }}}
    return 0;
}