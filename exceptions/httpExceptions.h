//
// Created by blkshdw on 27.03.16.
//
#include "../crow_all.h"
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <rapidjson/document.h>
#include <string>

using namespace std;

#ifndef BOOSHELF_SERVER_HTTPEXCEPTIONS_H
#define BOOSHELF_SERVER_HTTPEXCEPTIONS_H

namespace BooShelf {
    namespace Http {

        class HttpException {
        private:
            string _message;
            int _status;
        public:
            HttpException(string, int);
            crow::response response();
            string body();
            int status();
        };

        class NotFoundException: public HttpException {
        public:
            NotFoundException();
            NotFoundException(string);
        };

        class AccessDeniedException: public HttpException {
        public:
            AccessDeniedException();
            AccessDeniedException(string);
        };

        class UnprocessableEntityException: public HttpException {
        public:
            UnprocessableEntityException ();
            UnprocessableEntityException(string);
        };

        class AlreadyLoggedInException: public UnprocessableEntityException {
        public:
            AlreadyLoggedInException ();
            AlreadyLoggedInException(string);
        };

        class AlreadyRegisteredException: public UnprocessableEntityException {
        public:
            AlreadyRegisteredException ();
            AlreadyRegisteredException(string);
        };

        class DataBaseException: public HttpException {
        public:
            DataBaseException ();
            DataBaseException(string);
        };

        class ServerErrorException: public HttpException {
        public:
            ServerErrorException ();
            ServerErrorException(string);
        };

    }
}

#endif //BOOSHELF_SERVER_HTTPEXCEPTIONS_H
