//
// Created by tetofakun on 29.03.16.
//

#include "auth.h"
#include "../exceptions/httpExceptions.h"

using namespace std;
using namespace BooShelf;
namespace R = RethinkDB;

RethinkDB::Query* Middleware::Auth::_db;
std::shared_ptr<RethinkDB::Connection> Middleware::Auth::_conn;


Middleware::Auth::Auth() {
}

void Middleware::Auth::setDB(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query& db) {
        _conn = conn;
        _db = new R::Query(db);
    }

void Middleware::Auth::before_handle(crow::request& req, crow::response& res, context& ctx) {
    auto token = req.get_header_value("Token");
    ctx.visitor = std::shared_ptr<GuestVisitor>(new GuestVisitor());
    try {
        R::Cursor cursor = _db->table("users").filter(R::row["token"] == token).without(string("password")).run(*_conn);
        for (R::Datum& user : cursor) {
            crow::json::rvalue userJSON = crow::json::load(R::write_datum(user));
            ctx.visitor = std::shared_ptr<UserVisitor>(new UserVisitor(userJSON));
        }
    } catch (R::Error err) {
        CROW_LOG_ERROR << err.message;
        throw Http::DataBaseException(err.message);
    }
}

void Middleware::Auth::after_handle(crow::request& req, crow::response& res, context& ctx) {
        // no-op
}
