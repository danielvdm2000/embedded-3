#include "EthernetInterface.h"
#include "Router.h"
#include "Helpers.h"

Router::Router(EthernetInterface *net) {
    this->net = net;
};

void Router::get(std::string route, RouteResolverFn resolver) {
    getResolversDict.insert(
        std::pair<std::string, RouteResolverFn>(route, resolver)
    );
};

void Router::post(std::string route, RouteResolverFn resolver) {
    postResolversDict.insert(
        std::pair<std::string, RouteResolverFn>(route, resolver)
    );
};

void Router::listen(int port) {
    // Connect to the network
    net->connect();

    // Open the socket on the network
    serverSocket.open(this->net);

    // Bind the given port to the socket
    serverSocket.bind(port);

    // Specify number of clients the server can handle at once
    serverSocket.listen(1);

    // Print the ip
    net->get_ip_address(&clientAddress);
    const char* ip = clientAddress.get_ip_address();
    printf("Server running on %s:%d\r\n", ip ? ip : "None", port);

    while (true) {
        printf("Step: 1\r\n");

        // Wait of incomming request
        clientSocket = serverSocket.accept();

        printf("Step: 2\r\n");

        // Save address of incomming request in the clientAddress object
        clientSocket->getpeername(&clientAddress);

        printf("Step: 3\r\n");
        // Receive the requet
        char requestBuffer[1500];
        clientSocket->recv(requestBuffer, 1500);
        printf("%s\r\n", requestBuffer);

        printf("Step: 4\r\n");

        // Extract infomatin from the request
        char separator[] = " ";
        std::vector<char*> requestInfo = Helpers::splitString(requestBuffer, separator);
        
        char* method = requestInfo[0];
        char* path = requestInfo[1];

        printf("method: %s path: %s\r\n", method, path);

        printf("Step: 5\r\n");

        // Find the corret resolver by method and path
        RouteResolverFn resolver = findResolver(method, path);

        printf("Step: 6\r\n");

        if (!resolver) {
            if (routeIsRegisteret(path)) {
                // TODO responde with unsupported method
            }
            // TODO responde with a 404
        }

        printf("Step: 7\r\n");

        // Execute the resolver
        Request request;
        std::string response = resolver(request)->build();

        printf("Step: 8\r\n");

        // Send the response
        clientSocket->send(response.c_str(), response.length());

        printf("Step: 9\r\n");

        // Close connection
        clientSocket->close();

        printf("Step: 10\r\n");
    }
};

RouteResolverFn Router::findResolver(std::string method, std::string path) {
    if (method == "GET") {
        return getResolversDict[path];
    }

    if (method == "POST") {
        return postResolversDict[path];
    }

    RouteResolverFn emptyResolver;
    return emptyResolver;
};

bool Router::routeIsRegisteret(std::string path) {
    return getResolversDict.count(path) != 0
        || postResolversDict.count(path) != 0;
};