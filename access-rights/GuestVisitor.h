//
// Created by blkshdw on 30.03.16.
//
#include "Visitor.h"

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
        crow::json::wvalue getuserJSON() override;

        // Other Profile
        bool canGetOtherProfile(crow::json::wvalue& user) override;
        bool canEditOtherProfile(crow::json::wvalue& user) override;
        bool canEditOtherFullProfile(crow::json::wvalue& user) override;

        // Books
        bool canAddBook() override;
        bool canEditBook(crow::json::wvalue& book) override;
        bool canGetBook() override;
        bool canGetBooks() override;

        // Authors
        bool canEditAuthor(crow::json::wvalue& author) override;
        bool canAddAuthor() override;
        bool canGetAuthor(crow::json::wvalue& author) override;
        bool canGetAuthors() override;
    };
}


#endif //BOOSHELF_SERVER_GUESTVISITOR_H
