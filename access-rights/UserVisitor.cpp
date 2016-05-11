//
// Created by blkshdw on 30.03.16.
//
#include <iostream>
#include "UserVisitor.h"
#include "../exceptions/httpExceptions.h"

using namespace BooShelf;

// Constructors

UserVisitor::UserVisitor() {

}

UserVisitor::UserVisitor(std::shared_ptr<RethinkDB::Datum> userDatum) {
    _userDatum = userDatum;
}

// Auth and own profile

bool UserVisitor::canRegister() {
    return false;
}

bool UserVisitor::canLogin() {
    return false;
}


bool UserVisitor::canEditOwnProfile() {
    return true;
}

bool UserVisitor::canGetOwnProfile() {
    return true;
}

rapidjson::Document UserVisitor::getuserJSON() {
    rapidjson::Document userJSON;
    rapidjson::StringStream userJSON_s(this->getUserString().c_str());
    userJSON.ParseStream(userJSON_s);
    return userJSON;
}

std::string UserVisitor::getUserId() {
    return _userDatum->extract_field("id").extract_string();
}

std::string UserVisitor::getUserString() {
    return RethinkDB::write_datum(*_userDatum);
}

// Other Profile

bool UserVisitor::canGetOtherProfile() {
    return true;
}

bool UserVisitor::canEditOtherProfile(std::string userId, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db) {
    return false;
}

bool UserVisitor::canEditOtherFullProfile(std::string userId, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db) {
    return false;
}

// Books

bool UserVisitor::canAddBook() {
    return true;
}

bool UserVisitor::canEditBook(std::string bookId, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db) {
    try {
        RethinkDB::Cursor cursor = db.table("books").get(bookId).run(*conn);
        auto authorId = cursor.to_datum().get_field("createdBy");
        if (authorId == getUserId()) {
            return true;
        }
    } catch (RethinkDB::Error err) {
        throw Http::DataBaseException(err.message);
    }
    return false;
}

bool UserVisitor::canGetBook() {
    return true;
}

bool UserVisitor::canGetBooks() {
    return true;
}

//Trackings
bool UserVisitor::canEditTracking(std::string trackingId, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db) {
    try {
        RethinkDB::Cursor cursor = db.table("trackings").get(trackingId).run(*conn);
        auto authorId = cursor.to_datum().get_field("createdBy");
        if (authorId == getUserId()) {
            return true;
        }
    } catch (RethinkDB::Error err) {
        throw Http::DataBaseException(err.message);
    }
    return false;
}

bool UserVisitor::canGetTracking() {
    return true;
}

bool UserVisitor::canGetOwnTrackings() {
    return true;
}

bool UserVisitor::canGetOtherTrackings() {
    return true;
}

bool UserVisitor::canEditReview(std::string reviewId, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db) {
    try {
        RethinkDB::Cursor cursor = db.table("reviews").get(reviewId).run(*conn);
        auto authorId = cursor.to_datum().get_field("createdBy");
        if (authorId == getUserId()) {
            return true;
        }
    } catch (RethinkDB::Error err) {
        throw Http::DataBaseException(err.message);
    }
    return false;
}

bool UserVisitor::canAddReview() {
    return true;
}

bool UserVisitor::canGetReview() {
    return true;
}

bool UserVisitor::canGetReviews() {
    return true;
}
