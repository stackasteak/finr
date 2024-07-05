#ifndef ARMA_NET
#define ARMA_NET

#include "arma_g.h"
#include <vector>
#include <tuple>
#include <string>

#include <mlpack.h>

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

//////

template<class MatType = arma::mat>
struct Testnet_LossType{

  float cg =1.5;
  float cl2 = 1.0e-5;

  Testnet_LossType() {};

  typename MatType::elem_type Forward(const MatType& zz, const MatType& target){
    Row<float> oo(size(zz), fill::ones);
    Row<float> pred(size(zz), fill::zeros);
    for(int jj=0; jj<3; jj++){
      oo(jj) = oo(jj)*cg;
    }
    return -1.0* accu(oo%target%log(prediction)) ;
  }

  void Backward(const MatType& prediction, const MatType& target, MatType& loss){
    Row<float> oo(size(prediction), fill::ones);
    for(int jj=0; jj<3; jj++){
      oo(jj) = oo(jj)*cg;
    }
    loss = oo -1.0*oo%target/prediction;
  }

};



struct testnet_valpol_t{

testnet_valpol_t(){}

testnet_valpol_t(std::string filename) {}

std::tuple<float, std::vector<float>> operator()(arma_g gbe){

}

};


#endif
