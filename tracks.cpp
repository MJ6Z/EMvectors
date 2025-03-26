/*
    Simulate particle tracks using morph::quiverVisual
*/

//standard library includes.
#include <iostream>
#include <array>
#include <stdexcept>
#include <string>

//morphologica includes.
#include <morph/Visual.h>
#include <morph/ColourMap.h>
#include <morph/QuiverVisual.h>
#include <morph/vec.h>

#include <morph/tools.h>
#include <morph/Config.h> //json read-writer

// calculation header file.
#include "calculation.h"


int main(int argc, char **argv){

    //throw error if user does not supply JSON file.
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " /path/to/params.json" << std::endl;
        return 1;
    }
    std::string paramsfile (argv[1]);

    //Set up morph::Config JSON reader/writer for reading the parameters
    //Return error if this fails.
    morph::Config conf(paramsfile);
    if (!conf.ready) {
        return 1;
    }

    //get position and magnitude data about point charges from params.json
    morph::vvec<int> point_xcoord = conf.getvvec<int>("pointchargex");
    morph::vvec<int> point_ycoord = conf.getvvec<int>("pointchargey");
    morph::vvec<int> point_zcoord = conf.getvvec<int>("pointchargez");
    morph::vvec<int> point_q = conf.getvvec<int>("pointchargeq");

    //check there are no incomplete coordinates.
    if( point_xcoord.size() != point_ycoord.size() &&
        point_ycoord.size() != point_zcoord.size() &&
        point_zcoord.size() != point_q.size()){
        std::cerr<<"Ensure point positions & magnitudes are complete in paramsfile" <<std::endl;
        return 1;
    }


    //Visual model setup
    morph::Visual v(1024, 768, "E.P around point charge(s)");
    morph::vec<float, 3> offset = { 0.0, 0.0, 0.0 };
    v.showCoordArrows = true;
    v.showTitle = true;
    v.backgroundBlack();
    v.lightingEffects();

    //size of the grid of quivers
    int size = conf.getInt("size",10);
    int halfsize = size/2;


    //All of this will be moved into the electroStatics clas im just lazy as fuck.



    std::vector<morph::vec<float, 3>> E(size*size*size); //Electric field.
    std::vector<morph::vec<float, 3>> coords(size*size*size);


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

                morph::vec<float, 3> val = {0,0,0};
                for(int l = 0; l < point_xcoord.size(); ++l){
                    val = val + particle.pointcharge(i,j,k,point_q[l],{point_xcoord[l],point_ycoord[l],point_zcoord[l],});
                }

                coords[a]={x,y,z};
                E[a] = val;


                a++;
            }
        }
    }


    //Add the B field to the visualization.
    auto vmp = std::make_unique<morph::QuiverVisual<float>>(&coords, offset, &E, morph::ColourMapType::MonochromeRed); //coordinates of the arrows, offset, arrows.
    v.bindmodel (vmp);
    vmp->quiver_length_gain = 0.2f;
    vmp->quiver_thickness_gain = 0.02f;
    vmp->shapesides = 12;

    vmp->finalize();
    v.addVisualModel (vmp);

    v.keepOpen();




    return 0;
}
