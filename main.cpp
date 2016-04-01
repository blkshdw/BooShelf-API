// MIDDLEWARE
#include "middleware/auth.h"
// ROUTES
#include "routes/users/users.h"

// EXCEPTIONS
#include "exceptions/httpExceptions.h"

// LIBRARIES
#include "crow_all.h"
#include <rethinkdb.h>
#include <fstream>
#include <string>
#include <streambuf>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/istreamwrapper.h>
#include <rapidjson/stringbuffer.h>
#include <iostream>

namespace R = RethinkDB;
namespace json = crow::json;
using namespace std;

int main(){

    crow::App<BooShelf::Middleware::Auth> app;


    // CONFIG
    ifstream ifs("test.json");
    rapidjson::IStreamWrapper cfg(ifs);
    rapidjson::Document config;
    config.ParseStream(cfg);
    auto const DB_host = config["database"]["host"].GetString();
    auto const DB_port = config["database"]["port"].GetInt();
    string const DB_name = config["database"]["name"].GetString();
    std::shared_ptr<R::Connection> conn;
    try {
         conn = R::connect(DB_host, DB_port);
    } catch (R::Error err) {
        CROW_LOG_ERROR << "RethinkDB: " + err.message;
    }


    auto const db = R::db(DB_name);

    app.get_middleware<BooShelf::Middleware::Auth>().setDB(conn, db);

    CROW_ROUTE(app, "/me")
            .methods("GET"_method)
    ([&db, &conn] (const crow::request& req) {
        try {
            return BooShelf::Route::me(conn, db, req);
        } catch (BooShelf::Http::HttpException error) {
            return error.response();
        }
    });

    CROW_ROUTE(app, "/users")
            .methods("POST"_method)
    ([&db, &conn] (const crow::request& req) {
        try {
            return BooShelf::Route::createUser(conn, db, req);
        } catch (BooShelf::Http::HttpException error) {
            return error.response();
        }
    });

    crow::logger::setLogLevel(crow::LogLevel::DEBUG);

    app.port(config["server"]["port"].GetInt()).multithreaded().run();
}