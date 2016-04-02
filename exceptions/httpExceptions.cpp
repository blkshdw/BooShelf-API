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

string Http::HttpException::body(){
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Value error(rapidjson::kObjectType);
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    error.AddMember("type", rapidjson::Value(_status), allocator);
    rapidjson::Value mes_v;
    mes_v = rapidjson::StringRef(_message.c_str());
    error.AddMember("message", mes_v, allocator);
    document.AddMember("error", error, allocator);
    rapidjson::StringBuffer strbuf;
    rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
    document.Accept(writer);
    return strbuf.GetString();
};

crow::response Http::HttpException::response(){
    return crow::response(_status, this->body());
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

// 500 Data Base

Http::DataBaseException::DataBaseException(): Http::HttpException(string("RethinkDB Error"), 500){

};

Http::DataBaseException::DataBaseException(string message): Http::HttpException(string("RethinkDB Error: " + message), 500){

};

// 500 Server

Http::ServerErrorException::ServerErrorException(): Http::HttpException(string("Server Error"), 500) {

}

Http::ServerErrorException::ServerErrorException(string message): Http::HttpException(string("Server Error: " + message), 500) {

}

