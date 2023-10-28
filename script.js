const canvas = document.querySelector('.myCanvas');
const width = canvas.width = window.innerWidth;
const height = canvas.height = window.innerWidth;
const ctx = canvas.getContext('2d');

const sizePicker = document.querySelector('.bsize');
const outputx = document.querySelector('.outputx');
const outputy = document.querySelector('.outputy');
const backBtn = document.querySelector('.backBtn');
const forwBtn = document.querySelector('.forwBtn');
const clearBtn = document.querySelector('.clearBtn');

let xsize;
let ysize;


function redraw(){
  ctx.fillStyle = 'rgb(0,0,0)';
  ctx.fillRect(0,0,width,height);
}

function setSizeRedraw(){
  if(sizePicker.
  xsize
}
// update sizepicker output value

//document.getElementbyId("bsize").onchange = redraw;
sizePicker.onchange = redraw;

xPicker.addEventListener('input', () => outputx.textContent = xPicker.value);

yPicker.addEventListener('input', () => outputy.textContent = yPicker.value);

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
  ctx.fillStyle = 'rgb(0,0,0)';
  ctx.fillRect(0,0,width,height);
});
