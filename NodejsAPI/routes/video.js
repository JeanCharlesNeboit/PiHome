const express = require('express');
//const jwt = require('express-jwt');
const raspividStream = require('raspivid-stream');
const expressWs = require('express-ws');

var router = express.Router();

/*var jwtCheck = jwt({
  secret: config.secretKey
});

router.use('/video-stream', jwtCheck);*/

router.ws('/video-stream', (ws, req) => {
    console.log('Client connected');

    ws.send(JSON.stringify({
      action: 'init',
      width: '960',
      height: '540'
    }));

    var videoStream = raspividStream({ rotation: 180 });

    videoStream.on('data', (data) => {
        ws.send(data, { binary: true }, (error) => { if (error) console.error(error); });
    });

    ws.on('close', () => {
        console.log('Client left');
        videoStream.removeAllListeners('data');
    });
});

router.use(function (err, req, res, next) {
  console.error(err);
  next(err);
})

router.use(express.static(__dirname));

module.exports = router;
