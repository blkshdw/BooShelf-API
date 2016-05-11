//
// Created by blkshdw on 27.03.16.
//
#include "../../models/validator/validator.h"
#include "../../models/user.h"
#include "../../middleware/auth.h"
#include "../../models/review.h"
#include "../../tools/auth.h"
#include "../../exceptions/httpExceptions.h"
#include "../../tools/token.h"
#include "../../crow_all.h"
#include <rethinkdb.h>

#ifndef BOOSHELF_SERVER_ROUTE_REVIEWS_H
#define BOOSHELF_SERVER_ROUTE_REVIEWS_H

namespace BooShelf {
    namespace Route {
        crow::response getReviews(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query& db, const crow::request &req);
        crow::response getReview(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query& db, const crow::request &req);
        crow::response createReview(std::shared_ptr<RethinkDB::Connection> &conn, const RethinkDB::Query& db, const crow::request &req);
        crow::response updateReview(std::shared_ptr<RethinkDB::Connection> &conn, const RethinkDB::Query& db, const crow::request &req);
    }
}
#endif //BOOSHELF_SERVER_ROUTE_REVIEWS_H
