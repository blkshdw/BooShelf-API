//
// Created by blkshdw on 30.03.16.
//
#include "UserVisitor.h"

namespace json = crow::json;
using namespace BooShelf;

// Constructors

UserVisitor::UserVisitor() {
}

UserVisitor::UserVisitor(crow::json::rvalue userJSON) {
    _userJSON = userJSON;
}

UserVisitor::~UserVisitor() {
    delete &_userJSON;
}

// Auth and own profile

bool UserVisitor::canRegister(std::string& username, std::string& password, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query& db) {
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

crow::json::wvalue UserVisitor::getuserJSON() {
    return _userJSON;
}

// Other Profile

bool UserVisitor::canGetOtherProfile(crow::json::wvalue &user) {
    return true;
}

bool UserVisitor::canEditOtherProfile(crow::json::wvalue &user) {
    return false;
}

bool UserVisitor::canEditOtherFullProfile(crow::json::wvalue &user) {
    return false;
}

// Books

bool UserVisitor::canAddBook() {
    return true;
}

bool UserVisitor::canEditBook(crow::json::wvalue &book) {
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

bool UserVisitor::canGetAuthor(crow::json::wvalue &author) {
    return true;
}

bool UserVisitor::canEditAuthor(crow::json::wvalue &author) {
    return true;
}

bool UserVisitor::canGetAuthors() {
    return true;
}


