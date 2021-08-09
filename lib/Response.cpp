#include "Response.h"

Response Response::status(StatusCode status) {
    this->statusCode = status;
    return *this;
};

Response Response::html(std::string content) {
    this->content = content;
    this->contentType = ContentType::HTML;
    return *this;
};

Response Response::text(std::string content) {
    this->content = content;
    this->contentType = ContentType::Text;
    return *this;
};

bool Response::isValid() {
    if (!this->content.length()) {
        printf("No content provided to the response\r\n");
        return false;
    }

    if (!this->contentType) {
        printf("No content-type provided to the response\r\n");
        return false;
    }

    if (!this->statusCode) {
        printf("No status code provided to the response\r\n");
        return false;
    }

    return true;
};

std::string Response::build() {
    // Add the content to the start of the result
    std::string result;

    // Add status line
    result.append("HTTP/1.0 " + statusCodeString(statusCode) + "\n");

    // Add headers
    result.append("Content-Type: " + contentTypeString(contentType) + "\n");
    result.append("Content-Length: " + std::to_string(content.length()) + "\n");
    result.append("Connection: Closed\n");
    result.append("\n");

    // Add content
    result.append(content);

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