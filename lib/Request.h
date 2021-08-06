#ifndef REQUEST
#define REQUEST

#include <string>

class Request {
    public:
        Request();
        std::string header(std::string header_name);
};

#endif