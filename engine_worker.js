
var estate;

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
    //estate.resize(e.data.bs.xsize,e.data.bs.ysize);
    //estate = new Module.engineState(9,9);
    //estate.resize0();
    //doBatch();
    postMessage([9]);
  }

  if (e.data.msg == "stop"){
    //clearTimeout(timeoutID);
  }

  if (e.data.msg =="wasm"){
    const mod = e.data.m;

    WebAssembly.instantiate(mod).then((instance) => {
      instance.exports.exported_func();
    });
    postMessage([9]);
  }
};


