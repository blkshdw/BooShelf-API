//
// Created by blkshdw on 30.03.16.
//
#include "Visitor.h"
#include "../exceptions/httpExceptions.h"

#ifndef BOOSHELF_SERVER_GUESTVISITOR_H
#define BOOSHELF_SERVER_GUESTVISITOR_H

namespace BooShelf {
    class GuestVisitor: public Visitor {
    public:
        GuestVisitor();

        // Own Profile
        bool canRegister() override ;
        bool canLogin() override ;
        bool canEditOwnProfile() override ;
        bool canGetOwnProfile() override ;

        // Other Profile
        bool canGetOtherProfile() override ;
        bool canEditOtherProfile(RethinkDB::Query& user) override ;
        bool canEditOtherFullProfile(RethinkDB::Query& user) override;

        // User
        rapidjson::Document getuserJSON() override ;
        std::string getUserString() override ;
        std::string getUserId() override;

        // Books
        bool canAddBook() override;
        bool canEditBook(RethinkDB::Query& book) override ;
        bool canGetBook() override;
        bool canGetBooks() override;

        // Trackings
        bool canEditTracking(RethinkDB::Query& tracking) override;
        bool canGetTracking() override;
        bool canGetOwnTrackings() override;
        bool canGetOtherTrackings() override;

        // Reviews
        bool canEditReview(RethinkDB::Query& review) override;
        bool canAddReview() override;
        bool canGetReview() override;
        bool canGetReviews() override;
    };
}


#endif //BOOSHELF_SERVER_GUESTVISITOR_H
