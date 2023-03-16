#ifndef ERRORS_H
#define ERRORS_H
#include "types.h"
#include <exception>

class APIException : public std::exception {
public:
    APIException() = default;
    explicit APIException(const string &err) : message(err){};
    virtual const char *what() const noexcept {
        return message.c_str();
    }
    virtual ~APIException(){};

private:
    string message;
};

class RequestError : public APIException {
public:
    explicit RequestError(const string &err = "Request Error") : APIException(err){};
};

class BitrateError : public APIException {
public:
    explicit BitrateError(const string &err = "Invalid Bitrate") : APIException(err){};
};

class PathError : public APIException {
public:
    explicit PathError(const string &err = "Invalid Path") : APIException(err){};
};

#endif // ERRORS_H
