#include "WebSocketEndPoint/endPoint.hpp"

using namespace std;

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
      //cout << "Client Header: \"" << connection.get()->header.find("User-Agent")->second << "\"" << endl;

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
