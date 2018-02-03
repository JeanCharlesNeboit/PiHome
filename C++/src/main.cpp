#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "RF24/nRF24L01.h"
#include "RF24/RF24.h"
#include "WebSocket/client_wss.hpp"
#include "WebSocket/server_wss.hpp"
#include "WebSocketRoutes/routes.hpp"

using namespace std;

using WsServer = SimpleWeb::SocketServer<SimpleWeb::WS>;
using WsClient = SimpleWeb::SocketClient<SimpleWeb::WS>;
using WssServer = SimpleWeb::SocketServer<SimpleWeb::WSS>;
using WssClient = SimpleWeb::SocketClient<SimpleWeb::WSS>;

using Route = Web::Routes<WsServer>;

/*RF24 radio(22, 0);
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
}*/

int main() {
	//WssServer server("/etc/letsencrypt/archive/paoriginal.hopto.org/fullchain1.pem", "/etc/letsencrypt/archive/paoriginal.hopto.org/privkey1.pem");
	WsServer server;
  server.config.port = 8080;

	Route route(server);
	route.addRoute();

  thread server_thread([&server]() {
    // Start WS-server
    server.start();
  });

  // Wait for server to start so that the client can connect
  this_thread::sleep_for(chrono::seconds(1));

	/*WsClient client("localhost:3000/rf24");
	client.on_message = [](shared_ptr<WsClient::Connection> connection, shared_ptr<WsClient::Message> message) {
    cout << "Client: Message received: \"" << message->string() << "\"" << endl;

    cout << "Client: Sending close connection" << endl;
    connection->send_close(1000);
  };

  client.on_open = [](shared_ptr<WsClient::Connection> connection) {
    cout << "Client: Opened connection" << endl;

    string message = "Hello";
    cout << "Client: Sending message: \"" << message << "\"" << endl;

    auto send_stream = make_shared<WsClient::SendStream>();
    *send_stream << message;
    connection->send(send_stream);
  };

  client.on_close = [](shared_ptr<WsClient::Connection>, int status, const string &) {
    cout << "Client: Closed connection with status code " << status << endl;
  };

  // See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
  client.on_error = [](shared_ptr<WsClient::Connection>, const SimpleWeb::error_code &ec) {
    cout << "Client: Error: " << ec << ", error message: " << ec.message() << endl;
  };

  client.start();*/
	server_thread.join();

	return 0;
}
