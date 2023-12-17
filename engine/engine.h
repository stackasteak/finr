#include <vector>
#include "../fhourstones.h"
#include <emscripten/emscripten.h>
#include <cmath>
#include <numeric>
#include <tuple>
#include <algorithm>

struct engineface{
  std::vector<float> p;
  int nx;
  int ny;
  bool running;
  bool refresh;

  engineface(int nx_, int ny_) : nx(nx_), ny(ny_){
    p.resize(nx_,0.0);
    running = false;
    refresh = false;
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


std::tuple<std::vector<int>, std::vector<float>> randrollout_policy(std::vector<int> hist, int nx, int ny, int maxcount){
  std::vector<float> ans(nx, 0.0);
  std::vector<int> pcounts(nx, 0);
  Game gg;
  for(int jj=0;jj<maxcount; jj++){
    
    //set up position
    gg.reset();
    for(int imove=0; imove< hist.size(); imove++){
      gg.makemove(hist[imove]);
    }

    int inimove=-1;
    for(int imove=0; imove<nx*ny; imove++){
        std::vector<int> plms;
        for(int kk=0; kk<nx; kk++){
          if(gg.isplayable(kk)){
            plms.push_back(kk);
          }
        }
        
        int kk1= int(floor(emscripten_random() * plms.size()));
        int kk2= plms[kk1];
        gg.makemove(kk2);
        if (imove==0) inimove=kk2;
        
        if(gg.nplies==nx*ny){
  int ii = pcounts[inimove];
          ans[inimove] = ans[inimove] * (ii/(ii+1.0)) + 0.5/(ii+1.0);
          //ans[inimove] = 0.5;
          pcounts[inimove] = pcounts[inimove]+1;
          break;
        }
        else if(gg.haswon(gg.color[0])){
  int ii = pcounts[inimove];
          ans[inimove] = ans[inimove] * (ii/(ii+1.0)) + 1.0/(ii+1.0);
          //ans[inimove] = 1.0;
          pcounts[inimove] = pcounts[inimove]+1;
          break;
        }
        else if(gg.haswon(gg.color[1])){
  int ii = pcounts[inimove];
          ans[inimove] = ans[inimove] * (ii/(ii+1.0)) + 0.0/(ii+1.0);
          //ans[inimove] = 0.0;
          pcounts[inimove] = pcounts[inimove]+1;
          break;
        }
    }
  }
  return std::make_tuple(pcounts,ans);
}

float randrollout_value(std::vector<int> hist, int nx, int ny, int maxcount){
  auto res = randrollout_policy(hist,nx,ny,maxcount);
  std::vector<float> p = std::get<1>(res);
  return std::reduce(p.begin(), p.end())/p.size();
}


template<class allStateType>
struct runrand1 {

  Game gg;
  int maxcount;
  std::vector<int> pcounts_tot;
  int nx;
  int ny;

  runrand1(int nx_, int ny_) : nx(nx_), ny(ny_){
    gg.reset();
    std::fill(pcounts_tot.begin(), pcounts_tot.end(), 0);
    maxcount=100;
  }
 
  void run(allStateType * asp){
    if(asp->esp->refresh){
      asp->esp->refresh = false;
        std::fill(pcounts_tot.begin(), pcounts_tot.end(), 0);
      for(int jj=0; jj<nx; jj++){
        asp->esp->p[jj] = 0.0;
      }
    }
    
    //set up position
    gg.reset();
    auto hist = asp->dsp->history;

    auto res = randrollout_policy(hist,nx,ny,maxcount);
    auto pcounts = std::get<0>(res);
    std::vector<float> ptemp = std::get<1>(res);
    
    for(int jj=0; jj<nx; jj++){
  if(pcounts[jj]>0){
      asp->esp->p[jj] = asp->esp->p[jj] * (pcounts_tot[jj]/(1.0*pcounts_tot[jj]+pcounts[jj])) + ptemp[jj] * pcounts[jj]/(1.0*pcounts_tot[jj]+pcounts[jj]);
      //asp->esp->p[jj] = ptemp[jj] ;
    pcounts_tot[jj] += pcounts[jj];
  }
    }
    //ncount_tot = ncount_tot + nn;
    
  }
};
