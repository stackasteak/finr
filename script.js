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
  let re = "/.*(\d+).*/g"
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
  alert(hh[0]);
  //for (let kk=0; kk<hh.length; kk++){
  //  drawmove(hh[kk]);
  //  updateBoard(hh[kk]);
  //}
});
