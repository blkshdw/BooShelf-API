//
// Created by blkshdw on 27.03.16.
//
#include "users.h"

namespace R = RethinkDB;
namespace json = crow::json;
using namespace BooShelf;

crow::response Route::me(shared_ptr<RethinkDB::Connection> conn, const R::Query& db, const crow::request& req) {
    auto authCTX = (Middleware::Auth::context*)req.middleware_context;
    if (authCTX->visitor->canGetOwnProfile()) {
        return crow::response(authCTX->visitor->getuserJSON());
    }
    else {
        throw Http::AccessDeniedException();
    }
}

crow::response Route::createUser(std::shared_ptr<R::Connection> &conn, const R::Query& db, const crow::request& req) {
    json::wvalue user;
    auto authCTX = (Middleware::Auth::context*)req.middleware_context;
    try {
        Auth::reqNotAuth(conn, db, req);
    } catch (Http::HttpException error) {
        throw error;
    };
    auto reqJson = json::load(req.body);

    string userName = reqJson["username"].s();
    string password = reqJson["password"].s();

    bool canRegister;
    try {
        canRegister = authCTX->visitor->canRegister(userName, password, conn, db);
    } catch(Http::HttpException error) {
        throw error;
    }
    if (canRegister){
        user["username"] = userName;
        user["password"] = password;
        user["token"] = Token::generate(userName, password);
        try {
            db.table("users").insert(R::json(json::dump(user))).run(*conn);
        } catch (R::Error err) {
            throw Http::DataBaseException(err.message);
        }
    }
    return crow::response(200);
}
