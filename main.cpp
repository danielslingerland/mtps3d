
#include <iostream>
#include "vector.h"

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

    return 0;
}