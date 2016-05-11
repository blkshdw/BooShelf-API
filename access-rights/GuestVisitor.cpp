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

bool GuestVisitor::canEditOtherProfile(std::string userId, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db) {
    return false;
}

bool GuestVisitor::canEditOtherFullProfile(std::string userId, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db) {
    return false;
}

// Books

bool GuestVisitor::canAddBook() {
    return false;
}

bool GuestVisitor::canEditBook(std::string bookId, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db) {
    return false;
}

bool GuestVisitor::canGetBook() {
    return true;
}

bool GuestVisitor::canGetBooks() {
    return true;
}

// Trackings

bool GuestVisitor::canAddTracking() {
    return false;
}

bool GuestVisitor::canEditTracking(std::string trackingId, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db) {
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
bool GuestVisitor::canEditReview(std::string reviewId, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db) {
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
