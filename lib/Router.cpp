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
        // Wait of incomming request
        clientSocket = serverSocket.accept();

        // Save address of incomming request in the clientAddress object
        clientSocket->getpeername(&clientAddress);

        // Receive the requet
        char requestBuffer[1500];
        clientSocket->recv(requestBuffer, 1500);

        // Extract infomatin from the request
        char separator[] = " ";
        std::vector<char*> requestInfo = Helpers::splitString(requestBuffer, separator);
        
        char* method = requestInfo[0];
        char* path = requestInfo[1];

        printf("method: %s path: %s\r\n", method, path);

        // Find the corret resolver by method and path
        RouteResolverFn resolver = findResolver(method, path);

        if (!resolver) {
            if (routeIsRegisteret(path)) {
                // TODO responde with unsupported method
                printf("TODO responde with unsupported method\r\n");
            }
            // TODO responde with a 404
            printf("TODO responde with a 404\r\n");
        }

        // Execute the resolver
        Request request;
        Response response = resolver(request);

        // Build the response as a string
        std::string result = response.build();

        printf("%s\r\n", result.c_str());

        // Send the response
        clientSocket->send(result.c_str(), result.length());

        // Close connection
        clientSocket->close();
    }
};

RouteResolverFn Router::findResolver(std::string method, std::string path) {
    if (method == "GET") {
        printf("Found GET resolver\r\n");
        return getResolversDict.at(path);
    }

    if (method == "POST") {
        printf("Found POST resolver\r\n");
        return postResolversDict.at(path);
    }

    printf("Found no resolver\r\n");
    RouteResolverFn emptyResolver;
    return emptyResolver;
};

bool Router::routeIsRegisteret(std::string path) {
    return getResolversDict.count(path) != 0
        || postResolversDict.count(path) != 0;
};