//
// Created by danie on 10-6-2020.
//

#include "vector.h"

// ADD 2 vectors
vector vector::operator+(vector v)
{
    int x1, y1, z1;
    x1 = x + v.x;
    y1 = y + v.y;
    z1 = z + v.z;
    return vector(x1, y1, z1);
}

// Subtract 2 vectors
vector vector::operator-(vector v)
{
    int x1, y1, z1;
    x1 = x - v.x;
    y1 = y - v.y;
    z1 = z - v.z;
    return vector(x1, y1, z1);
}

// Dot product of 2 vectors
int vector::operator^(vector v)
{
    int x1, y1, z1;
    x1 = x * v.x;
    y1 = y * v.y;
    z1 = z * v.z;
    return (x1 + y1 + z1);
}

// Cross product of 2 vectors
vector vector::operator*(vector v)
{
    int x1, y1, z1;
    x1 = y * v.z - z * v.y;
    y1 = z * v.x - x * v.z;
    z1 = x * v.y - y * v.x;
    return vector(x1, y1, z1);
}

