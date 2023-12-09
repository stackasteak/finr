#include <vector>
#include "fhourstones.h"


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


struct runrand {

  runrand(int i){}
 
  void run(drawingState * dsp, engineface * ef){
    for(int ii=0; ii < ef->nx; ii++){
       ef->p[ii]= (std::rand()%100)/100.0;
     }
  }
};
