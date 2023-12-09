#include <vector>
#include "../fhourstones.h"
#include <emscripten/emscripten.h>


struct engineface{
  std::vector<float> p;
  int nx;
  int ny;
  bool running;

  engineface(int nx_, int ny_) : nx(nx_), ny(ny_){
    p.resize(nx_,0.0);
    running = false;
  }

  void resize(int nx_, int ny_) {
    nx =nx_;
    ny=ny_;
    p.resize(nx_,0.0);
  }


};

template<class allStateType>
struct runrand {

  runrand(int i){}
 
  void run(allStateType * asp){
    for(int ii=0; ii < asp->esp->nx; ii++){
       asp->esp->p[ii]= (std::rand()%100)/100.0;
     }
  }
};

template<class allStateType>
struct runrand1 {

  runrand1(int i){}
 
  void run(allStateType * asp){
    
  }
};
