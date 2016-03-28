//
// Created by blkshdw on 27.03.16.
//
#include "httpExceptions.h"
#include <string>
#include "../crow_all.h"

using namespace std;

Http::HttpException::HttpException(string message, int status){
    _status = status;
    _message = message;
};

crow::json::wvalue Http::HttpException::body(){
    crow::json::wvalue res;
    res["error"]["type"] = to_string(_status);
    res["error"]["message"] = _message;
    return res;
};

int Http::HttpException::status(){
    return _status;
};

Http::NotFoundException::NotFoundException(): Http::HttpException(string("Not Found"), 404){

};


Http::NotFoundException::NotFoundException(string message): Http::HttpException(string("Not Found: " + message), 404) {

};

Http::AccessDeniedException::AccessDeniedException(): Http::HttpException(string("Access Denied"), 403){

};

Http::AccessDeniedException::AccessDeniedException(string message): Http::HttpException(string("Access Denied: " + message), 403) {

};

Http::UnprocessableEntityException::UnprocessableEntityException(): Http::HttpException(string("Unprocessable Entity"), 422){

};

Http::UnprocessableEntityException::UnprocessableEntityException(string message): Http::HttpException(string("Unprocessable Entity: " + message), 422) {

};

Http::AlreadyLoggedInException::AlreadyLoggedInException(): Http::UnprocessableEntityException(string("Aready Logged In")){

};

Http::AlreadyLoggedInException::AlreadyLoggedInException(string message): Http::UnprocessableEntityException(string("Aready Logged In: " + message)) {

};
