//
// Created by blkshdw on 30.03.16.
//
#include "GuestVisitor.h"

namespace json = crow::json;
using namespace BooShelf;
namespace R = RethinkDB;

// Constructors

GuestVisitor::GuestVisitor() {
}

// Auth and own profile

bool GuestVisitor::canRegister(std::string& username, std::string& password, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query& db) {
    if (username.find_first_not_of(" \t\n\v\f\r") == std::string::npos) {
        throw Http::UnprocessableEntityException("Username is too short");
    }

    if (password.find_first_not_of(" \t\n\v\f\r") == std::string::npos) {
        throw Http::UnprocessableEntityException("Password is too short");
    }

    R::Cursor cursor = db.table("users").filter(R::row["username"] == username).run(*conn);
    for (R::Datum& userElem : cursor) {
        throw Http::AlreadyRegisteredException();
    }

    return true;
}

bool GuestVisitor::canLogin() {
    return true;
}

bool GuestVisitor::canEditOwnProfile() {
    return false;
}

bool GuestVisitor::canGetOwnProfile() {
    return false;
}

crow::json::wvalue GuestVisitor::getuserJSON() {
    return crow::json::wvalue();
}

// Other Profile

bool GuestVisitor::canGetOtherProfile(crow::json::wvalue &user) {
    return false;
}

bool GuestVisitor::canEditOtherProfile(crow::json::wvalue &user) {
    return false;
}

bool GuestVisitor::canEditOtherFullProfile(crow::json::wvalue &user) {
    return false;
}

// Books

bool GuestVisitor::canAddBook() {
    return false;
}

bool GuestVisitor::canEditBook(crow::json::wvalue &book) {
    return false;
}

bool GuestVisitor::canGetBook() {
    return true;
}

bool GuestVisitor::canGetBooks() {
    return false;
}

// Authors

bool GuestVisitor::canAddAuthor() {
    return false;
}

bool GuestVisitor::canGetAuthor(crow::json::wvalue &author) {
    return true;
}

bool GuestVisitor::canEditAuthor(crow::json::wvalue &author) {
    return false;
}

bool GuestVisitor::canGetAuthors() {
    return true;
}

