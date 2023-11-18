#include <emscripten.h>
#include "Game.h"
#include <vector>

using namespace emscripten;

class engineState{
  std::vector<float> p;
  int nx;
  int ny;

public: 

  engineState(int nx_, int ny_) : nx(nx_), ny(ny_){
    p.resize(nx_,0.0);
  }

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

int main (){
  return 0;
}

