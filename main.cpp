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

namespace R = RethinkDB;
namespace json = crow::json;
using namespace std;

int main(){

    crow::App<BooShelf::Middleware::Auth> app;


    // CONFIG
    std::ifstream config_file("config.json");
    // DB CONFIG
    std::string config_str((std::istreambuf_iterator<char>(config_file)), std::istreambuf_iterator<char>());
    auto const config = json::load(config_str);
    auto const DB_host = config["database"]["host"].s();
    auto const DB_port = config["database"]["port"].i();
    string const DB_name = config["database"]["name"].s();
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
        cout << "res";
        return "Hello world";
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

    app.port(config["server"]["port"].i()).multithreaded().run();
}