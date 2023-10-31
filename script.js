const canvas = document.querySelector('.myCanvas');
const width = canvas.width = window.innerWidth;
const height = canvas.height = window.innerWidth+30;
const ctx = canvas.getContext('2d');

const sizePicker = document.getElementById('bsize');
const backBtn = document.querySelector('.backBtn');
const forwBtn = document.querySelector('.forwBtn');
const clearBtn = document.querySelector('.clearBtn');

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
  nextys: []
};

function degToRad(degrees) {
  return degrees * Math.PI / 180;
};

function redraw(){
  ctx.fillStyle = 'rgb(0,0,255)';
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

function iselect(x){
  let ans=boardstate.xsize;
  for(let ii=0; ii<boardstate.xsize; ii++){
    if(x < xoffset+(ii+1)*stonesize){
      iselect = ii;
      break;
    }
  }
  return ans;
}

function drawhighlight(){
  let ii1 = iselect(curX);

  for(let jj=boardstate.nextys[iselect]; jj<boardstate.ysize; jj++){
    ctx.fillStyle = "rgb(0, 0, 0)";
    ctx.beginPath();
    ctx.arc(xoffset+(ii1+0.5)*stonesize,(jj+0.5)*stonesize , 0.5*stonesize-2, degToRad(0), degToRad(360), false);
    ctx.fill();
  }
}

function undrawhighlight(){}


// update sizepicker output value

sizePicker.onchange = ( () => {setSize(); redraw();} );


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
  curX = (window.Event) ? e.pageX : e.touches[0].clientX + (document.documentElement.scrollLeft ? document.documentElement.scrollLeft : document.body.scrollLeft);
  curY = (window.Event) ? e.pageY : e.touches[0].clientY + (document.documentElement.scrollTop ? document.documentElement.scrollTop : document.body.scrollTop);
  drawmove();
});

clearBtn.addEventListener('click', () => {
  redraw();
});
