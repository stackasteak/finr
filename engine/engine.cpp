#include <emscripten.h>
#include "Game.h"
#include <vector>


struct engineState{
  std::vector<float> p;
  int nx;
  int ny;
  engineState(int nx_, int ny_) : nx(nx_), ny(ny_){
    p.resize(nx_,0.0);
  }

};

engineState es(9,9);

extern "C" {

EMSCRIPTEN_KEEPALIVE
void resize(int nx_, int ny_) {
    nx =nx_;
    ny=ny_;
    p.resize(nx_,0.0);
  }

  void resize0(){}

  void batch(){
    for(int ii=0; ii<nx; ii++){
      p[ii]= std::rand();
    }
  }

  float getP(int ii){
    return p[ii];
  }

  int getNX(){return nx;}

  int getNY(){return ny;}

};


EMSCRIPTEN_BINDINGS(engine_module) {

  class_<engineState>("engineState")
    .constructor<int,int>()
    .function("resize0", &engineState::resize0)
    .function("batch", &engineState::batch)
    .function("getNX", &engineState::getNX)
    .function("getNY", &engineState::getNY)
    .function("resize", &engineState::resize)
    .function("getP", &engineState::getP);
    
  // register bindings for std::vector<int> and std::map<int, std::string>.
  //register_vector<float>("vector<float>");

}
