#include "Database/mysql.hpp"
#include <iostream>

/* Configuration */
#include "Config/config.hpp"

using namespace std;
using namespace sql;

namespace db {
  MySQL::MySQL() {
    connection();
  }

  MySQL::~MySQL() {
    if (connect) {
      connect->close();
    }

    delete connect;
    driver->threadEnd();
  }

  MySQL& MySQL::sharedInstance() {
    return instance;
  }

  void MySQL::connection() {
    try {
  		driver = get_driver_instance();
  		connect = driver->connect(config::HOST, config::USERNAME, config::PASSWORD);
      connect->setSchema(config::DATABASE);
  		if (connect) {
  			cout << "Connected to database" << endl;
  		}
  	}
  	catch (SQLException &e) {
  		cout << "# ERR: " << e.what();
  		cout << " (MySQL error code: " << e.getErrorCode();
  		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
  	}
  }

  void MySQL::disconnection() {
    try {
      connect->close();
      delete connect;
      driver->threadEnd();
      cout << "Disconnected to database" << endl;
    }
    catch(SQLException &e) {
      cout << "# ERR: " << e.what();
  		cout << " (MySQL error code: " << e.getErrorCode();
  		cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
  }

  void MySQL::execute(string request) {
    sql::Statement *stmt;
    try {
      stmt = connect->createStatement();
      stmt->executeQuery(request);
      delete stmt;
    }
    catch(SQLException &e) {
      cout << "# ERR: " << e.what();
      cout << " (MySQL error code: " << e.getErrorCode();
      cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
  }

  MySQL MySQL::instance;
}
