//
// Created by blkshdw on 27.03.16.
//
#include "httpExceptions.h"

using namespace std;
using namespace BooShelf;

Http::HttpException::HttpException(string message, int status){
    _status = status;
    _message = message;
};

crow::json::wvalue Http::HttpException::body(){
    crow::json::wvalue body;
    body["error"]["type"] = to_string(_status);
    body["error"]["message"] = _message;
    return body;
};

crow::response Http::HttpException::response(){
    return crow::response(_status, crow::json::dump(this->body()));
};

int Http::HttpException::status(){
    return _status;
};

// 404
Http::NotFoundException::NotFoundException(): Http::HttpException(string("Not Found"), 404){

};

// 403
Http::NotFoundException::NotFoundException(string message): Http::HttpException(string("Not Found: " + message), 404) {

};

Http::AccessDeniedException::AccessDeniedException(): Http::HttpException(string("Access Denied"), 403){

};

Http::AccessDeniedException::AccessDeniedException(string message): HttpException(string("Access Denied: " + message), 403) {

};

// 400
Http::UnprocessableEntityException::UnprocessableEntityException(): Http::HttpException(string("Unprocessable Entity"), 400){

};

Http::UnprocessableEntityException::UnprocessableEntityException(string message): Http::HttpException(string("Unprocessable Entity: " + message), 400) {

};

Http::AlreadyLoggedInException::AlreadyLoggedInException(): Http::UnprocessableEntityException(string("Aready Logged In")){

};

Http::AlreadyLoggedInException::AlreadyLoggedInException(string message): Http::UnprocessableEntityException(string("Aready Logged In: " + message)) {

};

Http::AlreadyRegisteredException::AlreadyRegisteredException(): Http::UnprocessableEntityException(string("Aready Registered")){

};

Http::AlreadyRegisteredException::AlreadyRegisteredException(string message): Http::UnprocessableEntityException(string("Already Registered: " + message)) {

};

// 500

Http::DataBaseException::DataBaseException(): Http::HttpException(string("RethinkDB Error"), 500){

};

Http::DataBaseException::DataBaseException(string message): Http::HttpException(string("RethinkDB Error: " + message), 500){

};

