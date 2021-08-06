#ifndef RESPONSE
#define RESPONSE

#include <string>

enum ContentType {
    HTML,
    Text,
};

enum StatusCode {
    _200,
};

class Response {
    private:
        StatusCode statusCode;
        std::string content;
        ContentType contentType;
        std::string statusCodeString(StatusCode code);
        std::string contentTypeString(ContentType type);

    public:
        Response* status(StatusCode code);
        Response* html(std::string content);
        Response* text(std::string content);
        std::string build();
};

#endif