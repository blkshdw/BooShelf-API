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
    auto authCTX = (Middleware::Auth::context*)req.middleware_context;
    if (authCTX->visitor->canRegister()){
        rapidjson::Document user_d;
        rapidjson::StringStream usr_ss(req.body.c_str());
        user_d.ParseStream(usr_ss);
        if (user_d.HasParseError() || !user_d.HasMember("username") || !user_d.HasMember("password")) {
            throw BooShelf::Http::UnprocessableEntityException("Payload is not a correct JSON object" + string(rapidjson::GetParseError_En(user_d.GetParseError())));
        }
        auto username = user_d["username"].GetString();
        auto password = user_d["password"].GetString();

        if (string(username).find_first_not_of(" \t\n\v\f\r") == std::string::npos) {
            throw Http::UnprocessableEntityException("Username is too short");
        }

        if (string(password).find_first_not_of(" \t\n\v\f\r") == std::string::npos) {
            throw Http::UnprocessableEntityException("Password is too short");
        }
        json::wvalue user;

        try {
            db.table("users").insert(R::json(json::dump(user))).run(*conn);
        } catch (R::Error err) {
            throw Http::DataBaseException(err.message);
        }
    }
    throw Http::AlreadyRegisteredException();
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

crow::response BooShelf::Route::login(std::shared_ptr<RethinkDB::Connection> &conn, const RethinkDB::Query& db, const crow::request &req) {
    auto authCTX = (Middleware::Auth::context*)req.middleware_context;
    if (authCTX->visitor->canLogin()) {
        rapidjson::Document user_d;
        rapidjson::StringStream usr_ss(req.body.c_str());
        user_d.ParseStream(usr_ss);
        if (user_d.HasParseError() || !user_d.HasMember("username") || !user_d.HasMember("password")) {
            throw BooShelf::Http::UnprocessableEntityException("Payload is not a correct JSON object" + string(rapidjson::GetParseError_En(user_d.GetParseError())));
        }
        auto username = user_d["username"].GetString();
        auto password = user_d["password"].GetString();
        try {
            R::Cursor cursor = db.table("users").filter(R::row["username"] == username && R::row["password"] == password).without(string("password")).run(*conn);
            for (R::Datum& userElem : cursor) {
                return crow::response(R::write_datum(userElem));
            }
        } catch (R::Error err) {
            throw Http::DataBaseException(err.message);
        }
        throw Http::UnprocessableEntityException("Wrong username or password");
    }
    throw Http::AlreadyLoggedInException();
}

crow::response BooShelf::Route::getUser(std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db, const crow::request &req, std::string userId) {
    auto authCTX = (Middleware::Auth::context*)req.middleware_context;
    if  (authCTX->visitor->canGetOtherProfile()) {
        try {
            R::Cursor cursor = db.table("users").get(userId).without(string("password"), string("token")).run(*conn);
            return crow::response(R::write_datum(cursor.to_datum()));
        } catch(R::Error err) {
            throw Http::DataBaseException(err.message);
        }
    }
    throw Http::AccessDeniedException();
}
