#ifndef MTCS
#define MTCS

#include <vector>
#include <tuple>
#include "../../fhourstones.h"
#include <memory>
#include <cmath>
#include <iostream>

struct mtcsNode;

struct mtcsEdge{
  float q= 0.5;
  int n=0;
  
  std::shared_ptr<mtcsNode> child ;

};

struct mtcsNode{
  std::vector<float> prior;
  std::vector<std::shared_ptr<mtcsEdge>> childs;

  mtcsNode(int nx){

  for(int ii=0; ii<nx; ii++){
  std::shared_ptr<mtcsEdge> ptr (new mtcsEdge());
  childs.push_back(ptr);
}}

};

 




template<class randBackend, class gBackend, class valpolType>
struct mtcsEngine{
  
  int playoutcap_small=100;
  int playoutcap_big=400;
  float pbigcap=0.25;
  float cpuct =1.1;
  float pdirichlet = 0.03;
  valpolType vpf;
  int nx;
  int ny;

  mtcsEngine(int nx_, int ny_, valpolType vpf_) : nx(nx_), ny(ny_), vpf(vpf_){}

  void refresh(){};
  
  std::vector<float> run(Game gg, int nx, int ny);
  int play(Game gg, int nx, int ny);


};


template<class randBackend, class gBackend, class valpolType>
std::vector<float> mtcsEngine<randBackend, gBackend, valpolType>::run(Game gg, int nx, int ny){



std::shared_ptr<mtcsNode> root = std::make_shared<mtcsNode>(mtcsNode(nx));


int plocap=playoutcap_small;
if (randBackend::rand()<pbigcap){
  plocap=playoutcap_big;
}

for(int iplo=0; iplo<plocap; iplo++){



std::vector<std::shared_ptr<mtcsEdge>> path;
std::shared_ptr<mtcsNode> currnode = root;



gBackend gbe(gg, nx, ny);

//std::cout << "gbe done" << std::endl;


for(int imove=0; imove<nx*ny; imove++){


float vv;
auto [gres, gval] = gbe.terminal();
bool isleaf = (currnode->prior.size()==0);

if(gres) {
vv = 1.0-gval;
}
else if(isleaf){
auto [vv1, pp1] = vpf(gbe);
currnode->prior = pp1;
vv = vv1;

//add noise if root
if(imove==0){
  std::vector<int> plms;
  for(int ii=0; ii<nx; ii++){
    if(gbe.isplayable(ii)){
      plms.push_back(ii);
    }
  }
  std::vector<float> pd = randBackend::poormandirichlet(plms.size());
  for(int iplm=0; iplm<plms.size(); iplm++){
    int jj = plms[iplm];
    currnode->prior[jj] = (1.0-pdirichlet)*currnode->prior[jj] + pdirichlet*pd[iplm];
  }
}}

if(gres || isleaf){//leaf

for(int ie=path.size()-1; ie>-1; ie--){
  path[ie]->q = path[ie]->q * (path[ie]->n)/(path[ie]->n+1.0) + vv/(path[ie]->n+1.0);
  path[ie]->n +=1;

  vv=1.0-vv;
}
break;
}

else{//nonleaf


std::vector<int> plms;
std::vector<float> puct;
float sumn=0;
for(int ii=0; ii<nx; ii++){
if(gbe.isplayable(ii)){
plms.push_back(ii);
puct.push_back(currnode->prior[ii]/(currnode->childs[ii]->n +1.0));
sumn += currnode->childs[ii]->n;
}}

for(int iplm=0; iplm<plms.size(); iplm++){
puct[iplm] = puct[iplm]*std::sqrt(sumn)*cpuct + currnode->childs[plms[iplm]]->q;
}

float bestpuct= puct[0];
int bestiplm=0;
for(int iplm=1; iplm<plms.size(); iplm++){
if(puct[iplm]>bestpuct){
bestpuct=puct[iplm];
bestiplm=iplm;
}}


if(currnode->childs[plms[bestiplm]]->child == nullptr){
currnode->childs[plms[bestiplm]]->child = std::shared_ptr<mtcsNode>(new mtcsNode(nx));
}

path.push_back(currnode->childs[plms[bestiplm]]);

currnode= currnode->childs[plms[bestiplm]]-> child;

gbe.makemove(plms[bestiplm]);
}//end nonleaf
}//end imove
}//end iplo

std::vector<float> ans;
for(int ii=0;ii<nx; ii++){
  if(gg.isplayable(ii)){
    ans.push_back(root->childs[ii]->q);
  }
  else{
    ans.push_back(-0.01);
  }
}
return ans;
}

template<class randBackend, class gBackend, class valType, class polType>
int mtcsEngine<randBackend, gBackend, valType, polType>::play(Game gg, int nx, int ny){

std::vector<float> qs=run(gg, nx,ny);
float bestq= qs[0];
int bestii=0;

std::cout << "qs: " ;
  
for(int ii=0; ii<nx; ii++){
std::cout << qs[ii] << " ";
if(qs[ii]>bestq){
bestq=qs[ii];
bestii=ii;
}}

std::cout << std::endl;
std::cout <<"moved " << bestii+1 <<std::endl;

return bestii;
}


#endif
