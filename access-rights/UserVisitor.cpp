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

bool UserVisitor::canEditOtherProfile(rapidjson::Document& user) {
    return false;
}

bool UserVisitor::canEditOtherFullProfile(rapidjson::Document& user) {
    return false;
}

// Books

bool UserVisitor::canAddBook() {
    return true;
}

bool UserVisitor::canEditBook(rapidjson::Document& book) {
    return true;
}

bool UserVisitor::canGetBook() {
    return true;
}

bool UserVisitor::canGetBooks() {
    return true;
}

// Authors

bool UserVisitor::canAddAuthor() {
    return true;
}

bool UserVisitor::canGetAuthor() {
    return true;
}

bool UserVisitor::canEditAuthor(rapidjson::Document& author) {
    return true;
}

bool UserVisitor::canGetAuthors() {
    return true;
}
