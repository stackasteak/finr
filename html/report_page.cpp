#include <emscripten.h>


EM_JS(void, writereport, (), {
  document.writeln("hi");
});

int main(){
  writereport();

  return 0;
}
