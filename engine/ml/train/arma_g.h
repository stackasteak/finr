#ifndef ARMA_GAME
#define ARMA_GAME


#include "../../../fhourstones.h"
#include <armadillo>
#include <tuple>
#include <vector>

struct arma_g{
  Game gg;
  int nx;
  int ny;
  arma::Cube<float> bb;
  std::vector<int> nextys;
  

  arma_g(Game gg_,int nx_, int ny_) : gg(gg_), nx(nx_), ny(ny_) {
    bb.zeros(2,nx,ny);
    nextys = std::vector<int>(nx, 0);
    int pl=0;
    for(int imove=0; imove<gg.nplies; imove++){
      int ii= gg.moves[imove];
      bb(pl,ii,nextys[ii])=1.0;
       nextys[ii] +=1;
       pl= 1-pl;
    }

  }

arma_g(int nx_, int ny_) : nx(nx_), ny(ny_) {
  bb.zeros(2,nx,ny);
  nextys = std::vector<int>(nx, 0);
}
   
  std::tuple<bool,float> terminal(){

int pl=gg.nplies%2;
int pl1= 1-pl;
  
if(gg.nplies==nx*ny){
    return std::make_tuple(true,0.5);
}
  else if (gg.haswon(gg.color[pl1])){
    return std::make_tuple(true,0.0);;
}
  else if (gg.haswon(gg.color[pl])){
    return std::make_tuple(true,1.0);;
}
  else {
return std::make_tuple(false,-2);
}

}

bool isplayable(int ii){
return gg.isplayable(ii);
}

void makemove(int ii){
int pl=gg.nplies%2;
int jj= nextys[ii];

//std::cout << "move " << pl << " " << ii << " " << jj << std::endl;

bb(pl,ii,jj)=1.0;
gg.makemove(ii);

}
};


#endif
