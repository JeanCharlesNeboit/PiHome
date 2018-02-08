#include <cstdlib>
#include <iostream>
#include <unistd.h>

#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

/* RF24 */
#include "RF24/nRF24L01.h"
#include "RF24/RF24.h"

/* WebSocketServer & WebServer */
#include "WebSocketServer/client_wss.hpp"
#include "WebSocketServer/server_wss.hpp"
#include "WebServer/client_https.hpp"
#include "WebServer/server_https.hpp"

/* WebSocketEndPoint & WebServerUrl */
#include "WebSocketEndPoint/endPoint.hpp"
#include "WebServerUrl/url.hpp"

#include "Database/mysql.hpp"

using namespace std;
using namespace boost::property_tree;

using WsServer = SimpleWeb::SocketServer<SimpleWeb::WS>;
using WsClient = SimpleWeb::SocketClient<SimpleWeb::WS>;
using WssServer = SimpleWeb::SocketServer<SimpleWeb::WSS>;
using WssClient = SimpleWeb::SocketClient<SimpleWeb::WSS>;

using HttpsServer = SimpleWeb::Server<SimpleWeb::HTTPS>;
using HttpsClient = SimpleWeb::Client<SimpleWeb::HTTPS>;
using HttpServer = SimpleWeb::Server<SimpleWeb::HTTP>;
using HttpClient = SimpleWeb::Client<SimpleWeb::HTTP>;

using EndPoint = WebSocket::EndPoint<WsServer>;
using Url = WebServer::Url<HttpServer>;

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
	/**
	* WebSocket Server
	*/

	//WssServer server("/etc/letsencrypt/archive/paoriginal.hopto.org/fullchain1.pem", "/etc/letsencrypt/archive/paoriginal.hopto.org/privkey1.pem");
	WsServer wsServer;
	wsServer.config.port = 8081;

	EndPoint endPoint(wsServer);
	endPoint.addRoute();

	thread wsServer_thread([&wsServer]() {
		// Start WS-server
		cout << "Starting WebSocket Server..." << endl;
		wsServer.start();
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

	/**
	* Web HTTP Server
	*/
	HttpServer httpServer;
	httpServer.config.port = 8080;

	Url url(httpServer);
	url.addUrl();

	thread httpServer_thread([&httpServer]() {
		// Start HTTP-server
		cout << "Starting HTTP Server..." << endl;
		httpServer.start();
	});

	// Wait for server to start so that the client can connect
	this_thread::sleep_for(chrono::seconds(1));

	/**
	* Wait Threads
	*/
	wsServer_thread.join();
	httpServer_thread.join();

	return 0;
}
