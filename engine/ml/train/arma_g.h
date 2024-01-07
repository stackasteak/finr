#include "../../../fhourstones.h"
#include <armadillo>
#include <tuple>

struct armag{
  Game gg;
  int nx;
  int ny;
  arma::Cube<float> bb;
  

  armag(Game gg_,int nx_, int ny_) : gg(gg_), nx(nx_), ny(ny_) {
    bb.zeros(2,nx,ny);
  }

  std::tuple<bool,float> terminal(){

int pl=gg.nplies%2;
int pl1=(gg.nplies+1)%2;
  
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
int jj=gg.hight[ii];
bb(pl,ii,jj)=1.0;
gg.makemove(ii);

}
};