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
  float q= -0.01;
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

 




template<class randBackend, class gBackend, class valType, class polType>
struct mtcsEngine{
  
  int playoutcap_small=10;
  int playoutcap_big=40;
  float pbigcap=0.25;
  float cpuct =1.1;
  valType vf;
  polType pf;
  int nx;
  int ny;

  mtcsEngine(int nx_, int ny_, valType vf_, polType pf_) : nx(nx_), ny(ny_), vf(vf_), pf(pf_){}

  void refresh(){};
  
  std::vector<float> run(Game gg, int nx, int ny);
  int play(Game gg, int nx, int ny);


};


template<class randBackend, class gBackend, class valType, class polType>
std::vector<float> mtcsEngine<randBackend, gBackend, valType, polType>::run(Game gg, int nx, int ny){

std::cout << "in run" << std::endl;

std::shared_ptr<mtcsNode> root = std::make_shared<mtcsNode>(mtcsNode(nx));

std::cout << "root done" << std::endl;

int plocap=playoutcap_small;
if (randBackend::rand()<pbigcap){
  plocap=playoutcap_big;
}

for(int iplo=0; iplo<plocap; iplo++){

std::cout << "iplo" << iplo << std::endl;

std::cout << "root expanded? " << root->prior.size() << std::endl ;

std::vector<std::shared_ptr<mtcsEdge>> path;
std::shared_ptr<mtcsNode> currnode = root;

std::cout << "currnode defined" << std::endl;

std::cout << "currnode expanded? " << currnode->prior.size() << std::endl ;

std::cout << "root expanded? " << root->prior.size() << std::endl ;

gBackend gbe(gg, nx, ny);

std::cout << "gbe done" << std::endl;


for(int imove=0; imove<nx*ny; imove++){

std::cout << "imove" << imove << std::endl;


float vv;
auto [gres, gval] = gbe.terminal();
bool isleaf = (currnode->prior.size()==0);

if(gres) {
vv = gval;
}
else if(isleaf){
currnode->prior = std::vector<float>(9,0.5);
vv = vf(gbe);
std::cout << "inside currnode expanded? " << currnode->prior.size() << std::endl ;

}

if(gres || isleaf){//leaf

std::cout << "imleaf " << gres << isleaf << std::endl;

std::cout << "use count" << currnode.use_count() << std::endl;

std::cout << "currnode expanded? " << currnode->prior.size() << std::endl ;

std::cout << "root expanded? " << root->prior.size() << std::endl ;

for(int ie=path.size()-1; ie>-1; ie--){
  path[ie]->q = path[ie]->q * (path[ie]->n)/(path[ie]->n+1.0) + vv/(path[ie]->n+1.0);
  path[ie]->n +=1;

  vv=1.0-vv;
}
break;
}

else{//nonleaf

std::cout << "in non leaf" << std::endl;

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

std::cout << "puct done" << std::endl;

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
ans.push_back(root->childs[ii]->q);
}
return ans;
}

template<class randBackend, class gBackend, class valType, class polType>
int mtcsEngine<randBackend, gBackend, valType, polType>::play(Game gg, int nx, int ny){

std::vector<float> qs=run(gg, nx,ny);
float bestq= qs[0];
int bestii=0;
for(int ii=0; ii<nx; ii++){
if(qs[ii]>bestq){
bestq=qs[ii];
bestii=ii;
}}

return bestii;
}


#endif