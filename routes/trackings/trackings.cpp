//
// Created by tetofag on 03.04.16.
//

#include "trackings.h"

crow::response getTrackings(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query &db,
                            const crow::request &req) {
    return crow::response();
}

crow::response getTracking(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query &db,
                           const crow::request &req) {
    return crow::response();
}

crow::response createTracking(std::shared_ptr<RethinkDB::Connection> &conn, const RethinkDB::Query &db,
                              const crow::request &req) {
    return crow::response();
}

crow::response updateTracking(std::shared_ptr<RethinkDB::Connection> &conn, const RethinkDB::Query &db,
                              const crow::request &req) {
    return crow::response();
}
