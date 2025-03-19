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


constexpr double pi = 3.14159265359; //pi
constexpr double C = 299792458.0; // Speed of light in meters per second (m/s)
constexpr double q_e = -1.602176634e-19; // Electron charge in coulombs (C)
constexpr double mass_e = 9.1093837e-31; //(Invarient/rest Electron mass (cannot name variable m_e.)
constexpr double epsilon_zero = 8.8541878188e-12; //Permitivity of free space.
constexpr double electric_coeff = 8.98755179e9; //1/(4*pi*e_0)

int main(){

    //Visual model setup
    morph::Visual v(1024, 768, "morph::QuiverVisual");
    morph::vec<float, 3> offset = { 0.0, 0.0, 0.0 };
    v.showCoordArrows = true;
    v.showTitle = true;
    v.backgroundBlack();
    v.lightingEffects();

    //size of the grid of quivers
    int size = 20;
    int halfsize = size/2;

    std::vector<morph::vec<float, 3>> B(size*size*size); //Magnetic field.
    std::vector<morph::vec<float, 3>> E(size*size*size);
    std::vector<morph::vec<float, 3>> coords(size*size*size);
/*
    morph::vec<float, 3> r = {0,0,0};
    morph::vec<float, 3> drdt = {0,0,0};
    morph::vec<float, 3> d2rdt2 = {0,0,0};
*/

    //iterator.
    size_t a = 0;
    for (int i = -halfsize; i < halfsize; ++i) {
        for (int j = -halfsize; j < halfsize; ++j) {
            for (int k = -halfsize; k < halfsize; ++k) {

                float x = 0.1*i-0.5;
                float y = 0.1*j;
                float z = 0.1*k;

                //distance from 0,0,0
                float d = std::sqrt(x*x + y*y + z*z);

                //unit vector calculations
                float xhat = x/std::abs(x);
                float yhat = y/std::abs(y);
                float zhat = z/std::abs(z);

                if(i == 5){xhat = 0;}
                if(j == 0){yhat = 0;}
                if(k == 0){zhat = 0;}


                coords[a]={x,y,z};
                B[a]={xhat*(1/d),yhat*(1/d),zhat*(1/d)}; // field on {x,y,z}, currently simulating a single point charge on {0,0,0}


                a++;
            }
        }
    }


    //Add the B field to the visualization.
    auto vmp = std::make_unique<morph::QuiverVisual<float>>(&coords, offset, &B, morph::ColourMapType::MonochromeRed); //coordinates of the arrows, offset, arrows.
    v.bindmodel (vmp);
    vmp->quiver_length_gain = 0.2f;
    vmp->quiver_thickness_gain = 0.02f;
    vmp->shapesides = 12;

    vmp->finalize();
    v.addVisualModel (vmp);

    v.keepOpen();




    return 0;
}
