#include <stdio.h>
#include "../engine/engine.h"

int main(int argc, char** argv){
  using rT = runab<lookrollout>;
  lookrollout rro(5);
  rT rs(9,9,rro);

  Game gg;
    gg.reset();
    for(int imove=0; imove< ds1->movenum; imove++){
      gg.makemove(ds1->history[imove]);
    }

    rs1.run(gg, ds1->nx, ds1->ny);

  return 0;
}

