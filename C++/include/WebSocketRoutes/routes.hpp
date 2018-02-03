#ifndef WebSocketRoutes_HPP
#define WebSocketRoutes_HPP

namespace Web {
  template<typename ServerType>
  class Routes {
  private:
    ServerType& server;

  public:
    Routes(ServerType&);
    void addRoute();
  };
} // namespace Web

#include "WebSocketRoutes/routes.hxx"

#endif
