const loopDeLaMort = () => {
  let i = 0;
  const a = [];
  while (i < 100000000) {
    a.push(i);
    i += 1;
  }
};
const getPath = (cb) => {
  console.log('begin');
  loopDeLaMort();
//   return ('done');
  return (cb(2));
};

// getPath().then((res) => {
//   console.log(res);
// });

calcDeOuf = (num1, num2, cb) => {
    return (cb(num1 + num2));
}

setTimeout( () => {
    getPath(successCallback = (res) => {
        console.log('done');
        calcDeOuf(res, 4, (res) => {
            console.log('le resultat est : ' + res);
        })
    })
}, 0);
console.log('sync');