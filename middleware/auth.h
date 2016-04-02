//
// Created by tetofakun on 29.03.16.
//

#include "../crow_all.h"
#include "../access-rights/Visitor.h"
#include "../access-rights/GuestVisitor.h"
#include "../access-rights/UserVisitor.h"
#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>
#include <rethinkdb.h>
#include <string>

#ifndef BOOSHELF_SERVER_MIDDLEWARE_AUTH_H
#define BOOSHELF_SERVER_MIDDLEWARE_AUTH_H
namespace BooShelf {
    namespace Middleware {
        struct Auth {
        private:
            static RethinkDB::Query *_db;
            static std::shared_ptr<RethinkDB::Connection> _conn;
        public:
            Auth();
            void setDB(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query& db);

            struct context {
                std::shared_ptr<BooShelf::Visitor> visitor;
            };
            void before_handle(crow::request& req, crow::response& res, context& ctx);
            void after_handle(crow::request& req, crow::response& res, context& ctx);

        };
    }
}

#endif //BOOSHELF_SERVER_MIDDLEWARE_AUTH_H
