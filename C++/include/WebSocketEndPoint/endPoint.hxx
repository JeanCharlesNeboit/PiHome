#include "WebSocketEndPoint/endPoint.hpp"
#include "WebSocketServer/server_ws.hpp"

/* RF24 */
#include "RF24/nRF24L01.h"
#include "RF24/RF24.h"

/* JSON */
#define BOOST_SPIRIT_THREADSAFE
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

using namespace std;
using namespace boost::property_tree;

namespace WebSocket {
  template<typename ServerType>
  EndPoint<ServerType>::EndPoint(ServerType& s) : server(s) {

  }

  template<typename ServerType>
  void EndPoint<ServerType>::addRoute() {
    auto &echo = server.endpoint["^/echo/?$"];

    echo.on_message = [](shared_ptr<typename ServerType::Connection> connection, shared_ptr<typename ServerType::Message> message) {
      auto message_str = message->string();

      cout << "Server: Message received: \"" << message_str << "\" from " << connection.get() << endl;
      cout << "Client IP: \"" << connection.get()->remote_endpoint_address() << "\"" << endl;
      cout << "Client Header: \"" << connection.get()->header.find("User-Agent")->second << "\"" << endl;

      ptree pt;
      stringstream ss(message_str);
			read_json(ss, pt);
			string type = pt.get<string>("type");
      cout << "Type: " << type << endl;


      #ifdef __arm__
      RF24 radio(22, 0);
			const uint64_t address = 0xE8E8F0F0E1LL;

			radio.begin();
			radio.openWritingPipe(address);
			radio.setPALevel(RF24_PA_MIN);
			radio.stopListening();
			radio.write(message_str.c_str(), message_str.size());
      #endif

      cout << "Server: Sending message \"" << message_str << "\" to " << connection.get() << endl;

      auto send_stream = make_shared<typename ServerType::SendStream>();
      *send_stream << message_str;
      // connection->send is an asynchronous function
      connection->send(send_stream, [](const SimpleWeb::error_code &ec) {
        if(ec) {
          cout << "Server: Error sending message. " <<
              // See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
              "Error: " << ec << ", error message: " << ec.message() << endl;
        }
      });
    };

    echo.on_open = [](shared_ptr<typename ServerType::Connection> connection) {
      cout << "Server: Opened connection " << connection.get() << endl;
    };

    // See RFC 6455 7.4.1. for status codes
    echo.on_close = [](shared_ptr<typename ServerType::Connection> connection, int status, const string &) {
      cout << "Server: Closed connection " << connection.get() << " with status code " << status << endl;
    };

    // See http://www.boost.org/doc/libs/1_55_0/doc/html/boost_asio/reference.html, Error Codes for error code meanings
    echo.on_error = [](shared_ptr<typename ServerType::Connection> connection, const SimpleWeb::error_code &ec) {
      cout << "Server: Error in connection " << connection.get() << ". "
           << "Error: " << ec << ", error message: " << ec.message() << endl;
    };
  }
}
