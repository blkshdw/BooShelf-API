//
// Created by blkshdw on 27.03.16.
//
#include <rethinkdb.h>
#include "../crow_all.h"

#ifndef BOOSHELF_SERVER_AUTH_H
#define BOOSHELF_SERVER_AUTH_H

crow::json::wvalue checkAuth(std::unique_ptr<RethinkDB::Connection>&, const RethinkDB::Query&, const crow::request&);

#endif //BOOSHELF_SERVER_AUTH_H
