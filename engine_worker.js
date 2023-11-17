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
  if (e.data.msg == "init"){
    estate=e.data.es;
    postMessage([estate.getP(0),0,0,0,0,0,0,0,0]);
  }
  else if (e.data.msg == "start"){
    //estate.resize(e.data.bs.xsize,e.data.bs.ysize);
    //estate.resize0();
    //doBatch();
    postMessage([9,9,9,9,9,9,9,9,9]);
  }
  else if (e.data.msg == "stop"){
    //clearTimeout(timeoutID);
  }
  //postMessage([9]);
};


