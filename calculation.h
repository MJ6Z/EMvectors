
#include <morph/vec.h>
#include <iostream>
#include <array>
#include <stdexcept>
#include <cmath>
#include <string>

constexpr double pi = 3.14159265359; //pi
constexpr double C = 299792458.0; // Speed of light in meters per second (m/s)
constexpr double q_e = -1.602176634e-19; // Electron charge in coulombs (C)
constexpr double mass_e = 9.1093837e-31; //(Invarient/rest Electron mass (cannot name variable m_e.)
constexpr double epsilon_zero = 8.8541878188e-12; //Permitivity of free space.
constexpr double k = 8.98755179e9; //1/(4*pi*e_0)

class electroStatics {

public:
morph::vvec<morph::vec<float, 3>> pointCharge(int size, float q, morph::vec<int, 3> point){

    int halfsize = size/2;
    morph::vvec<morph::vec<float, 3>> result(size*size*size);

    size_t a = 0;
    for (int i = -halfsize; i < halfsize; ++i) {
        for (int j = -halfsize; j < halfsize; ++j) {
            for (int k = -halfsize; k < halfsize; ++k) {

                float x = 0.1*(i-point[0]); //let the centre of x,y,z be the point.
                float y = 0.1*(j-point[1]);
                float z = 0.1*(k-point[2]);

                float d = std::sqrt(x*x + y*y + z*z); //magnitude of the distance from the point.

                float xhat = x/std::abs(x); //unit vectors. Important for the direction of EP arrows.
                float yhat = y/std::abs(y);
                float zhat = z/std::abs(z);

                if(i == point[0]){xhat = 0;} //avoid infinite magnitudes if |x| = 0.
                if(j == point[1]){yhat = 0;}
                if(k == point[2]){zhat = 0;}

                result[a++] = {q*xhat*(1/d),q*yhat*(1/d),q*zhat*(1/d)}; //E=q*electric_coeff*1/d

                }
            }
        }
    return result;
    };
};
