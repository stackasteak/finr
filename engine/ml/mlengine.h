#include <vector>
#include <tuple>
#include "../../fhourstones.h"
#include <memory>
#include <cmath>

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
struct runmtcs{
  
  int playoutcap_small=10;
  int playoutcap_big=40;
  float pbigcap=0.25;
  float cpuct =1.1;
  valType vf;
  polType pf;
  int nx;
  int ny;

  runmtcs(int nx_, int ny_, valType vf_, polType pf_) : nx(nx_), ny(ny_), vf(vf_), pf(pf_){}

  void refresh(){};
  
  std::vector<float> run(Game& gg, int nx, int ny);
  void play(Game& gg, int nx, int ny);


};


template<class randBackend, class gBackend, class valType, class poltype>
std::vector<float> runmtcs<randBackend, gBackend, valType, polType>::run(Game& gg, int nx, int ny){

gbackend gbe(gg, nx, ny);

mtcsNode root(nx);

int plocap=playoutcap_small;
if (randBackend.rand()<pbigcap){
  plocap=playoutcap_big;
}

for(int iplo=0; iplo<plocap; iplo++){

std::vector<std::shared_ptr<mtcsEdge>> path;
std::shared_ptr<mtcsNode> currnode = &root;

for(int imove=0; imove<nx*ny; imove++){

float vv;
auto termres = gbe.terminal();
bool isleaf = (currnode->prior.size()==0);

if(std::get<0>(termres)) {
vv = std::get<1>(termres);
}
else if(isleaf){
currnode->prior = pf(gbe);
vv = vf(gbe);
}

if(std::get<0>(termres) || isleaf){//leaf

for(auto ie=path.begin(); ie!=path.end(); ie++){
  path[ie]->q = path[ie]->q * (path[ie]->n)/(path[ie]->n+1.0) + vv/(path[ie]->n+1.0);
  path[ie]->n +=1;
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
}//end nonleaf
}//end imove
}//end iplo

std::vector<float> ans;
for(int ii=0;ii<nx; ii++){
ans.push_back(root.childs[ii]->q);
}
return ans;
}

template<class randBackend, class gBackend, class valType, class poltype>
void runmtcs<randBackend, gBackend, valType, polType>::play(Game& gg, int nx, int ny){

std::vector<float> qs=run(gg, nx,ny);
float bestq= qs[0];
int bestii=0;
for(int ii=0; ii<nx; ii++){
if(qs[ii]>bestq){
bestq=qs[ii];
bestii=ii;
}}

gg.makemove(bestii);
}