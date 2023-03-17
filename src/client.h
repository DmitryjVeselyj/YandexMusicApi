#ifndef CLIENT_H
#define CLIENT_H
#include "request.h"
#include "types.h"

extern const string BASE_API_URL;
extern const string BASE_OAUTH_URL;

class Client {
private:
    string apiUrl, oauthUrl;
    string token;
    string language;
    json accountStatus;
    Request request;

public:
    Client() = default;
    Client(const string &token, const string &language = "ru", const string &apiUrl = "", const string &oauthUrl = "");
    void initAccount();
    json requestAccountStatus();
    json userLikesTracks();
    Request getRequest() const;
    void setRequest(const Request &newRequest);
    string getApiUrl() const;
    void setApiUrl(const string &newApiUrl);
};

#endif // CLIENT_H
