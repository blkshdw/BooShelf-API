//
// Created by tetofag on 27.03.16.
//
#include "auth.h"
#include "../exceptions/httpExceptions.h"
#include "../crow_all.h"
#include <rethinkdb.h>

namespace R = RethinkDB;
using namespace std;

crow::json::wvalue checkAuth(std::unique_ptr<R::Connection>& conn, const R::Query& db, const crow::request& req) {
    auto token = req.get_header_value("Token");
    R::Cursor cursor = db.table("users").filter(R::row["token"] == token).run(*conn);
    for (R::Datum& user : cursor) {
        return crow::json::load(R::write_datum(user).c_str());
    }
    throw AccessDeniedException();
};