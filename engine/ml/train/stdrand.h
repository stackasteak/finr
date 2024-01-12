#ifndef STDRANDHH
#define STDRANDHH

#include <cstdlib>

struct stdrand{

  static float rand(){
    return (float)(std::rand()) / (float)(RAND_MAX);
  }
};

#endif