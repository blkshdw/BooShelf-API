#include "crow_all.h"
#include "routes/users/users.h"
#include "tools/auth.h"
#include "exceptions/httpExceptions.h"
#include <rethinkdb.h>
#include <fstream>
#include <string>
#include <streambuf>
#include <jwt.h>


namespace R = RethinkDB;
namespace json = crow::json;
using namespace std;

int main(){

    crow::SimpleApp app;

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

    jwt* key;
    jwt_new(&key);
    jwt_add_grants_json(key, config_str.c_str());
    

    CROW_ROUTE(app, "/users")
            ([&db, &conn]() {
                json::wvalue response;
                R::Cursor cursor = db.table("users").run(*conn);
                for (R::Datum& user : cursor) {
                    json::rvalue userJSON = json::load(R::write_datum(user).c_str());
                    response["users"][userJSON["id"].s()] = userJSON;
                }
                return response;
            });

    CROW_ROUTE(app, "/me")
            .methods("GET"_method)
    ([&db, &conn] (const crow::request& req) {
        return Route::me(conn, db, req);
    });

    app.port(config["server"]["port"].i()).multithreaded().run();
}