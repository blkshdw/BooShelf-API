//
// Created by blkshdw on 27.03.16.
//
#include "users.h"
#include "../../middleware/auth.h"
#include "../../tools/auth.h"
#include "../../exceptions/httpExceptions.h"
#include "../../tools/token.h"
#include "../../crow_all.h"
#include <rethinkdb.h>

namespace R = RethinkDB;
namespace json = crow::json;
using namespace BooShelf;

crow::response Route::me(std::unique_ptr<R::Connection> &conn, const R::Query &db, const crow::request& req) {
    json::wvalue user;
    auto a = (ExampleMiddleware::context*)req.middleware_context;
    try {
        user = Auth::reqAuth(conn, db, req);
    } catch (Http::HttpException error) {
        return crow::response(error.status(), error.body());
    };

    return crow::response(user);
}

crow::response Route::createUser(std::unique_ptr<R::Connection> &conn, const R::Query &db, const crow::request& req) {
    json::wvalue user;

    try {
        Auth::reqNotAuth(conn, db, req);
    } catch (Http::HttpException error) {
        return crow::response(error.status(), error.body());
    };
    auto reqJson = json::load(req.body);
    string userName = reqJson["username"].s();
    string password = reqJson["password"].s();

    if (userName.find_first_not_of(" \t\n\v\f\r") == std::string::npos) {
        auto response = Http::UnprocessableEntityException("Username is too short");
        return crow::response(response.status(), response.body());
    }

    if (password.find_first_not_of(" \t\n\v\f\r") == std::string::npos) {
        auto response = Http::UnprocessableEntityException("Password is too short");
        return crow::response(response.status(), response.body());
    }

    auto a = &req.middleware_context;

    R::Cursor cursor = db.table("users").filter(R::row["username"] == userName).run(*conn);
    for (R::Datum& userElem : cursor) {
        auto response = Http::AlreadyRegisteredException();
        return crow::response(response.status(), response.body());
    }

    user["username"] = userName;
    user["password"] = password;
    user["token"] = Token::generate(userName, password);
    try {
        db.table("users").insert(R::json(json::dump(user))).run(*conn);
    } catch (R::Error err) {
        auto response = Http::DataBaseException(err.message);
        return crow::response(response.status(), response.body());
    }

    return crow::response(200);
}
