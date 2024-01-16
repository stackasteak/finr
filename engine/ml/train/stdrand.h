#ifndef STDRANDHH
#define STDRANDHH

#include <cstdlib>
#include <vector>

struct stdrand{

  static float rand(){
    return (float)(std::rand()) / (float)(RAND_MAX);
  }

  static std::vector<float> poormandirichlet(int n){
    std::vector<float> ans;
    float tot = 0.0;
    for(int ii=0; ii<n; ii++){
      float v = 1.0*std::rand();
      ans.push_back(v);
      tot += v;
    }

    for(int ii=0; ii<n; ii++){
      ans[ii] = ans[ii]/tot;
    }
    return ans;
  }

};

#endif
