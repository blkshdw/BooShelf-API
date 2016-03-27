//
// Created by blkshdw on 27.03.16.
//
#include <string>
#include "../crow_all.h"

using namespace std;

#ifndef BOOSHELF_SERVER_HTTPEXCEPTIONS_H
#define BOOSHELF_SERVER_HTTPEXCEPTIONS_H

class HttpException {
private:
    string _message;
    int _status;
public:
    HttpException(string description, int status);
    crow::json::wvalue body();
    int status();
};

class NotFoundException: public HttpException{
public:
    NotFoundException();
    NotFoundException(string);
};

class AccessDeniedException: public HttpException{
public:
    AccessDeniedException();
    AccessDeniedException(string);
};


#endif //BOOSHELF_SERVER_HTTPEXCEPTIONS_H
