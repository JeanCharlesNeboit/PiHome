var mysql = require('mysql');
const db_config = require('./db_config.json');

var connection = null;
exports.connect = function() {
  connection = mysql.createConnection(db_config);
}

exports.get = function() {
  return connection;
}
