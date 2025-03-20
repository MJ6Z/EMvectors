
#include <morph/vec.h>
#include <iostream>
#include <array>
#include <stdexcept>
#include <cmath>
#include <string>

morph::vec<float,3> pointcharge(int i, int j, int k, morph::vec<int, 3> point){


    float x = 0.1*i-0.1*point[0];
    float y = 0.1*j-0.1*point[1];
    float z = 0.1*k-0.1*point[2];

    float d = std::sqrt(x*x + y*y + z*z);


    float xhat = x/std::abs(x);
    float yhat = y/std::abs(y);
    float zhat = z/std::abs(z);
    if(i == point[0]){xhat = 0;}
    if(j == point[1]){yhat = 0;}
    if(k == point[2]){zhat = 0;}

    morph::vec<float,3> result = {xhat*(1/d),yhat*(1/d),zhat*(1/d)};

    return result;
}
