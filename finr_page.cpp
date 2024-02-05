#include <emscripten.h>
#include <emscripten/html5.h>
#include <vector>
#include "engine/engine.h"
#include <stdio.h>


//using namespace emscripten;


// javascript functions

EM_JS(void, alert_float, (float x), {
  alert(x);
});


EM_JS(float, redraw, (int nx, int ny), {
  let ctx = Module.canvas.getContext('2d');
  let width = Module.canvas.width = window.innerWidth;
  let height = Module.canvas.height = window.innerWidth+30;
  ctx.fillStyle = 'rgb(25,140,255)';
  ctx.fillRect(0,0,width,height);

  let stonesize;
  let xoffset =0;
  if(nx>=ny){
    stonesize = width/nx;
  }
  else{
    stonesize = width/ny;
    xoffset = (width-stonesize*nx)*0.5;
  }

  for(let ii=0; ii<nx; ii++){
    for(let jj=0; jj<ny; jj++){
      ctx.fillStyle = "rgb(0, 0, 0)";
      ctx.beginPath();
      ctx.arc((ii+0.5)*stonesize,(jj+0.5)*stonesize , 0.5*stonesize-2, 0.0, 6.2830, false);
      ctx.fill();
    }
  }

  ctx.fillStyle = 'rgb(0,0,0)'; 
  ctx.fillRect(0, stonesize*ny, width, height);

  return stonesize;
});

EM_JS(void, drawmove, (float xpos, float ypos, float ss, int pl), {
  let ctx = Module.canvas.getContext('2d');
  let colo;
  if (pl==0){
    colo = "rgb(255, 234, 128)";
  }
  else {
    colo = "rgb(255, 0,0)";
  }

  ctx.fillStyle = colo;
  ctx.beginPath();
  ctx.arc(xpos, ypos , 0.5*ss-2, 0.0, 6.283, false);
  ctx.fill();

});

EM_JS(void, undrawmove, (float xpos, float ypos, float ss), {
  let ctx = Module.canvas.getContext('2d');
  let colo = "rgb(0,0,0)";

  ctx.fillStyle = colo;
  ctx.beginPath();
  ctx.arc(xpos, ypos , 0.5*ss-2, 0.0, 6.283, false);
  ctx.fill();

});

EM_JS(int, loadhiststep, (int nx, int ny, int n), {
  const re = new RegExp('[^0123456789]*([0123456789]+)',"g") ;
  let h = Module.pastehistBox.value;
  
  let m = [...h.matchAll(re)];
  let moves = m.map((mm) => Number(mm[1]));
  //m.map(mm => alert(mm[1]));
  if(n<moves.length){
    return moves[n]-1;
  }
  else{
    return -1;
  }
});

EM_JS(void, draw1p, (int ii, float ss, float p, int pl), {
  let ctx = Module.canvas.getContext('2d');
  let height = Module.canvas.height;
  let colo;
if (pl==0){
    colo = "rgb(255, 234, 128)";
  }
  else {
    colo = "rgb(255, 0,0)";
  }
  
  let ypos = height+2;
  let xpos = ii*ss+2;

  ctx.font = "30px Arial";
  ctx.fillStyle = colo;
  ctx.fillText((p*100).toFixed(0).toString(), xpos, ypos, ss);
});



EM_JS(void, redrawpbar, (), {
  let ctx = Module.canvas.getContext('2d');
  let width = window.innerWidth;
  let height = window.innerWidth+30;
  
  ctx.fillStyle = 'rgb(0,0,0)'; 
  ctx.fillRect(0, width, width, height);
});


//global state variables


struct drawingState{
  float stonesize;
  int nx;
  int ny;
  std::vector<int> nextys;
  std::vector<int> history;
  int movenum;

  drawingState(int nx_, int ny_) : nx(nx_), ny(ny_) {
    movenum =0;
    nextys.resize(nx,0);
  };

  drawingState(int nx_, int ny_, float ss) : nx(nx_), ny(ny_), stonesize(ss) {
    movenum =0;
    nextys.resize(nx,0);
  };

  int iselect(float x){
    int ans=nx;
    for(int ii=0; ii<nx; ii++){
      if(x < (ii+1)*stonesize){
        ans = ii;
        break;
      }
    }
   return ans;
  }

  void update(int ii){
    if(nextys[ii]<ny){
      if(history.size() > movenum){
        history.resize(movenum);
      }
      history.push_back(ii);
      movenum = movenum + 1;
      nextys[ii] = nextys[ii] +1;
  
    }
  }

  void reset(){
    movenum =0;
    nextys.resize(nx,0);
    std::fill(nextys.begin(), nextys.end(), 0);
    history.resize(0);
  }

  int back(){
    if(movenum>0){
      int prevx = history[movenum-1];
      nextys[prevx] = nextys[prevx]-1;
      movenum = movenum - 1;
    return prevx;
    }
    return -1;
  }

