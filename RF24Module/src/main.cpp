// Unidirectionnel Transmitter

#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "RF24/nRF24L01.h"
#include "RF24/RF24.h"

using namespace std;

RF24 radio(22, 0);
const uint64_t address = 0xE8E8F0F0E1LL;

void setup() {
    // put your setup code here, to run once:

	// Transmitter
	radio.begin();
    	radio.openWritingPipe(address);
    	radio.setPALevel(RF24_PA_MIN);
    	radio.stopListening();
}

void loop() {
    // put your main code here, to run repeatedly:

    // Transmitter
    const char text[] = "Hello World";
    radio.write(&text, sizeof(text));
    sleep(1);
}

int main() {
	cout << "Raspberry Pi" << endl;
	setup();
	for(;;) {
		loop();
	}
	return 0;
}
