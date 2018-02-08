#ifndef WEB_SOCKET_URL_HPP
#define WEB_SOCKET_URL_HPP

namespace WebServer {
  template<typename ServerType>
  class Url {
  private:
    ServerType& server;
    void urlError();

  public:
    Url(ServerType&);
    void addUrl();
  };
} // namespace WebServer

#include "WebServerUrl/url.hxx"

#endif
