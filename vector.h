

#ifndef MTPS3D_VECTOR_H
#define MTPS3D_VECTOR_H


#include <cmath>
#include <ostream>

class vector {
private:
    double x, y, z;
    // 3D Coordinates of the Vector

public:
    vector(){
        x = 0.0;
        y = 0.0;
        z = 0.0;
    }
    vector(double x, double y, double z)
    {
        // Constructor
        this->x = x;
        this->y = y;
        this->z = z;
    }
    vector operator+(vector v); // ADD 2 Vectors
    vector operator-(vector v); // Subtraction
    int operator^(vector v); // Dot Product
    vector operator*(vector v); // Cross Product
    vector operator*(double d); // Product
    double magnitude()
    {
        return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
    }
    friend std::ostream& operator<<(std::ostream& out, const vector& v);
    // To output the Vector
};


#endif //MTPS3D_VECTOR_H
