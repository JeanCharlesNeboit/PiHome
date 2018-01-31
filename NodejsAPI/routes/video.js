/*const express = require('express');
const raspividStream = require('raspivid-stream');
const expressWs = require('express-ws');

var router = module.exports = express.Router();*/

var router = require('../app.js')

router.get('/hello', function(req, res) {
  res.send("hello world");
})

/*router.ws('/video-stream', (ws, req) => {
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
});*/
