/*
    Simulate particle tracks using morph::quiverVisual
*/

#include <morph/Visual.h>
#include <morph/ColourMap.h>
#include <morph/QuiverVisual.h>
#include <morph/vec.h>
#include <iostream>
#include <array>
#include <stdexcept>
#include <string>

constexpr double C = 299792458.0; // Speed of light in meters per second (m/s)
constexpr double q_e = -1.602176634e-19; // Electron charge in coulombs (C)
constexpr double mass_e = 9.1093837e-31; //(Invarient/restElectron mass (cannot name variable m_e.)

int main(){

    //Visual model setup
    morph::Visual v(1024, 768, "morph::QuiverVisual");
    morph::vec<float, 3> offset = { 0.0, 0.0, 0.0 };
    v.showCoordArrows = true;
    v.showTitle = true;
    v.backgroundBlack();
    v.lightingEffects();

    //size of the grid of quivers
    int size = 100;
    int halfsize = size/2;

    std::vector<morph::vec<float, 3>> B(size*size*size);
    std::vector<morph::vec<float, 3>> coords(size*size*size);
    float rx=0.0;
    float ry=0.0;
    float rz=0.0;
    morph::vec<float, 3> _v = {10,0,0};

    //iterator.
    size_t a = 0;
    for (int i = 0; i < size; ++i) {
        for (int j = -halfsize; j < halfsize; ++j) {
            for (int k = -halfsize; k < halfsize; ++k) {
                float x = 0.1*i;
                float y = 0.1*j;
                float z = 0.1*k;

                B[a]={0,0,1}; // B field on {x,y,z}.

                a++;
            }
        }
    }




    return 0;
}
