#include <vector>
#include <tuple>

template<class valType, class poltype>
struct runmtcs{
  
  int playoutcap_small=10;
  int playoutcap_big=40;
  valType vf;
  polType pf;
  int nx;
  int ny;

  runab(int nx_, int ny_, valType vf_, polType pf_) : nx(nx_), ny(ny_), vf(vf_), pf(pf_){}

  void refresh(){};
  
  std::vector<float> run(Game gg, int nx, int ny);
  void play(Game& gg, int nx, int ny);


};


template<class valType, class poltype>
runmtcs<valType, polType>::run(Game gg, int nx, int ny){

