importScripts("engine/engine.js");

var estate = new Module.engineState(9,9); 

onmessage = (e) => {
  if (e.data.msg == "start"){
    estate.resize(e.data.bs.xsize,e.data.bs.ysize);
  }
    
};


