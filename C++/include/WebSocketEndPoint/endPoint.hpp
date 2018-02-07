#ifndef WebSocketEndPoint_HPP
#define WebSocketEndPoint_HPP

namespace WebSocket {
  template<typename ServerType>
  class EndPoint {
  private:
    ServerType& server;

  public:
    EndPoint(ServerType&);
    void addRoute();
  };
} // namespace Web

#include "WebSocketEndPoint/endPoint.hxx"

#endif
