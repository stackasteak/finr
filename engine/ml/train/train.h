#ifndef TRAINHH
#define TRAINHH

#include "arma_g.h"
#include "stdrand.h"
#include "arma_net.h"
#include "../mtcs.h" 
#include "../../../fhourstones.h"
#include <tuple>
#include <armadillo>

template<class eng1_t, class eng2_t>
std::tuple<float, Game> h2h(eng1_t& eng1, eng2_t& eng2){

  int nx=eng1.nx;
  int ny=eng2.ny;

  arma_g agg(nx,ny);
  int pl=0;
  for(int ii=0; ii<nx*ny; ii++){

int jj;
if (pl==0) { 
jj=eng1.play(agg.gg, nx,ny);
}
else {
jj=eng2.play(agg.gg, nx,ny);
}
agg.makemove(jj);
pl=1-pl;

auto [gres, gval] =agg.terminal();

if (gres) {
//pl 1 is maximizing
float retval = (gval-0.5)*(-2.0*pl+1.0)+0.5;
return std::make_tuple(retval, agg.gg);
}

}

return std::make_tuple(-2.0,agg.gg);
}


#endif