  int forw(){
    if(movenum < history.size()){
      int nextx = history[movenum];
      nextys[nextx] = nextys[nextx]+1;
      movenum = movenum + 1;
      return nextx;
    }
    return -1;
  }
 

};

drawingState ds(9,9);

//engine

using rT = runab<randrollout>;
randrollout rro(5);
rT rs(9,9,rro);

struct allState{
  drawingState * dsp;
  engineface * esp;
  rT * rsp;

  allState(drawingState * ds_, engineface * es_, rT * rs_) : dsp(ds_), esp(es_), rsp(rs_) {};
};


engineface es(9,9);
allState as(&ds,&es,&rs);



//event handling and callbacks 

void drawps(void * as0 ){
  allState * as2 = static_cast<allState*>(as0);
    
  std::vector<float> ps = as2->esp->p;

  int pl = (as2->dsp->movenum)%2;

  float ss = as2->dsp->stonesize;
  for(int ii=0; ii<ps.size(); ii++){
    draw1p(ii,ss,ps[ii],pl);
  }
}

EM_BOOL touchend_callback(
    int eventType,
    const EmscriptenTouchEvent *event,
    void *ud
) {
    allState* userData = static_cast<allState*>(ud);
    
  int ii = userData->dsp->iselect(event->touches[0].clientX);
    
  
    int jj = userData->dsp->nextys[ii];
    int pl = (userData->dsp->movenum)%2;
    
    
    if (jj< userData->dsp->ny){
      int jj2= userData->dsp->ny-1-jj;
      float xpos=(ii+0.5)*userData->dsp->stonesize;
      float ypos =(jj2+0.5)*userData->dsp->stonesize;
      
      drawmove(xpos,ypos,userData->dsp->stonesize,pl);
      userData->dsp->update(ii);
      userData->esp->refresh=true;
    }
  
    
    return EM_TRUE;
}

extern "C"{

void onClear(){
  redraw(ds.nx,ds.ny);
  ds.reset();
  es.refresh=true;
}

void onBack(){
  int ii = ds.back();
  int jj = ds.nextys[ii];
  if(jj<ds.ny && jj > -1){
    int jj2=ds.ny-1-jj;
    float xpos=(ii+0.5)*ds.stonesize;
    float ypos =(jj2+0.5)*ds.stonesize;
      
    undrawmove(xpos,ypos, ds.stonesize);
    es.refresh=true;
  }
}

void onForw(){
  if (ds.history.size()>ds.movenum){
    int ii = ds.history[ds.movenum];
    int jj = ds.nextys[ii];
    if(jj<ds.ny && jj > -1){
      int jj2=ds.ny-1-jj;
      float xpos=(ii+0.5)*ds.stonesize;
      float ypos =(jj2+0.5)*ds.stonesize;
      int pl = (ds.movenum)%2;  
      drawmove(xpos,ypos, ds.stonesize,pl);
      es.refresh=true;
    }
    ds.forw();
  }
}

void onLoad(){
  redraw(ds.nx,ds.ny);
  ds.reset();
  es.refresh=true;
  
  int res = -1;
  for(int n =0; n<ds.nx * ds.ny;n++){
    res = loadhiststep(ds.nx,ds.ny, n);
    if (res <0){
      break;
    }
    int jj = ds.nextys[res];
    if(jj<ds.ny && jj > -1){
      int jj2=ds.ny-1-jj;
      float xpos=(res+0.5)*ds.stonesize;
      float ypos =(jj2+0.5)*ds.stonesize;
      int pl = (ds.movenum)%2;  
      drawmove(xpos,ypos, ds.stonesize,pl);
      ds.update(res);
    }
  }
}

void onStart(){
  if (es.running){
    es.running=false;
  }
  else{
    es.running=true;
  }
}

}

//main loop
void mainloop(void * as0){
  allState * as1 = static_cast<allState*>(as0);
  drawingState * ds1 = as1->dsp;
  engineface * es1 = as1->esp;
  rT * rs1 = as1->rsp;

  if(es1->running){

    if (es1->refresh){
      es1->refresh = false;
      rs1->refresh();
      for(int jj=0; jj<ds1->nx; jj++){
      es1->p[jj] = 0.0;
      }
    
    }

    //set up position
    Game gg;
    gg.reset();
    for(int imove=0; imove< ds1->movenum; imove++){
    gg.makemove(ds1->history[imove]);
    }

    es1->p = rs1->run(gg, ds1->nx, ds1->ny);
  }
  redrawpbar();
  drawps(as0);
}


int main (){

  int nx=9;
  int ny=9;
  

  alert_float(1.0);
/*
  float ss = redraw(nx,ny);

  alert_float(2.0);

  ds.stonesize=ss;
  
  emscripten_set_touchend_callback(
        "canvas",
        static_cast<void*>(&as),
        1,
        touchend_callback
    );

  emscripten_set_main_loop_arg(mainloop, static_cast<void*>(&as), 1, false);
  
  */
  return 0;
}

