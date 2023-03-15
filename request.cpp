#include "request.h"

#include <cpr/parameters.h>

#include "errors.h"

cpr::Header Request::getHeaders() const {
    return headers;
}

void Request::setHeaders(const cpr::Header &newHeaders) {
    headers = newHeaders;
}

cpr::Header Request::request_headers(const string &token, const string &language) {
    return cpr::Header{{"X-Yandex-Music-Client", "YandexMusicAndroid/23020251"},
                       {"User-Agent", "Yandex-Music-API"},
                       {"Connection", "Keep-Alive"},
                       {"Authorization", "OAuth " + token},
                       {"Accept-Language", language}};
}

cpr::Response Request::Get(const cpr::Url &url, const cpr::Header &headers, const cpr::Timeout &timeout) {
    cpr::Response response = cpr::Get(url, headers);
    if (response.status_code < 200 || response.status_code > 299) {
        throw RequestError("Request Get Error");
    }
    return response;
}

cpr::Response Request::Post(const cpr::Url &url, const cpr::Header &headers, const cpr::Parameters &params,
                            const cpr::Body &body, const cpr::Timeout &timeout) {
    cpr::Response response = cpr::Post(url, body, params, headers);
    if (response.status_code < 200 || response.status_code > 299) {
        throw RequestError("Request Post Error");
    }
    return response;
}

Request::Request(const string &token, const string &language) {
    headers = request_headers(token, language);
}
