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
        return crow::response(authCTX->visitor->getUserString());
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

    string username = reqJson["username"].s();
    string password = reqJson["password"].s();

    if (username.find_first_not_of(" \t\n\v\f\r") == std::string::npos) {
        throw Http::UnprocessableEntityException("Username is too short");
    }

    if (password.find_first_not_of(" \t\n\v\f\r") == std::string::npos) {
        throw Http::UnprocessableEntityException("Password is too short");
    }

    R::Cursor cursor = db.table("users").filter(R::row["username"] == username).run(*conn);
    for (R::Datum& userElem : cursor) {
        throw Http::AlreadyRegisteredException();
    }

    if (authCTX->visitor->canRegister()){
        user["username"] = username;
        user["password"] = password;
        user["token"] = Token::generate(username, password);
        try {
            db.table("users").insert(R::json(json::dump(user))).run(*conn);
        } catch (R::Error err) {
            throw Http::DataBaseException(err.message);
        }
    }
    return crow::response(200);
}

crow::response BooShelf::Route::updateMe(std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db, const crow::request &req) {
    auto authCTX = (Middleware::Auth::context*)req.middleware_context;
    if (authCTX->visitor->canEditOwnProfile()) {
        try {
            BooShelf::Validator::validate(req.body, USER_SCHEMA);
        } catch (Http::HttpException err) {
            throw err;
        }
        auto userId = authCTX->visitor->getUserId();
        try {
            db.table("users").get(userId).update(R::json(req.body)).run(*conn);
            R::Cursor cursor = db.table("users").get(userId).run(*conn);
            return crow::response(R::write_datum(cursor.to_datum()));
        } catch(R::Error err) {
            throw Http::DataBaseException(err.message);
        }
    }
    else {
        throw Http::AccessDeniedException();
    }
}
