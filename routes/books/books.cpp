//
// Created by blkshdw on 27.03.16.
//

#include "books.h"
namespace R = RethinkDB;
crow::response BooShelf::Route::getBooks(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query &db, const crow::request &req) {
    auto authCTX = (Middleware::Auth::context*)req.middleware_context;
    auto orderBy = BooShelf::DEF_FILTERS::DEF_ORDER_BY;
    auto author_filter = BooShelf::DEF_FILTERS::DEF_AUTHOR_FILTER;
    auto genre_filter = BooShelf::DEF_FILTERS::DEF_GENRE_FILTER;
    auto title_filter = BooShelf::DEF_FILTERS::DEF_TITLE_FILTER;
    if (req.url_params.get("author") != nullptr) {
        author_filter = req.url_params.get("author");
    }
    if (req.url_params.get("genre") != nullptr) {
        genre_filter = req.url_params.get("genre");
    }
    if (req.url_params.get("title") != nullptr) {
        title_filter = req.url_params.get("title");
    }

    if (!authCTX->visitor->canGetBooks()) {
        throw Http::AccessDeniedException();
    }
    try {
        R::Cursor cur = db.table("books").order_by(R::desc("popularity")).filter(
                (R::row["author"].match(author_filter), R::) &&
                (R::expr(R::row["title"].not_()) || R::row["title"].match(title_filter)) &&
                (R::expr(R::row["title"].not_()) || R::row["genre"].match(genre_filter))).limit(1000).run(*conn);
        return crow::response(R::write_datum(cur.to_datum()));
    } catch(R::Error err) {
        throw Http::DataBaseException(err.message);
    }


};

crow::response BooShelf::Route::getBook(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query &db, const crow::request &req, std::string book) {
    return crow::response();
}

crow::response BooShelf::Route::createBook(std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db, const crow::request &req) {
    return crow::response();
}
crow::response BooShelf::Route::updateBook(std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db, const crow::request &req) {
    return crow::response();
}
