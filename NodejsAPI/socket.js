var server = require('./bin/www');
var socket_io = require('socket.io')(server);

socket_io.on('connection', function(socket) {
    console.log('user connected');

    socket.on('disconnect', function() {
        console.log('user disconnected');
    });

    socket.on('send', function(msg) {
      console.log('msg: ' + msg);
    });
});
