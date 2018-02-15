#ifndef DATABASE_MYSQL_HPP
#define DATABASE_MYSQL_HPP

/* MySQL */
#include <mysql_connection.h>
#include <driver.h>
#include <exception.h>
#include <resultset.h>
#include <statement.h>

namespace db {
  class MySQL {
  private:
    MySQL();
    MySQL(const MySQL&) = delete;
    ~MySQL();

    MySQL& operator=(const MySQL&) = delete;

    static MySQL instance;
    sql::Driver *driver;
    sql::Connection *connect;

  public:
    static MySQL& sharedInstance();

    void connection();
    void disconnection();
    void execute(std::string);
  };
} // namespace db

#endif
