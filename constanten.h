//
// Created by danie on 10-6-2020.
//

#ifndef MTPS3D_CONSTANTEN_H
#define MTPS3D_CONSTANTEN_H

//Values from Xavi Fernandez-Luengo Flores MSc Thesis (Table 4.11)
//T : seconds (s)
#define T_STEP 0.1
#define N_MICROTUBULES 1000
//R : per second (s^-1)
#define R_CATASTROPHE 0.005
#define R_RESCUE 0.0068
#define R_UNBIND 0.1
//V : micrometer per second (um/s)
#define V_GROW 0.08
#define V_SHRINK 0.16
//P: probability
#define P_RIGHT 0.5

#define T_MAX 10000

//daniel:
#define HOST_PENALTY_FACTOR 1
#define BIND_DISTANCE 5

#define X_MAX 10000
#define Y_MAX 100000
#define Z_MAX 10000
enum{X, Y, Z};
enum{GROWING, SHRINKING, BOUND};
enum{RIGHT, LEFT};

#endif //MTPS3D_CONSTANTEN_H
