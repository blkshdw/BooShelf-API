//
// Created by tetofag on 27.03.16.
//
#include "httpExceptions.h"
#include <string>
#include "../crow_all.h"

using namespace std;

HttpException::HttpException(string message, int status){
    _status = status;
    _message = message;
};

crow::json::wvalue HttpException::body(){
    crow::json::wvalue res;
    res["error"]["type"] = to_string(_status);
    res["error"]["message"] = _message;
    return res;
};

int HttpException::status(){
    return _status;
};

NotFoundException::NotFoundException(): HttpException(string("Not Found"), 404){

};


NotFoundException::NotFoundException(string message): HttpException(string("Not Found: " + message), 404) {

};

AccessDeniedException::AccessDeniedException(): HttpException(string("Access Denied"), 403){

};

AccessDeniedException::AccessDeniedException(string message): HttpException(string("Access Denied: " + message), 403) {

};
