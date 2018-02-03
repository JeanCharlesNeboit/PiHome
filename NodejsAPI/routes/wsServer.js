const express = require('express');
const expressWs = require('express-ws');

var router = express.Router();

router.ws('/rf24', function(ws, req) {
  console.log('Server: Client connected ' + req.connection.remoteAddress);
});

module.exports = router;
