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
        bool canRegister() override;
        bool canLogin() override;
        bool canEditOwnProfile() override;
        bool canGetOwnProfile() override;

        // Other Profile
        bool canGetOtherProfile() override;
        bool canEditOtherProfile(rapidjson::Document&  user) override;
        bool canEditOtherFullProfile(rapidjson::Document&  user) override;

        // User
        rapidjson::Document getuserJSON() override;
        std::string getUserString() override;
        std::string getUserId() override;

        // Books
        bool canAddBook() override;
        bool canEditBook(rapidjson::Document&  book) override;
        bool canGetBook() override;
        bool canGetBooks() override;

        // Authors
        bool canEditAuthor(rapidjson::Document&  author) override;
        bool canAddAuthor() override;
        bool canGetAuthor() override;
        bool canGetAuthors() override;
    };
}


#endif //BOOSHELF_SERVER_USERVISITOR_H
