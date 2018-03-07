#include "WebServerUrl/url.hpp"
#include "WebServer/server_http.hpp"

using namespace std;

namespace WebServer {
  template<typename ServerType>
  Url<ServerType>::Url(ServerType& s) : server(s) {
    urlError();
  }

  template<typename ServerType>
  void Url<ServerType>::addUrl() {
    // GET-example for the path /match/[number], responds with the matched string in path (number)
  	// For instance a request GET /match/123 will receive: 123
  	server.resource["^/match/([0-9]+)$"]["GET"] = [](shared_ptr<typename ServerType::Response> response, shared_ptr<typename ServerType::Request> request) {
  		response->write(request->path_match[1]);
  	};
  }

  template<typename ServerType>
  void Url<ServerType>::urlError() {
    server.on_error = [](shared_ptr<typename ServerType::Request> /*request*/, const SimpleWeb::error_code &/*ec*/) {
  		// Handle errors here
  		// Note that connection timeouts will also call this handle with ec set to SimpleWeb::errc::operation_canceled
  	};
  }

  /*httpServer.resource["^/arduino$"]["POST"] = [](shared_ptr<HttpServer::Response> response, shared_ptr<HttpServer::Request> request) {
    try {
      ptree pt;
      read_json(request->content, pt);
      string action = pt.get<string>("action");

      response->write(action);
    }
    catch(const exception &e) {
      response->write(SimpleWeb::StatusCode::client_error_bad_request, e.what());
    }
  };*/
}
