#include <stdio.h>
#include "../engine/engine.h"

int main(int argc, char** argv){
  using rT = runab<lookrollout>;
  lookrollout rro(5);
  rT rs(9,9,rro);

  return 0;
}

