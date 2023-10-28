const canvas = document.querySelector('.myCanvas');
const width = canvas.width = window.innerWidth;
const height = canvas.height = window.innerHeight-85;
const ctx = canvas.getContext('2d');

ctx.fillStyle = 'rgb(0,0,0)';
ctx.fillRect(0,0,width,height);


const xPicker = document.querySelector('.rangex');
const yPicker = document.querySelector('.rangey');
const outputx = document.querySelector('.outputx');
const outputy = document.querySelector('.outputy');
const backBtn = document.querySelector('.backBtn');
const forwBtn = document.querySelector('.forwBtn');
const clearBtn = document.querySelector('.clearBtn');

// update sizepicker output value

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
