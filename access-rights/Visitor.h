//
// Created by blkshdw on 30.03.16.
//
#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>
#include <rethinkdb.h>

#ifndef BOOSHELF_SERVER_VISITOR_H
#define BOOSHELF_SERVER_VISITOR_H

namespace BooShelf {
    class Visitor {
    public:
        // Own Profile
        virtual bool canRegister() = 0;
        virtual bool canLogin() = 0;
        virtual bool canEditOwnProfile() = 0;
        virtual bool canGetOwnProfile() = 0;

        // Other Profile
        virtual bool canGetOtherProfile() = 0;
        virtual bool canEditOtherProfile(std::string userId, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db) = 0;
        virtual bool canEditOtherFullProfile(std::string userId, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db) = 0;

        // User
        virtual rapidjson::Document getuserJSON() = 0;
        virtual std::string getUserString() = 0;
        virtual std::string getUserId() = 0;

        // Books
        virtual bool canAddBook() = 0;
        virtual bool canEditBook(std::string bookId, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db) = 0;
        virtual bool canGetBook() = 0;
        virtual bool canGetBooks() = 0;

        // Trackings
        virtual bool canEditTracking(std::string trackingId, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db) = 0;
        virtual bool canGetTracking() = 0;
        virtual bool canAddTracking() = 0;
        virtual bool canGetOwnTrackings() = 0;
        virtual bool canGetOtherTrackings() = 0;

        // Reviews
        virtual bool canEditReview(std::string reviewId, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db) = 0;
        virtual bool canAddReview() = 0;
        virtual bool canGetReview() = 0;
        virtual bool canGetReviews() = 0;

    };
}


#endif //BOOSHELF_SERVER_VISITOR_H
