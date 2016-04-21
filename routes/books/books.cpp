//
// Created by blkshdw on 27.03.16.
//

#include "books.h"
namespace R = RethinkDB;
crow::response BooShelf::Route::getBooks(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query &db, const crow::request &req) {
    auto authCTX = (Middleware::Auth::context*)req.middleware_context;

    if (!authCTX->visitor->canGetBooks()) {
        throw Http::AccessDeniedException();
    }

    // Forming query

    auto query = db.table("books");

    if (req.url_params.get("orderBy") != nullptr) {
        if (req.url_params.get("asc") != nullptr && req.url_params.get("asc") == "true") {
            query = query.order_by((req.url_params.get("orderBy")));
        } else {
            query = query.order_by(R::desc(BooShelf::DEF_FILTERS::DEF_ORDER_BY));
        }
    }

    if (req.url_params.get("author") != nullptr) {
        query = query.filter((R::row["author"].match(req.url_params.get("author"))));
    }
    if (req.url_params.get("genre") != nullptr) {
        query = query.filter((R::row["genre"].match(req.url_params.get("genre"))));
    }
    if (req.url_params.get("title") != nullptr) {
        query = query.filter((R::row["title"].match(req.url_params.get("title"))));
    }

    try {
        R::Cursor cur = query.limit(1000).run(*conn);
        return crow::response(R::write_datum(cur.to_datum()));
    } catch(R::Error err) {
        throw Http::DataBaseException(err.message);
    }
};

crow::response BooShelf::Route::getBook(std::shared_ptr<RethinkDB::Connection> conn, const RethinkDB::Query &db, const crow::request &req, std::string bookId) {
    auto authCTX = (Middleware::Auth::context*)req.middleware_context;

    if (!authCTX->visitor->canGetBook()) {
        throw Http::AccessDeniedException();
    }
    try {
        auto cur = db.table("books").get(bookId).run(*conn);
        return crow::response(R::write_datum(cur));
    } catch (R::Error err) {
        throw Http::DataBaseException(err.message);
    }
}

crow::response BooShelf::Route::createBook(std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db, const crow::request &req) {
    auto authCTX = (Middleware::Auth::context*)req.middleware_context;

    if (!authCTX->visitor->canAddBook()) {
        throw Http::AccessDeniedException();
    }
    rapidjson::Document book_d;
    rapidjson::StringStream book_ss(req.body.c_str());
    book_d.ParseStream(book_ss);
    if (book_d.HasParseError()) {
        throw BooShelf::Http::UnprocessableEntityException("Payload is not a correct JSON object" + string(rapidjson::GetParseError_En(book_d.GetParseError())));
    }

    try {
        BooShelf::Validator::validate (req.body, BOOK_SCHEMA);
    } catch (Http::HttpException err) {
        throw err;
    }
    rapidjson::Value created_by;
    created_by = rapidjson::StringRef(authCTX->visitor->getUserId().c_str());
    book_d.AddMember("createdBy", created_by, book_d.GetAllocator());
    rapidjson::Value rating;
    rating.SetInt(0);
    book_d.AddMember("rating", rating, book_d.GetAllocator());
    rapidjson::Value viewCount;
    viewCount.SetInt(0);
    book_d.AddMember("viewCount", viewCount, book_d.GetAllocator());
    try {
        auto cur = db.table("books").filter(R::row["title"] == book_d["title"].GetString() && R::row["author"] == book_d["author"].GetString()).run(*conn);
        for (R::Datum& book_exists : cur) {
            throw Http::UnprocessableEntityException("Book already exists");
        };
        rapidjson::StringBuffer strbuf;
        rapidjson::Writer<rapidjson::StringBuffer> writer(strbuf);
        book_d.Accept(writer);
        cout << strbuf.GetString();
        auto cur_i = db.table("books").insert(R::json(strbuf.GetString())).run(*conn);
        auto bookId = cur_i.to_datum().get_field("generated_keys")->get_nth(0)->extract_string();
        cout << bookId;
        auto cur_g = db.table("books").get(bookId).run(*conn);
        return crow::response(R::write_datum(cur_g));
    } catch (R::Error err) {
        throw Http::DataBaseException(err.message);
    }
}

crow::response BooShelf::Route::updateBook(std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db, const crow::request &req) {
    auto authCTX = (Middleware::Auth::context*)req.middleware_context;
    auto bookData = R::json(req.body.c_str());
    if(!authCTX->visitor->canEditBook(bookData));
    return crow::response();
}
