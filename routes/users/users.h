//
// Created by blkshdw on 27.03.16.
//
#include "../../crow_all.h"
#include <rethinkdb.h>

#ifndef BOOSHELF_SERVER_USERS_H
#define BOOSHELF_SERVER_USERS_H

namespace BooShelf {
    namespace Route {
        crow::response me(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query &db, const crow::request &req);
        crow::response createUser(std::shared_ptr<RethinkDB::Connection> &conn, const RethinkDB::Query &db, const crow::request &req);
    }
}

#endif //BOOSHELF_SERVER_USERS_H
