//
// Created by blkshdw on 27.03.16.
//
#include "../../models/validator/validator.h"
#include "../../models/user.h"
#include "../../middleware/auth.h"
#include "../../tools/auth.h"
#include "../../exceptions/httpExceptions.h"
#include "../../tools/token.h"
#include "../../crow_all.h"
#include <rethinkdb.h>
#ifndef BOOSHELF_SERVER_BOOKS_H
#define BOOSHELF_SERVER_BOOKS_H

namespace BooShelf {
    namespace Route {
        crow::response getBooks(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query& db, const crow::request &req);
        crow::response getBooks(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query& db, const crow::request &req, std::string userId);
        crow::response getBook(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query& db, const crow::request &req, std::string book);
        crow::response createBook(std::shared_ptr<RethinkDB::Connection> &conn, const RethinkDB::Query& db, const crow::request &req);
        crow::response updateBook(std::shared_ptr<RethinkDB::Connection> &conn, const RethinkDB::Query& db, const crow::request &req);
    }
    namespace DEF_FILTERS {
        static const string DEF_ORDER_BY = "author";
        static const string DEF_AUTHOR_FILTER = ".";
        static const string DEF_GENRE_FILTER = ".";
        static const string DEF_TITLE_FILTER = ".";
    }
}
#endif //BOOSHELF_SERVER_BOOKS_H
