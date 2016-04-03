//
// Created by tetofag on 03.04.16.
//
//
#include "../../models/validator/validator.h"
#include "../../models/user.h"
#include "../../middleware/auth.h"
#include "../../tools/auth.h"
#include "../../exceptions/httpExceptions.h"
#include "../../tools/token.h"
#include "../../crow_all.h"
#include <rethinkdb.h>

#ifndef BOOSHELF_SERVER_TRACKINGS_H
#define BOOSHELF_SERVER_TRACKINGS_H
        crow::response getTrackings(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query& db, const crow::request &req);
        crow::response getTracking(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query& db, const crow::request &req);
        crow::response createTracking(std::shared_ptr<RethinkDB::Connection> &conn, const RethinkDB::Query& db, const crow::request &req);
        crow::response updateTracking(std::shared_ptr<RethinkDB::Connection> &conn, const RethinkDB::Query& db, const crow::request &req);

#endif //BOOSHELF_SERVER_TRACKINGS_H
