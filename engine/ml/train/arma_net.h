#ifndef ARMA_NET
#define ARMA_NET

#include "arma_g.h"
#include <vector>
#include <tuple>

/*
struct valnet_t{

float operator()(arma_g gbe){
  return 0.5;
}

};

struct polnet_t{

std::vector<float> operator()(arma_g gbe){
  std::vector<float> ans(gbe.nx, 1.0/gbe.nx );
  return ans;
}

};
*/

struct simple_valpol_t{

std::tuple<float, std::vector<float>> operator()(arma_g gbe){
  std::vector<float> pans(gbe.nx, 1.0/gbe.nx );
  auto ans = std::make_tuple(0.5, pans);
  return ans;
}

};


#endif
