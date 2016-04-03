//
// Created by blkshdw on 27.03.16.
//

#include "reviews.h"

crow::response BooShelf::Route::getReviews(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query &db, const crow::request &req) {
    return crow::response();
}
crow::response BooShelf::Route::getReview(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query &db, const crow::request &req) {
    return crow::response();
}
crow::response BooShelf::Route::createReview(std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db, const crow::request &req) {
    return crow::response();
}
crow::response BooShelf::Route::updateReview(std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db, const crow::request &req) {
    return crow::response();
}
