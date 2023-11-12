#include <emscripten/bind.h>
#include "Game.h"
#include <vector.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(my_class_example) {
  class_<MyClass>("MyClass")
    .constructor<int, std::string>()
    .function("incrementX", &MyClass::incrementX)
    .property("x", &MyClass::getX, &MyClass::setX)
    .property("x_readonly", &MyClass::getX)
    .class_function("getStringFromInstance", &MyClass::getStringFromInstance)
    ;
}



EMSCRIPTEN_BINDINGS(engine_module) {

  // register bindings for std::vector<int> and std::map<int, std::string>.
  register_vector<float>("vector<float>");

}
