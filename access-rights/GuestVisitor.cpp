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

bool GuestVisitor::canEditOtherProfile(RethinkDB::Query& user) {
    return false;
}

bool GuestVisitor::canEditOtherFullProfile(RethinkDB::Query& user) {
    return false;
}

// Books

bool GuestVisitor::canAddBook() {
    return false;
}

bool GuestVisitor::canEditBook(RethinkDB::Query& book) {
    return false;
}

bool GuestVisitor::canGetBook() {
    return true;
}

bool GuestVisitor::canGetBooks() {
    return true;
}

// Trackings
bool GuestVisitor::canEditTracking(RethinkDB::Query& tracking) {
    return false;
}

bool GuestVisitor::canGetTracking() {
    return false;
}

bool GuestVisitor::canGetOwnTrackings() {
    return false;
}

bool GuestVisitor::canGetOtherTrackings() {
    return false;
}

// Review
bool GuestVisitor::canEditReview(RethinkDB::Query& review) {
    return false;
}

bool GuestVisitor::canAddReview() {
    return false;
}

bool GuestVisitor::canGetReview() {
    return true;
}

bool GuestVisitor::canGetReviews() {
    return true;
}
