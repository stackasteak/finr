#include <vector>


struct engineface{
  std::vector<float> p;
  int nx;
  int ny;
  bool running;

  baseEngine(int nx_, int ny_, runType rr_) : nx(nx_), ny(ny_), rr(rr_){
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
 
  void run(engineface * ef){
    for(int ii=0; ii < ef->nx; ii++){
       ef->p[ii]= (std::rand()%100)/100.0;
     }
  }
};
