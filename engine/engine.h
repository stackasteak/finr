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


struct runrand {

  runrand(int i){}
 
  std::vector<float> run(std::vector<int> hh, int nx, int ny){
    std::vector<float> ans(nx,0.0);
    for(int ii=0; ii < nx; ii++){
       ans[ii]= (std::rand()%100)/100.0;
     }
    return ans;
  }
};


std::tuple<std::vector<int>, std::vector<float>> randrollout_policy(Game gg0, int nx, int ny, int maxcount){
  std::vector<float> ans(nx, 0.0);
  std::vector<int> pcounts(nx, 0);
  
  for(int jj=0;jj<maxcount; jj++){
    Game gg=gg0;

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

float randrollout_value(Game gg, int nx, int ny, int maxcount){
  auto res = randrollout_policy(gg,nx,ny,maxcount);
  std::vector<float> p = std::get<1>(res);
  return std::reduce(p.begin(), p.end())/p.size();
}

struct randrollout{
  int maxcount;
  randrollout(int mc) : maxcount(mc) {};
  float operator()(Game gg0, int nx, int ny){
  float ans =0.0;
for(int ii=0;ii<maxcount; ii++){
    Game gg=gg0;

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
        
        if(gg.nplies==nx*ny){
 
  ans = ans * (ii/(ii+1.0)) + 0.5/(ii+1.0);
          //ans[inimove] = 0.5;
        
          break;
        }
        else if(gg.haswon(gg.color[0])){
    ans = ans* (ii/(ii+1.0)) + 1.0/(ii+1.0);
          //ans[inimove] = 1.0;
          break;
        }
        else if(gg.haswon(gg.color[1])){
    ans = ans* (ii/(ii+1.0)) + 0.0/(ii+1.0);
          //ans[inimove] = 0.0;
          break;
        }
    }
  }
  return ans;
}
};


struct lookrollout{
  int maxcount;
  lookrollout(int mc) : maxcount(mc) {};
  float operator()(Game gg0, int nx, int ny){
float ans =0.0;
/*
for(int ii=0;ii<maxcount; ii++){
    Game gg=gg0;

    for(int imove=0; imove<nx*ny; imove++){
int pl = (gg.nplies)%2;
int pl1 = (pl+1)%2;

if(gg.nplies==nx*ny){
 
  ans = ans * (ii/(ii+1.0)) + 0.5/(ii+1.0);
          //ans[inimove] = 0.5;
        
          break;
        }
        else if(gg.haswon(gg.color[0])){
    ans = ans* (ii/(ii+1.0)) + 1.0/(ii+1.0);
          //ans[inimove] = 1.0;
          break;
        }
        else if(gg.haswon(gg.color[1])){
    ans = ans* (ii/(ii+1.0)) + 0.0/(ii+1.0);
          //ans[inimove] = 0.0;
          break;
        }
        std::vector<int> plms;
        for(int kk=0; kk<nx; kk++){
          if(gg.isplayable(kk)){
gg.makemove(kk);
if(!gg.haswon(gg.color[pl1])){
            plms.push_back(kk);
          }
gg.backmove();
}
        }

        if(plms.size()==0){
  ans = ans*(ii/(ii+1.0)) + 1.0*pl/(ii+1.0);
  break;
}
        
        int kk1= int(floor(emscripten_random() * plms.size()));
        int kk2= plms[kk1];
        gg.makemove(kk2);
        
        
    }
  }
*/
  return ans;
}
};


struct runrand1 {

  int maxcount;
  std::vector<int> pcounts_tot;
  std::vector<float> p;
  int nx;
  int ny;

  runrand1(int nx_, int ny_) : nx(nx_), ny(ny_){
    pcounts_tot=std::vector<int>(nx,0);
    p=std::vector<float>(nx,0.0);
    maxcount=100;
  }

  void refresh(){
    std::fill(pcounts_tot.begin(), pcounts_tot.end(), 0);
std::fill(p.begin(), p.end(), 0.0);
  }
 
  std::vector<float> run(Game gg, int nx, int ny){
    
    auto res = randrollout_policy(gg,nx,ny,maxcount);
    auto pcounts = std::get<0>(res);
    std::vector<float> ptemp = std::get<1>(res);
    
    for(int jj=0; jj<nx; jj++){
  if(pcounts[jj]>0){
      p[jj] = p[jj] * (pcounts_tot[jj]/(1.0*pcounts_tot[jj]+pcounts[jj])) + ptemp[jj] * pcounts[jj]/(1.0*pcounts_tot[jj]+pcounts[jj]);
      
    pcounts_tot[jj] += pcounts[jj];
  }

    }
    return p;
    
  }
};

//alpha beta search
template<class valType>
float ab_value(Game gg, int nx, int ny, float aa, float bb, int depth, valType vf){
  int pl=gg.nplies%2;
  float vv0;
if(gg.nplies==nx*ny){
    return 0.5;
}
  else if (gg.haswon(gg.color[0])){
    return 1.0;
}
  else if (gg.haswon(gg.color[1])){
    return 0.0;
}
  else if (depth==0){
    return vf(gg, nx,ny);
}
  else if (pl==0){
    vv0=0.0;
    float aa0=aa;
    for(int ii=0; ii<nx; ii++){
      Game gg1=gg;
      float vv=0;
  if(gg1.isplayable(ii)){
  gg1.makemove(ii);
  vv=ab_value(gg1, nx,ny,aa0,bb,depth-1,vf);

  if(vv>vv0)vv0=vv;
  if(vv>aa0)aa0=vv;
  if(vv0>=bb)break;
}}}
  else if(pl==1){
    vv0=1.0;
    float bb0=bb;
    for(int ii=0; ii<nx; ii++){
      Game gg1=gg;
      float vv=0;
  if(gg1.isplayable(ii)){
  gg1.makemove(ii);
  vv=ab_value(gg1, nx,ny,aa,bb0,depth-1,vf);

  if(vv<vv0)vv0=vv;
  if(vv<bb0)bb0=vv;
  if(vv0<=aa)break;
}}}    
  return vv0;
}



template<class valType>
std::vector<float> ab_policy(Game gg, int nx, int ny, int depth, valType vf){
std::vector<float> ans;
for(int jj=0; jj<nx; jj++){
  Game gg1=gg;
    if(gg1.isplayable(jj)){
  gg1.makemove(jj);
ans.push_back(ab_value(gg1, nx, ny, 0.0, 1.0, depth, vf));
}
else ans.push_back(-0.01);
}
return ans;
}


template<class valType>
struct runab{
  
  int depth=2;
  valType vf;
  int nx;
  int ny;

  runab(int nx_, int ny_, valType vf_) : nx(nx_), ny(ny_), vf(vf_){}

  void refresh(){};
  
  std::vector<float> run(Game gg, int nx, int ny){
    return ab_policy(gg,nx,ny,depth,vf);
}


};
