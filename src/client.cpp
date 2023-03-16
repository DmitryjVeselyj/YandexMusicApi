#include "client.h"

#include <iostream>

const string BASE_API_URL = "https://api.music.yandex.net";
const string BASE_OAUTH_URL = "https://oauth.yandex.ru/token";

Request Client::getRequest() const {
    return request;
}

void Client::setRequest(const Request &newRequest) {
    request = newRequest;
}

string Client::getApiUrl() const {
    return apiUrl;
}

void Client::setApiUrl(const string &newApiUrl) {
    apiUrl = newApiUrl;
}

Client::Client(const string &token, const string &language, const string &apiUrl, const string &oauthUrl) {
    this->token = token;
    this->language = language;
    this->request = Request(token, language);

    if (apiUrl.empty())
        this->apiUrl = BASE_API_URL;
    if (oauthUrl.empty())
        this->oauthUrl = BASE_OAUTH_URL;
}

void Client::initAccount() {
    accountStatus = requestAccountStatus();
}

json Client::requestAccountStatus() {
    return json::parse(request.Get(cpr::Url{apiUrl + "/account/status"}, request.getHeaders()).text);
}

json Client::userLikesTracks() {
    int uid = accountStatus["result"]["account"]["uid"];
    cpr::Url url = cpr::Url{apiUrl + "/users/" + std::to_string(uid) + "/likes/tracks"};
    cpr::Response response = request.Get(url, request.getHeaders());

    return json::parse(response.text);
}
