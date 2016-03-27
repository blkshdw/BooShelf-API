//
// Created by tetofag on 27.03.16.
//
#include "users.h"
#include "../../tools/auth.h"
#include "../../exceptions/httpExceptions.h"
#include "../../crow_all.h"
#include <rethinkdb.h>

namespace R = RethinkDB;
namespace json = crow::json;

crow::response Route::me(std::unique_ptr<R::Connection> &conn, const R::Query &db, const crow::request& req) {
    json::wvalue user;
    try {
        user = checkAuth(conn, db, req);
    } catch (HttpException error) {
        return crow::response(error.status(), error.body());
    };

    return crow::response(user);
}
