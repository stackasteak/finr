#include <emscripten.h>
#include <emscripten/html5.h>
#include "Game.h"
#include <vector>
#include <pthread.h>


//using namespace emscripten;

/*

const canvas = document.querySelector('.myCanvas');
const width = canvas.width = window.innerWidth;
const height = canvas.height = window.innerWidth+30;
const ctx = canvas.getContext('2d');

const sizePicker = document.getElementById('bsize');
const backBtn = document.querySelector('.backBtn');
const forwBtn = document.querySelector('.forwBtn');
const clearBtn = document.querySelector('.clearBtn');
const pastehistBox = document.getElementById('pastehistBox');
const pastehistBtn = document.getElementById('pastehistButton');
const startBtn = document.getElementById('startBtn');

//engine variables
const engineWorker = new Worker("engine_worker.js");
var enginerun = false;
var engineinit =false;



//drawing variables
let stonesize;
let xoffset=0;

// store mouse pointer coordinates, and whether the button is pressed
let curX;
let curY;
let pressed = false;

const boardstate = {
  xsize: 9,
  ysize: 9,
  history: [],
  nextys: [],
  movenum: 0
};

function setSize(){
  if(sizePicker.value =="6x7"){
    boardstate.xsize = 7;
    boardstate.ysize = 6;
  }
  if(sizePicker.value =="8x8"){
    boardstate.xsize = 8;
    boardstate.ysize = 8;
  }
  if(sizePicker.value =="9x9"){
    boardstate.xsize = 9;
    boardstate.ysize = 9;
  }
  if(sizePicker.value =="10x10"){
    boardstate.xsize = 10;
    boardstate.ysize = 10;
  }
}


//interface

function readHistory(h){
  //let re = "/;[ry]\[(\d+)\]/g";
  let re = /[^\d]*(\d+)[^\d]* /g
  let m = [...h.matchAll(re)];
  return m.map((mm) => Number(mm[1]));
}

//drawing 

function degToRad(degrees) {
  return degrees * Math.PI / 180;
};


function drawhighlight(){
  let ii1 = iselect(curX);

  for(let jj=boardstate.nextys[ii1]; jj<boardstate.ysize; jj++){
    let jj2=boardstate.ysize-1-jj;
    ctx.fillStyle = "rgb(100, 100, 100)";
    ctx.beginPath();
    ctx.arc(xoffset+(ii1+0.5)*stonesize,(jj2+0.5)*stonesize , 0.5*stonesize-2, degToRad(0), degToRad(360), false);
    ctx.fill();
  }
}

function undrawhighlight(ii1){

  for(let jj=boardstate.nextys[ii1]; jj<boardstate.ysize; jj++){
    let jj2=boardstate.ysize-1-jj;
    ctx.fillStyle = "rgb(0, 0, 0)";
    ctx.beginPath();
    ctx.arc(xoffset+(ii1+0.5)*stonesize,(jj2+0.5)*stonesize , 0.5*stonesize-2, degToRad(0), degToRad(360), false);
    ctx.fill();
  }
}


// update sizepicker output value

sizePicker.onchange = ( () => {setSize(); resetBoard(); redraw();} );


// update mouse pointer coordinates
document.addEventListener('mousemove', e => {
  curX = (window.Event) ? e.pageX : e.clientX + (document.documentElement.scrollLeft ? document.documentElement.scrollLeft : document.body.scrollLeft);
  curY = (window.Event) ? e.pageY : e.clientY + (document.documentElement.scrollTop ? document.documentElement.scrollTop : document.body.scrollTop);
});

canvas.addEventListener('mousedown', () => pressed = true);

canvas.addEventListener('mouseup', () => pressed = false);

canvas.addEventListener('touchstart', (e) => {
  pressed = true;
  curX = (window.Event) ? e.pageX : e.touches[0].clientX + (document.documentElement.scrollLeft ? document.documentElement.scrollLeft : document.body.scrollLeft);
  curY = (window.Event) ? e.pageY : e.touches[0].clientY + (document.documentElement.scrollTop ? document.documentElement.scrollTop : document.body.scrollTop);
  drawhighlight();
}
);

canvas.addEventListener('touchend', (e) => {
  pressed = false;
  let curX0=curX;
  let curY0=curY;
  curX = (window.Event) ? e.pageX : e.touches[0].clientX + (document.documentElement.scrollLeft ? document.documentElement.scrollLeft : document.body.scrollLeft);
  curY = (window.Event) ? e.pageY : e.touches[0].clientY + (document.documentElement.scrollTop ? document.documentElement.scrollTop : document.body.scrollTop);
  let ii0 = iselect(curX0);
  let ii = iselect(curX);
  undrawhighlight(ii0);
  drawmove(ii);
  updateBoard(ii);
});

clearBtn.addEventListener('click', () => {
  resetBoard();
  redraw();
});


pastehistBtn.addEventListener('click', () => {
  resetBoard();
  redraw();
  hh = readHistory(pastehistBox.value);
  for (let kk=0; kk<hh.length; kk++){
    drawmove(hh[kk]-1);
    updateBoard(hh[kk]-1);
  }
});



startBtn.addEventListener('click', () => {
  if(!enginerun && !engineinit){
    //var estate = new Module.engineState(9,9); 
    engineWorker.postMessage(
      {msg:"init",
       bs: boardstate,
       m: Module});
    enginerun =true; 
    engineinit=true;
    startBtn.textContent = "stop";
  }
  else if(!enginerun){ 
    engineWorker.postMessage(
      {msg:"start",
       bs: boardstate});
    enginerun =true;
    startBtn.textContent = "stop";
  }
  else{
    engineWorker.postMessage(
      {msg:"stop"});
    enginerun =false;
    startBtn.textContent = "start";
  }
});

engineWorker.onmessage =  (e) => {
  
  alert(e.data[0]);
  //drawP(e.data)
};


  */

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

