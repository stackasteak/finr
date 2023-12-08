#include <vector>

struct baseEngine{
  std::vector<float> p;
  int nx;
  int ny;
  bool running;

  baseEngine(int nx_, int ny_) : nx(nx_), ny(ny_){
    p.resize(nx_,0.0);
    running = false;
  }

  void resize(int nx_, int ny_) {
    nx =nx_;
    ny=ny_;
    p.resize(nx_,0.0);
  }

  void run(){}


};


struct randEngine : public baseEngine{

  randEngine(int nx_, int ny_) : baseEngine(nx,ny) {};
 
  void run(){
    for(int ii=0; ii <nx; ii++){
       p[ii]= (std::rand()%100)/100.0;
     }
  }
};
