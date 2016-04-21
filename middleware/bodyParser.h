//
// Created by tetofag on 11.04.16.
//
#include "../crow_all.h"
#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>
#ifndef BOOSHELF_SERVER_MIDDLEWARE_BODYPARSER_H
#define BOOSHELF_SERVER_MIDDLEWARE_BODYPARSER_H
namespace BooShelf {
    namespace Middleware {
        struct bodyParser {
        public:
            bodyParser();

            rapidjson::Document getDocument();
            struct context {
            };
            void before_handle(crow::request& req, crow::response& res, context& ctx);
            void after_handle(crow::request& req, crow::response& res, context& ctx);

        };
    }
}

#endif //BOOSHELF_SERVER_MIDDLEWARE_BODYPARSER_H
