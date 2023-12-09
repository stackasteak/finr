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

  Game gg;
  int ncount;
  int maxcount;
  int nx;
  int ny;

  runrand1(int i){
    gg.reset();
    ncount =0;
    maxcount=100;
  }
 
  void run(allStateType * asp){
    for(int ii=0;ii<maxcount; ii++){
      for(int imove=0; imove< asp->dsp->history.size(); imove++){
        gg.makemove(asp->dsp->history[imove]);
      }

      for(int imove=0; imove<
  }
};
