#ifndef WEB_SOCKET_END_POINT_HPP
#define WEB_SOCKET_END_POINT_HPP

namespace WebSocket {
  template<typename ServerType>
  class EndPoint {
  private:
    ServerType& server;

  public:
    EndPoint(ServerType&);
    void addRoute();
  };
} // namespace WebSocket

#include "WebSocketEndPoint/endPoint.hxx"

#endif
