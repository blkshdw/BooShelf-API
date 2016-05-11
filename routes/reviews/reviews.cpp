//
// Created by blkshdw on 27.03.16.
//

#include "reviews.h"

namespace R = RethinkDB;

crow::response BooShelf::Route::getReviews(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query &db, const crow::request &req) {
    return crow::response();
}
crow::response BooShelf::Route::getReview(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query &db, const crow::request &req) {
    return crow::response();
}

// я не знаю, работает ли этот метод - я его не тестил
crow::response BooShelf::Route::createReview(std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db, const crow::request &req) {
    auto authCTX = (Middleware::Auth::context*)req.middleware_context;
    if (authCTX->visitor->canAddReview()) {
        try {
            BooShelf::Validator::validate(req.body, REVIEW_SCHEMA);
        } catch (Http::HttpException err) {
            throw err;
        }
        auto userId = authCTX->visitor->getUserId();
        try {
            auto cur = db.table("reviews").filter(R::row["bookId"] == string()).run(*conn);
            for (R::Datum& user_exists : cur) {
                throw Http::UnprocessableEntityException("Review for this book already exists");
            };
            db.table("users").get(userId).update(R::json(req.body)).run(*conn);
            R::Cursor cursor = db.table("users").get(userId).run(*conn);
            return crow::response(R::write_datum(cursor.to_datum()));
        } catch(R::Error err) {
            throw Http::DataBaseException(err.message);
        }
    }
    else {
        throw Http::AccessDeniedException();
    }
}

crow::response BooShelf::Route::updateReview(std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db, const crow::request &req) {
    return crow::response();
}
