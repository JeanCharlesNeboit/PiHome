#include "API/listen.hpp"
#include <iostream>
#include <unistd.h>

/* RF24 */
#include "RF24/nRF24L01.h"
#include "RF24/RF24.h"

/* MySQL */
#include "Database/mysql.hpp"

using namespace std;

namespace api {
  void listen() {
    std::cout << "Listen Client" << std::endl;

    RF24 radio(22, 0);
    char buffer[50] = "";
    const uint64_t readAddress = 0xE8E8F0F0E4LL;
    uint8_t pipe = -1;

    radio.begin();
    radio.openReadingPipe(2, readAddress);
    radio.setPALevel(RF24_PA_MIN);
    radio.startListening();

    while(1) {
      if (radio.available(&pipe)) {
        if (pipe == 2) {
          cout << "Received" << endl;
          radio.read(buffer, sizeof(buffer));
          cout << buffer << endl;
          db::MySQL::sharedInstance().execute("INSERT INTO Temperature (temperature, humidite, date, idRaspberry) VALUES("+string(buffer)+","+string(buffer)+",NOW(),"+to_string(1)+")");
        }
      }
      usleep(10000);
    }
  }
}
