#include <cstdlib>

struct stdrand{

  float rand(){
    return (float)(std::rand()) / (float)(RAND_MAX);
  }
};