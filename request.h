#ifndef REQUEST_H
#define REQUEST_H
#include "types.h"
#include <cpr/cpr.h>

class Request {
private:
    cpr::Header headers;

public:
    Request() = default;
    Request(const string &token, const string &language);
    cpr::Header getHeaders() const;
    void setHeaders(const cpr::Header &newHeaders);
    static cpr::Header request_headers(const string &token, const string &language);
    static cpr::Response Get(const cpr::Url &url, const cpr::Header &headers = {}, const cpr::Timeout &timeout = 5);
    static cpr::Response Post(const cpr::Url &url, const cpr::Header &headers = {}, const cpr::Parameters &params = {}, const cpr::Body &body = {}, const cpr::Timeout &timeout = 5);
};

#endif // REQUEST_H
