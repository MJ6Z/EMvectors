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

#include "calculation.h"

int main(){

    //Visual model setup
    morph::Visual v(1024, 768, "E.P around point charge(s)");
    morph::vec<float, 3> offset = { 0.0, 0.0, 0.0 };
    v.showCoordArrows = true;
    v.showTitle = true;
    v.backgroundBlack();
    v.lightingEffects();

    //size of the grid of quivers
    int size = 14;
    int halfsize = size/2;


    //All of this will be moved into the electroStatics clas im just lazy as fuck.



    std::vector<morph::vec<float, 3>> B(size*size*size); //Magnetic field.
    std::vector<morph::vec<float, 3>> E(size*size*size); //Electric field.
    std::vector<morph::vec<float, 3>> coords(size*size*size);

    morph::vec<int, 3> point1= {0,0,0};
    float q1 = 1;
    morph::vec<int, 3> point2= {4,0,0};
    float q2 = 1;


//instantiate electroStatics class as object "particle" for making calculations.
electroStatics particle;

    //iterator.
    size_t a = 0;

    for (int i = -halfsize; i < halfsize; ++i) {
        for (int j = -halfsize; j < halfsize; ++j) {
            for (int k = -halfsize; k < halfsize; ++k) {

                float x = 0.1*i;
                float y = 0.1*j;
                float z = 0.1*k;

                morph::vec<float, 3> val = particle.pointcharge(i,j,k, q1, point1);
                val = val + particle.pointcharge(i,j,k, q2, point2);

                coords[a]={x,y,z};
                B[a] = val;


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
