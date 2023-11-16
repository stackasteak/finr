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
  es.nx =nx_;
  es.ny=ny_;
  es.p.resize(nx_,0.0);
}

EMSCRIPTEN_KEEPALIVE
void batch(){
  for(int ii=0; ii<nx; ii++){
    es.p[ii]= std::rand();
  }
}

EMSCRIPTEN_KEEPALIVE
float getP(int ii){
  return es.p[ii];
}

EMSCRIPTEN_KEEPALIVE  
int getNX(){return es.nx;}

EMSCRIPTEN_KEEPALIVE
int getNY(){return es.ny;}

}


