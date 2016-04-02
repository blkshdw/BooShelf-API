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

bool GuestVisitor::canRegister() {
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

rapidjson::Document GuestVisitor::getuserJSON() {
    return rapidjson::Document();
}

std::string GuestVisitor::getUserId() {
    return std::string();
}

std::string GuestVisitor::getUserString() {
    return std::string();
}

// Other Profile

bool GuestVisitor::canGetOtherProfile() {
    return false;
}

bool GuestVisitor::canEditOtherProfile(rapidjson::Document& user) {
    return false;
}

bool GuestVisitor::canEditOtherFullProfile(rapidjson::Document& user) {
    return false;
}

// Books

bool GuestVisitor::canAddBook() {
    return false;
}

bool GuestVisitor::canEditBook(rapidjson::Document& book) {
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

bool GuestVisitor::canGetAuthor() {
    return true;
}

bool GuestVisitor::canEditAuthor(rapidjson::Document& author) {
    return false;
}

bool GuestVisitor::canGetAuthors() {
    return true;
}

