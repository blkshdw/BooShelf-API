//
// Created by blkshdw on 27.03.16.
//

#include "books.h"
namespace R = RethinkDB;
crow::response BooShelf::Route::getBooks(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query &db, const crow::request &req) {
    auto authCTX = (Middleware::Auth::context*)req.middleware_context;
    string orderBy = "name";

    auto author = req.url_params.get("author");
    cout << author;
    cout << "vvvv";
    auto genre = req.url_params.get("genre");
    auto title = req.url_params.get("title");

    if (!authCTX->visitor->canGetBooks()) {
        throw Http::AccessDeniedException();
    }

    R::Cursor cur = db.table("books").order_by(R::desc("popularity")).filter((R::expr(author != nullptr) && R::expr(R::row["author"] == author))).limit(1000).run(*conn);
    return crow::response(R::write_datum(cur.to_datum()));
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
