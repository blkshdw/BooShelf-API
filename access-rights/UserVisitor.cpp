//
// Created by blkshdw on 30.03.16.
//
#include <iostream>
#include "UserVisitor.h"

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

bool UserVisitor::canEditOtherProfile(RethinkDB::Query& user) {
    return false;
}

bool UserVisitor::canEditOtherFullProfile(RethinkDB::Query& user) {
    return false;
}

// Books

bool UserVisitor::canAddBook() {
    return true;
}

bool UserVisitor::canEditBook(RethinkDB::Query& book) {

    }
    return true;
}

bool UserVisitor::canGetBook() {
    return true;
}

bool UserVisitor::canGetBooks() {
    return true;
}

//Trackings
bool UserVisitor::canEditTracking(RethinkDB::Query &tracking) {
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

bool UserVisitor::canEditReview(RethinkDB::Query &review) {
    return true;
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
