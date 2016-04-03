//
// Created by tetofag on 02.04.16.
//
#include "../crow_all.h"
#ifndef BOOSHELF_SERVER_MIDDLEWARE_HEADERS_H
#define BOOSHELF_SERVER_MIDDLEWARE_HEADERS_H
namespace BooShelf {
    namespace Middleware {
        struct Headers {
        public:
            Headers();

            struct context {
            };
            void before_handle(crow::request& req, crow::response& res, context& ctx);
            void after_handle(crow::request& req, crow::response& res, context& ctx);

        };
    }
}

#endif //BOOSHELF_SERVER_MIDDLEWARE_HEADERS_H
