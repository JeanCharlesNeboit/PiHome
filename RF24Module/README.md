# RF24Module
## RF24 library dependencies
```shell
cd lib/RF24/
make all && sudo make install
```

- Installing Libs to **/usr/local/lib** for name `librf24.so.1.3.0`
- Installing Headers to **/usr/local/include/RF24**
``` c++
#include <RF24/nRF24L01.h>
#include <RF24/RF24.h>
```


## Run
Run as **root** to allow access to `bcm2835`
```shell
sudo ./build/main
```
