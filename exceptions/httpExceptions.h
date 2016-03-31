//
// Created by blkshdw on 27.03.16.
//
#include <string>
#include "../crow_all.h"

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
            ~HttpException();
            crow::response response();
            crow::json::wvalue body();
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

    }
}

#endif //BOOSHELF_SERVER_HTTPEXCEPTIONS_H
