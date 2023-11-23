#include <emscripten.h>
#include <emscripten/html5.h>
#include "Game.h"
#include <vector>


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

function resetBoard(){
  boardstate.history =[];
  boardstate.movenum =0;
  boardstate.nextys = new Array(boardstate.xsize);
  boardstate.nextys.fill(0);
}

function updateBoard(ii){
  if(boardstate.nextys[ii]<boardstate.ysize){
    if(boardstate.history.length > boardstate.movenum){
      boardstate.history = boardstate.history.slice(0, boardstate.movenum);
    }
    boardstate.history.push(ii);
    boardstate.movenum = boardstate.movenum + 1;
    boardstate.nextys[ii] = boardstate.nextys[ii] +1;
  
  }
}

function backBoard(){
  let err = -1;
  if(boardstate.movenum>0){
    let prevx = boardstate.history[boardstate.movenum-1];
    boardstate.nextys[prevx] = boardstate.nextys[prevx]-1;
    boardstate.movenum = boardstate.movenum - 1;
    return prevx;
  }
  return err;
}

function forwBoard(){
  let err = -1;
  if(boardstate.movenum < boardstate.history.length){
    let nextx = boardstate.history[boardstate.movenum];
    boardstate.nextys[nextx] = boardstate.nextys[nextx]+1;
    boardstate.movenum = boardstate.movenum + 1;
    return nextx;
  }
  return err;
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

function redraw(){
  ctx.fillStyle = 'rgb(25,140,255)';
  ctx.fillRect(0,0,width,height);

  if(boardstate.xsize>=boardstate.ysize){
    stonesize = width/boardstate.xsize;
  }
  else{
    stonesize = width/boardstate.ysize;
    xoffset = (width-stonesize*boardstate.xsize)*0.5;
  }

  for(let ii=0; ii<boardstate.xsize; ii++){
    for(let jj=0; jj<boardstate.ysize; jj++){
      ctx.fillStyle = "rgb(0, 0, 0)";
      ctx.beginPath();
      ctx.arc(xoffset+(ii+0.5)*stonesize,(jj+0.5)*stonesize , 0.5*stonesize-2, degToRad(0), degToRad(360), false);
      ctx.fill();
    }
  }

  ctx.fillStyle = 'rgb(0,0,0)'; 
  ctx.fillRect(0, stonesize*boardstate.ysize, width, height);
}


function iselect(x){
  let ans=boardstate.xsize;
  for(let ii=0; ii<boardstate.xsize; ii++){
    if(x < xoffset+(ii+1)*stonesize){
      ans = ii;
      break;
    }
  }
  return ans;
}

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

function drawmove(ii){
  let colo;
  if (boardstate.movenum %2==0){
    colo = "rgb(255, 234, 128)";
  }
  else {
    colo = "rgb(255, 0,0)";
  }

  if(ii>-1 && ii<boardstate.xsize){
    jj=boardstate.nextys[ii];
    if(jj<boardstate.ysize && jj > -1){
      let jj2=boardstate.ysize-1-jj;
      ctx.fillStyle = colo;
      ctx.beginPath();
      ctx.arc(xoffset+(ii+0.5)*stonesize,(jj2+0.5)*stonesize , 0.5*stonesize-2, degToRad(0), degToRad(360), false);
      ctx.fill();
    }
  }
}

function undrawmove(ii){
  let colo = "rgb(0, 0,0)";

  if(ii>-1 && ii<boardstate.xsize){
    jj=boardstate.nextys[ii];
    if(jj<boardstate.ysize && jj > -1){
      let jj2=boardstate.ysize-1-jj;
      ctx.fillStyle = colo;
      ctx.beginPath();
      ctx.arc(xoffset+(ii+0.5)*stonesize,(jj2+0.5)*stonesize , 0.5*stonesize-2, degToRad(0), degToRad(360), false);
      ctx.fill();
    }
  }
}

function drawP(p){
  ctx.fillStyle = "rgb(255,255,255)";
  alert(p[0]);
  for(let ii=0; ii<boardstate.xsize; ii++){
    let jj=boardstate.nextys[ii];
    if (jj<boardstate.ysize){
      let jj2=boardstate.ysize-1-jj;
      ctx.fillText(p[ii].toFixed(0).tostring(), xoffset+ii*stonesize, (jj2)*stonesize, stonesize);
    }
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

backBtn.addEventListener('click', () => {
  let ii = backBoard();
  undrawmove(ii);
});

forwBtn.addEventListener('click', () => {
  let ii = boardstate.history[boardstate.movenum];
  drawmove(ii);
  forwBoard();
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

EM_JS(void, alert_float, (float x), {
  alert(x);
});

EM_JS(void, alert_int, (int x), {
  alert(x);
});

EM_JS(void, alert_str, (std::string x), {
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
  let colo;
  if (pl==0){
    colo = "rgb(255, 234, 128)";
  }
  else {
    colo = "rgb(255, 0,0)";
  }
  //alert(xpos);
  //alert(ss);
  //alert(xpos/ss);

  ctx.fillStyle = colo;
  ctx.beginPath();
  ctx.arc(xpos, ypos , 0.5*ss-2, 0.0, 6.283, false);
  ctx.fill();

});

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

};

drawingState ds(9,9);

EM_BOOL touchend_callback(
    int eventType,
    const EmscriptenTouchEvent *event,
    void *ud
) {
    drawingState* userData = static_cast<drawingState*>(ud);
    int ii = userData->iselect(event->touches[0].clientX);
    //alert_float( event->touches[0].clientX);
    
  
    int jj = userData->nextys[ii];
    int pl = (userData->movenum)%2;
    alert_float(jj);
    alert_float(pl);
    if (jj< userData->ny){
      int jj2= userData->ny-1-jj;
      float xpos=(ii+0.5)*userData->stonesize;
      float ypos =(jj2+0.5)*userData->stonesize;
      //alert_int(ii);
      //alert_int(jj2);
      drawmove(xpos,ypos,userData->stonesize,pl);
      userData->update(ii);
    }
    
    return 0;
}

class engineState{
  std::vector<float> p;
  int nx;
  int ny;

public: 

  engineState(int nx_, int ny_) : nx(nx_), ny(ny_){
    p.resize(nx_,0.0);
  }

  void resize(int nx_, int ny_) {
    nx =nx_;
    ny=ny_;
    p.resize(nx_,0.0);
  }

  void resize0(){}

  void batch(){
    for(int ii=0; ii<nx; ii++){
      p[ii]= std::rand();
    }
  }

  float getP(int ii){
    return p[ii];
  }

  int getNX(){return nx;}

  int getNY(){return ny;}

};

int main (){

  int nx=9;
  int ny=9;

  float ss = redraw(nx,ny);
  //drawingState drawstate(nx,ny,ss);

  ds.stonesize=ss;
  alert_float(ds.stonesize);
  
  emscripten_set_touchend_callback(
        "canvas",
        static_cast<void*>(&ds),
        1,
        touchend_callback
    );
  
  
  
  return 0;
}

