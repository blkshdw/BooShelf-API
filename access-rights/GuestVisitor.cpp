//
// Created by blkshdw on 30.03.16.
//
#include "GuestVisitor.h"

namespace json = crow::json;
using namespace BooShelf;

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

