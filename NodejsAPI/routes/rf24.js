var express = require('express');
var webSocket = require('websocket').w3cwebsocket;

var router = express.Router();

router.get('/rf24', function(req, res) {
  var client = new webSocket('ws://localhost:8080/echo');

  client.onerror = function() {
    console.log('Connection Error');
  };

  client.onopen = function() {
    console.log('Client Connected');
    client.send("Hello");
  };

  client.onclose = function() {
    console.log('Client Closed');
  };

  client.onmessage = function(response) {
    if (typeof response.data === 'string') {
        console.log("Received: '" + response.data + "'");
        res.status(201).send(response.data);
    }
  };
});

module.exports = router;
