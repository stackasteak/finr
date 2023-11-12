#include <emscripten/bind.h>
#include "Game.h"
#include <vector.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(module) {

  // register bindings for std::vector<int> and std::map<int, std::string>.
  register_vector<float>("vector<float>");

}
