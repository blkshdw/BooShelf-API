//
// Created by blkshdw on 27.03.16.
//
#include "../../models/validator/validator.h"
#include "../../models/book.h"
#include "../../middleware/auth.h"
#include "../../exceptions/httpExceptions.h"
#include "../../tools/token.h"
#include "../../crow_all.h"
#include <rethinkdb.h>
#ifndef BOOSHELF_SERVER_ROUTE_BOOKS_H
#define BOOSHELF_SERVER_ROUTE_BOOKS_H

namespace BooShelf {
    namespace Route {
        crow::response getBooks(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query& db, const crow::request &req);
        crow::response getBook(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query& db, const crow::request &req, std::string bookId);
        crow::response createBook(std::shared_ptr<RethinkDB::Connection> &conn, const RethinkDB::Query& db, const crow::request &req);
        crow::response updateBook(std::shared_ptr<RethinkDB::Connection> &conn, const RethinkDB::Query& db, const crow::request &req, std::string bookId);
    }
    namespace DEF_FILTERS {
        static const string DEF_ORDER_BY = "author";
    }
}
#endif //BOOSHELF_SERVER_ROUTE_BOOKS_H
