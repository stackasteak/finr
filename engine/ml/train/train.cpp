#include "arma_g.h"
#include "stdrand.h"
#include "arma_net.h"
#include "../mtcs.h" 
#include "train.h"
#include <iostream>

int main(){

valnet_t vf;
polnet_t pf;

mtcsEngine<stdrand,arma_g, valnet_t, polnet_t> eng(9,9,vf,pf);

auto [vv, gg] = h2h(eng,eng);

std::cout << vv << std::endl;

for(int ii=0; ii<gg.nplies; ii ++){
std::cout << gg.moves[ii] << " ";
}



}