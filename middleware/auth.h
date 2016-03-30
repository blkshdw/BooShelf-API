//
// Created by tetofakun on 29.03.16.
//

#include "../crow_all.h"
#include <rethinkdb.h>
#include <string>

#ifndef BOOSHELF_SERVER_MIDDLEWARE_AUTH_H
#define BOOSHELF_SERVER_MIDDLEWARE_AUTH_H
namespace BooShelf {
    namespace Middleware {
        struct Auth {
        private:
            static RethinkDB::Query& _db;
            static std::unique_ptr<RethinkDB::Connection> _conn;
        public:
            Auth(std::unique_ptr<RethinkDB::Connection> &conn, const RethinkDB::Query &db);

            struct context {
                std::string message;
            };
            void before_handle(crow::request& req, crow::response& res, context& ctx);
            void after_handle(crow::request& req, crow::response& res, context& ctx);
        };
    }
}

#endif //BOOSHELF_SERVER_MIDDLEWARE_AUTH_H
