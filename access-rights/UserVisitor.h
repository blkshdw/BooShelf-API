//
// Created by blkshdw on 30.03.16.
//
#include "Visitor.h"

#ifndef BOOSHELF_SERVER_USERVISITOR_H
#define BOOSHELF_SERVER_USERVISITOR_H

namespace BooShelf {
    class UserVisitor: public Visitor {
    private:
        crow::json::rvalue _userJSON;
    public:
        UserVisitor();
        UserVisitor(crow::json::rvalue userJSON);

        // Own Profile
        bool canRegister(std::string& username, std::string& password, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query& db) override;
        bool canLogin() override;
        bool canEditOwnProfile() override;
        bool canGetOwnProfile() override;

        // Other Profile
        bool canGetOtherProfile(crow::json::wvalue& user) override;
        bool canEditOtherProfile(crow::json::wvalue& user) override;
        bool canEditOtherFullProfile(crow::json::wvalue& user) override;

        // User
        crow::json::wvalue getuserJSON() override;

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


#endif //BOOSHELF_SERVER_USERVISITOR_H
