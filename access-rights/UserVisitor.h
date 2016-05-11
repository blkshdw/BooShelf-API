//
// Created by blkshdw on 30.03.16.
//
#include "Visitor.h"
#include <rethinkdb.h>
#ifndef BOOSHELF_SERVER_USERVISITOR_H
#define BOOSHELF_SERVER_USERVISITOR_H

namespace BooShelf {
    class UserVisitor: public Visitor {
    private:
        std::shared_ptr<RethinkDB::Datum> _userDatum;
    public:
        UserVisitor();
        UserVisitor(std::shared_ptr<RethinkDB::Datum> userDatum);

        // Own Profile
        bool canRegister() override ;
        bool canLogin() override ;
        bool canEditOwnProfile() override ;
        bool canGetOwnProfile() override ;

        // Other Profile
        bool canGetOtherProfile() override ;
        bool canEditOtherProfile(std::string userId, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db) override ;
        bool canEditOtherFullProfile(std::string userId, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db) override;

        // User
        rapidjson::Document getuserJSON() override ;
        std::string getUserString() override ;
        std::string getUserId() override;

        // Books
        bool canAddBook() override;
        bool canEditBook(std::string bookId, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db) override ;
        bool canGetBook() override;
        bool canGetBooks() override;

        // Trackings
        bool canEditTracking(std::string trackingId, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db) override ;
        bool canGetTracking() override ;
        bool canGetOwnTrackings() override ;
        bool canGetOtherTrackings() override;

        // Reviews
        bool canEditReview(std::string reviewId, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query &db) override ;
        bool canAddReview() override;
        bool canGetReview() override;
        bool canGetReviews() override;
    };
}


#endif //BOOSHELF_SERVER_USERVISITOR_H
