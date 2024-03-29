// MIDDLEWARE
#include "middleware/auth.h"
// ROUTES
#include "routes/users/users.h"
#include "routes/books/books.h"

// EXCEPTIONS
#include "exceptions/httpExceptions.h"

// LIBRARIES
#include "crow_all.h"
#include "middleware/headers.h"
#include <rethinkdb.h>
#include <fstream>
#include <string>
#include <rapidjson/document.h>
#include <rapidjson/istreamwrapper.h>

namespace R = RethinkDB;
using namespace std;

int main(){

    crow::App<BooShelf::Middleware::Auth, BooShelf::Middleware::Headers> app;


    // CONFIG
    ifstream cfg_file("config.json");
    rapidjson::IStreamWrapper cfg_wrp(cfg_file);
    rapidjson::Document config;
    config.ParseStream(cfg_wrp);
    auto const DB_host = config["database"]["host"].GetString();
    auto const DB_port = config["database"]["port"].GetInt();
    string const DB_name = config["database"]["name"].GetString();
    std::shared_ptr<R::Connection> conn;
    try {
         conn = R::connect(DB_host, DB_port);
    } catch (R::Error err) {
        CROW_LOG_CRITICAL << "RethinkDB: " + err.message;
        throw err;
    }


    auto const db = R::db(DB_name);

    app.get_middleware<BooShelf::Middleware::Auth>().setDB(conn, db);

    CROW_ROUTE(app, "/me")
            .methods("GET"_method, "PUT"_method)
    ([&db, &conn] (const crow::request& req) {
        crow::response res;
        if (req.method == crow::HTTPMethod::GET) {
            try {
                return BooShelf::Route::me(conn, db, req);
            } catch (BooShelf::Http::HttpException error) {
                return error.response();
            }
        } else if (req.method == crow::HTTPMethod::PUT) {
            try {
                return BooShelf::Route::updateMe(conn, db, req);
            } catch (BooShelf::Http::HttpException error) {
                return error.response();
            }
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

    CROW_ROUTE(app, "/users/<string>")
            .methods("GET"_method)
    ([&db, &conn] (const crow::request& req, string userId) {
        try {
            return BooShelf::Route::getUser(conn, db, req, userId);
        } catch (BooShelf::Http::HttpException error) {
            return error.response();
        }
    });

    CROW_ROUTE(app, "/login")
            .methods("POST"_method)
    ([&db, &conn] (const crow::request& req) {
        try {
            return BooShelf::Route::login(conn, db, req);
        } catch (BooShelf::Http::HttpException error) {
            return error.response();
        }
    });

    CROW_ROUTE(app, "/books")
            .methods("GET"_method, "POST"_method)
    ([&db, &conn] (const crow::request& req) {
        crow::response res;
        if (req.method == crow::HTTPMethod::GET) {
            try {
                return BooShelf::Route::getBooks(conn, db, req);
            } catch (BooShelf::Http::HttpException error) {
                return error.response();
            }
        } else if (req.method == crow::HTTPMethod::POST) {
            try {
                return BooShelf::Route::createBook(conn, db, req);
            } catch (BooShelf::Http::HttpException error) {
                return error.response();
            }
        }
    });

    CROW_ROUTE(app, "/books/<string>")
            .methods("GET"_method, "PUT"_method)
    ([&db, &conn] (const crow::request& req, string bookId) {
        crow::response res;
        if (req.method == crow::HTTPMethod::GET) {
            try {
                return BooShelf::Route::getBook(conn, db, req, bookId);
            } catch (BooShelf::Http::HttpException error) {
                return error.response();
            }
        } else if (req.method == crow::HTTPMethod::PUT) {
            try {
                return BooShelf::Route::updateBook(conn, db, req, bookId);
            } catch (BooShelf::Http::HttpException error) {
                return error.response();
            }
        }
    });

    crow::logger::setLogLevel(crow::LogLevel::DEBUG);

    app.port(config["server"]["port"].GetInt()).multithreaded().run();
}