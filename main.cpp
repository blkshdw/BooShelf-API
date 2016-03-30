// MIDDLEWARE
#include "middleware/auth.h"
// ROUTES
#include "routes/users/users.h"

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

    // CONFIG
    std::ifstream config_file("config.json");
    // DB CONFIG
    std::string config_str((std::istreambuf_iterator<char>(config_file)), std::istreambuf_iterator<char>());
    auto const config = json::load(config_str);
    auto const DB_host = config["database"]["host"].s();
    auto const DB_port = config["database"]["port"].i();
    string const DB_name = config["database"]["name"].s();
    std::unique_ptr<R::Connection> conn = R::connect(DB_host, DB_port);
    auto const db = R::db(DB_name);

    crow::App<BooShelf::Middleware::Auth(conn, db)> app;

    CROW_ROUTE(app, "/me")
            .methods("GET"_method)
    ([&db, &conn] (const crow::request& req) {
        return BooShelf::Route::me(conn, db, req);
    });

    CROW_ROUTE(app, "/users")
            .methods("POST"_method)
    ([&db, &conn] (const crow::request& req) {
        return BooShelf::Route::createUser(conn, db, req);
    });

    crow::logger::setLogLevel(crow::LogLevel::DEBUG);

    app.port(config["server"]["port"].i()).multithreaded().run();
}