EM_JS(void, draw1p, (int ii, float ss, float p), {
  let ctx = Module.canvas.getContext('2d');
  let height = Module.canvas.height;
  let colo = "rgb(255,255,255)";
  let ypos = height+2;
  let xpos = ii*ss+2;

  ctx.font = "30px Arial";
  ctx.fillStyle = colo;
  ctx.fillText((p*100).toFixed(0).toString(), xpos, ypos, ss);
});



EM_JS(void, redrawpbar, (), {
  let ctx = Module.canvas.getContext('2d');
  let width = Module.canvas.width;
  let height = Module.canvas.height;
  
  ctx.fillStyle = 'rgb(0,0,0)'; 
  ctx.fillRect(0, width, width, height);
});


//global state variables

pthread_mutex_t mutexas;

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



struct engineState{
  std::vector<float> p;
  int nx;
  int ny;

  engineState(int nx_, int ny_) : nx(nx_), ny(ny_){
    p.resize(nx_,0.0);
  }

  void resize(int nx_, int ny_) {
    nx =nx_;
    ny=ny_;
    p.resize(nx_,0.0);
  }

  void batch(){
    for(int ii=0; ii<nx; ii++){
      p[ii]= std::rand();
    }
  }


};

engineState es(9,9);

struct allState{
  drawingState * dsp;
  engineState * esp;

  allState(drawingState * ds_, engineState * es_) : dsp(ds_), esp(es_) {};
};

allState as(&ds,&es);


//event handling and callbacks 

void drawps(void * as1 ){
  allState * as2 = static_cast<allState*>(as1);
  
pthread_mutex_lock(mutexas); 
  
std::vector<float> ps = as2->esp->p;

  prhread_mutex_unlock(mutexas);
  float ss = as2->dsp->stonesize;
  for(int ii=0; ii<ps.size(); ii++){
    draw1p(ii,ss,ps[ii]);
  }
}

EM_BOOL touchend_callback(
    int eventType,
    const EmscriptenTouchEvent *event,
    void *ud
) {
    drawingState* userData = static_cast<drawingState*>(ud);
    int ii = userData->iselect(event->touches[0].clientX);
    
  
    int jj = userData->nextys[ii];
    int pl = (userData->movenum)%2;
    
    
    if (jj< userData->ny){
      int jj2= userData->ny-1-jj;
      float xpos=(ii+0.5)*userData->stonesize;
      float ypos =(jj2+0.5)*userData->stonesize;
      
      drawmove(xpos,ypos,userData->stonesize,pl);
      userData->update(ii);
    }
    
    return EM_TRUE;
}

extern "C"{

void onClear(){
  redraw(ds.nx,ds.ny);
  ds.reset();
}

void onBack(){
  int ii = ds.back();
  int jj = ds.nextys[ii];
  if(jj<ds.ny && jj > -1){
    int jj2=ds.ny-1-jj;
    float xpos=(ii+0.5)*ds.stonesize;
    float ypos =(jj2+0.5)*ds.stonesize;
      
    undrawmove(xpos,ypos, ds.stonesize);
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
    }
    ds.forw();
  }
}

void onLoad(){
  redraw(ds.nx,ds.ny);
  ds.reset();
  
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

}


int main (){

  int nx=9;
  int ny=9;

  float ss = redraw(nx,ny);

  ds.stonesize=ss;
  
  emscripten_set_touchend_callback(
        "canvas",
        static_cast<void*>(&ds),
        1,
        touchend_callback
    );

  emscripten_set_main_loop_arg(drawps, static_cast<void*>(&as), 1, false);
  
  //drawps(es.p,ss);
  
  return 0;
}

