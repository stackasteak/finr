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

  runrand1(int nx_, int ny_) : nx(nx_), ny(ny_){
    gg.reset();
    ncount =0;
    maxcount=100;
  }
 
  void run(allStateType * asp){
    for(int ii=0;ii<maxcount; ii++){
      gg.reset();
      for(int imove=0; imove< asp->dsp->history.size(); imove++){
        gg.makemove(asp->dsp->history[imove]);
      }

      for(int imove=0; imove<nx*ny; imove++){
        int jj ;
        std::vector<int> plms;
        for(int kk=0; kk<nx; kk++){
          if(gg.isplayable(kk)){
            plms.push_back(kk);
          }
        }
        int kk1= std::rand()%plms.size();
        int kk2= plms[kk1];
        gg.makemove(kk2);
        /*
        while(true){
          jj= std::rand()%nx;
          if(gg.isplayable(jj)){
            break;
          }
        }
        */
        //gg.makemove(jj);
        
        if(gg.nplies==nx*ny){
          ncount++;
          asp->esp->p[kk2] = asp->esp->p[kk2] * (ncount/(ncount+1)) + 0.5/(ncount+1);
          break;
        }
        else if(gg.haswon(gg.color[0])){
          ncount++;
          asp->esp->p[kk2] = asp->esp->p[kk2] * (ncount/(ncount+1)) + 0.0/(ncount+1);
          
          break;
        }
        else if(gg.haswon(gg.color[1])){
          ncount++;
          asp->esp->p[kk2] = asp->esp->p[kk2] * (ncount/(ncount+1)) + 1.0/(ncount+1);
          
          break;
        }
      }
    }
  }
};
