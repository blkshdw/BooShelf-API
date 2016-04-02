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
        bool canRegister() override;
        bool canLogin() override;
        bool canEditOwnProfile() override;
        bool canGetOwnProfile() override;
        rapidjson::Document getuserJSON() override;
        std::string getUserString() override;
        std::string getUserId() override;

        // Other Profile
        bool canGetOtherProfile() override;
        bool canEditOtherProfile(rapidjson::Document& user) override;
        bool canEditOtherFullProfile(rapidjson::Document& user) override;

        // Books
        bool canAddBook() override;
        bool canEditBook(rapidjson::Document& book) override;
        bool canGetBook() override;
        bool canGetBooks() override;

        // Authors
        bool canEditAuthor(rapidjson::Document& author) override;
        bool canAddAuthor() override;
        bool canGetAuthor() override;
        bool canGetAuthors() override;
    };
}


#endif //BOOSHELF_SERVER_GUESTVISITOR_H
