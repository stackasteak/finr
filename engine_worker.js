importScripts("engine/engine.js");

var estate = new Module.engineState(9,9); 

var timeoutID;
function doBatch(){
  estate.batch();
  let p =[];
  for( let ii=0; ii<estate.getNX(); ii++){
    p.push(estate.getP(ii));
  }
  postMessage(p);
  timeoutID = setTimeout(doBatch,2000);
}

onmessage = (e) => {
  if (e.data.msg == "start"){
    estate.resize(e.data.bs.xsize,e.data.bs.ysize);
    doBatch();
  }

  if (e.data.msg == "stop"){
    clearTimeout(timeoutID);
  }
    
};


