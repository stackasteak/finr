#ifndef ARMA_NET
#define ARMA_NET

#include "arma_g.h"
#include <vector>

struct valnet_t{

float operator()(arma_g gbe){
  return 0.5;
}

};

struct polnet_t{

std::vector<float> operator()(arma_g gbe){
  std::vector<float> ans(1.0/gbe.nx, gbe.nx);
  return ans;
}

};


#endif
