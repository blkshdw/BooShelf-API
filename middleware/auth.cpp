//
// Created by tetofakun on 29.03.16.
//

#include "auth.h"
#include "../exceptions/httpExceptions.h"

using namespace std;
using namespace BooShelf;
namespace R = RethinkDB;

Middleware::Auth::Auth() {

}


void Middleware::Auth::setDB(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query& db) {
        _conn = conn;
        _db = db;
}

void Middleware::Auth::before_handle(crow::request& req, crow::response& res, context& ctx) {
        auto token = req.get_header_value("Token");
        R::Cursor cursor = _db.table("users").filter(R::row["token"] == token).without(string("password")).run(*_conn);
        for (R::Datum& user : cursor) {
                auto visitor = BooShelf::UserVisitor(crow::json::load(R::write_datum(user)));
                *ctx.visitor = visitor;
        }
        auto visitor = BooShelf::GuestVisitor();
        *ctx.visitor = visitor;
}

void Middleware::Auth::after_handle(crow::request& req, crow::response& res, context& ctx) {
        // no-op
}
