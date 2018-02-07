# C++

### Dependencies
- [Simple-Web-Socket-Server library](https://github.com/eidheim/Simple-WebSocket-Server.git)
- [Simple-Web-Server](https://github.com/eidheim/Simple-Web-Server.git)
- [RF24](https://github.com/nRF24/RF24.git)

### Adding RF24
```shell
git clone https://github.com/nRF24/RF24.git
cd lib/RF24/
make all && sudo make install
```

#### Include & lib
include | lib
------- | ---
`/usr/local/include/RF24` | `/usr/local/lib/librf24.so`

```c++
#include <RF24/nRF24L01.h>
#include <RF24/RF24.h>
```

### Adding Boost
```shell
sudo apt-get install libboost-all-dev
```

#### Include & lib
include | lib
------- | ---
`/usr/include/boost` | `/usr/lib/x86-64-linux/`

### Adding MySQL
```shell
sudo apt-get install libmysqlcppconn-dev
```

#### Include & lib
include | lib
------- | ---
`/usr/include/cppconn` | `/usr/local/lib/libmysqlcppconn.so`

```c++
#include <mysql_connection.h>
#include <driver.h>
#include <exception.h>
#include <resultset.h>
#include <statement.h>
```

### Adding Configuration

```shell
mkdir ./include/Config
cd ./include/Config
touch db_config.hpp
```

```c++
// db_config.hpp
#ifndef DB_CONFIG_HPP
#define DB_CONFIG_HPP

#include <string>

namespace config {
  const std::string HOST = "HOST";
  const std::string USERNAME = "USERNAME";
  const std::string PASSWORD = "PASSWORD";
}

#endif
```

### Compile and Run
```shell
make
./bin/main
```
