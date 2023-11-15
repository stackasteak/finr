#include <emscripten/bind.h>
#include "Game.h"
#include <vector>

using namespace emscripten;

struct engineState{
  std::vector<float> p;
  int nx;
  int ny;

  engineState(int nx_, int ny_) : nx(nx_), ny(ny_){
    p.resize(nx_,0.0);
  }

  float getP(int ii){
    return p[ii];
  }

};


EMSCRIPTEN_BINDINGS(engine_module) {

  class_<engineState>("engineState")
    .constructor<int>()
    .function("getP", &engineState::getP);
    
  // register bindings for std::vector<int> and std::map<int, std::string>.
  //register_vector<float>("vector<float>");

}
