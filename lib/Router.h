#ifndef ROUTER
#define ROUTER

#include <string>
#include <map>
#include "EthernetInterface.h"
#include "Request.h"
#include "Response.h"

// Type definition of a route resolver
typedef Response* (*RouteResolverFn)(Request req);

class Router {
    private:
        EthernetInterface *net;
        TCPSocket serverSocket;
        TCPSocket *clientSocket;
        SocketAddress clientAddress;
        std::map<std::string, RouteResolverFn> getResolversDict;
        std::map<std::string, RouteResolverFn> postResolversDict;

        RouteResolverFn findResolver(std::string method, std::string path);
        bool routeIsRegisteret(std::string path);

    public:
        Router(EthernetInterface *net);

        void listen(int port);
        
        void get(std::string route, RouteResolverFn resolver);
        void post(std::string route, RouteResolverFn resolver);
};

#endif