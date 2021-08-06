#include "Response.h"

Response* Response::status(StatusCode status) {
    this->statusCode = status;
    return this;
};

Response* Response::html(std::string content) {
    this->content = content;
    this->contentType = ContentType::HTML;
    return this;
};

Response* Response::text(std::string content) {
    this->content = content;
    this->contentType = ContentType::Text;
    return this;
};

std::string Response::build() {
    // Add the content to the start of the result
    std::string result = content;

    // Add status code header
    result.append("HTTP/1.0 ");
    result.append(statusCodeString(statusCode));
    result.append("\r\n");

    // Add content type header
    result.append("Content-Type: ");
    result.append(contentTypeString(contentType));
    result.append("\r\n");

    // Add content length
    result.append("Content-Length: ");
    result.append(std::to_string(content.length()));
    result.append("\r\n");

    return result;
};

std::string Response::contentTypeString(ContentType type) {
    switch (type) {
        case ContentType::HTML:
            return "text/html";

        case ContentType::Text:
            return "text/plain";
    }
};

std::string Response::statusCodeString(StatusCode code) {
    switch (code) {
        case StatusCode::_200:
            return "200 OK";
    }
};