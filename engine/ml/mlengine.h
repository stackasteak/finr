#include <vector>
#include <tuple>
#include "../../fhourstones.h"

struct mtcsNode{
  std::vector<float> prior;
  std::vector<float> q;
  std::vector<int> ns;
  std::vector<mtcsNode*> childs;

  mtcsNode(int nx){
    q=std::vector<float>(0.0,nx);
ns=std::vector<int>(0,nx);
childs=std::vector<mtcsNode*>(NULL,nx);
}

};

template<class randBackend, class gBackend, class valType, class polType>
struct runmtcs{
  
  int playoutcap_small=10;
  int playoutcap_big=40;
  float pbigcap=0.25;
  valType vf;
  polType pf;
  int nx;
  int ny;

  runab(int nx_, int ny_, valType vf_, polType pf_) : nx(nx_), ny(ny_), vf(vf_), pf(pf_){}

  void refresh(){};
  
  std::vector<float> run(Game gg, int nx, int ny);
  void play(Game& gg, int nx, int ny);


};


template<class randBackend, class gBackend, class valType, class poltype>
std::vector<float> runmtcs<randBackend, gBackend, valType, polType>::run(Game gg, int nx, int ny){

gbackend be(gg, nx, ny);

mtcsNode root(nx);

int plocap=playoutcap_small;
if (randBackend.rand()<pbigcap){
  plocap=playoutcap_big;
}

for(int iplo=0; iplo<plocap; iplo++){

std::vector<mtcsNode*> path;

path.push_back(&root);

for(int imove=0; imove<nx*ny; imove++){

float vv= gg.terminal();
if(vv>-0.5){