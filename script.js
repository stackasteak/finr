const canvas = document.querySelector('.myCanvas');
const width = canvas.width = window.innerWidth;
const height = canvas.height = window.innerWidth;
const ctx = canvas.getContext('2d');

const sizePicker = document.getElementById('bsize');
const backBtn = document.querySelector('.backBtn');
const forwBtn = document.querySelector('.forwBtn');
const clearBtn = document.querySelector('.clearBtn');

let xsize=9;
let ysize=9;

function degToRad(degrees) {
  return degrees * Math.PI / 180;
};

function redraw(){
  ctx.fillStyle = 'rgb(0,0,255)';
  ctx.fillRect(0,0,width,height);

  

  let stonesize;
  let xoffset=0;
  if(xsize>ysize){
    stonesize = width/xsize;
  }
  else{
    stonesize = width/ysize;
    xoffset = (width-stonesize*xsize)/2;
  }

  for(let ii=0; ii<xsize; ii++){
    for(let jj=0; jj<ysize; jj++){
      ctx.fillStyle = "rgb(0, 0, 0)";
      ctx.beginPath();
      ctx.arc(xoffset+(ii+0.5)*stonesize,(jj+0.5)*stonesize , 0.5*stonesize, degToRad(0), degToRad(360), false);
      ctx.fill();
    }
  }

  ctx.fillStyle = 'rgb(0,0,0)'; 
  ctx.fillRect(0, stonesize*ysize, width, height);
}

function setSize(){
  if(sizePicker.value =="6x7"){
    xsize = 7;
    ysize = 6;
  }
  if(sizePicker.value =="8x8"){
    xsize = 8;
    ysize = 8;
  }
  if(sizePicker.value =="9x9"){
    xsize = 9;
    ysize = 9;
  }
  if(sizePicker.value =="10x10"){
    xsize = 10;
    ysize = 10;
  }
}
// update sizepicker output value

//document.getElementbyId("bsize").onchange = redraw;
sizePicker.onchange = ( () => {setSize(); redraw();} );


// store mouse pointer coordinates, and whether the button is pressed
let curX;
let curY;
let pressed = false;

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
}
);

canvas.addEventListener('touchend', () => pressed = false);

clearBtn.addEventListener('click', () => {
  redraw();
});
