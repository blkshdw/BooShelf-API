//
// Created by blkshdw on 30.03.16.
//
#include "../crow_all.h"
#include <rethinkdb.h>

#ifndef BOOSHELF_SERVER_VISITOR_H
#define BOOSHELF_SERVER_VISITOR_H

namespace BooShelf {
    class Visitor {
    public:
        // Own Profile
        virtual bool canRegister(std::string& username, std::string& password, std::shared_ptr<RethinkDB::Connection>& conn, const RethinkDB::Query& db) = 0;
        virtual bool canLogin() = 0;
        virtual bool canEditOwnProfile() = 0;
        virtual bool canGetOwnProfile() = 0;

        // Other Profile
        virtual bool canGetOtherProfile(crow::json::wvalue& user) = 0;
        virtual bool canEditOtherProfile(crow::json::wvalue& user) = 0;
        virtual bool canEditOtherFullProfile(crow::json::wvalue& user) = 0;

        // User
        virtual crow::json::wvalue getuserJSON() = 0;

        // Books
        virtual bool canAddBook() = 0;
        virtual bool canEditBook(crow::json::wvalue &book) = 0;
        virtual bool canGetBook() = 0;
        virtual bool canGetBooks() = 0;

        // Authors
        virtual bool canEditAuthor(crow::json::wvalue &author) = 0;
        virtual bool canAddAuthor() = 0;
        virtual bool canGetAuthor(crow::json::wvalue &author) = 0;
        virtual bool canGetAuthors() = 0;

    };
}


#endif //BOOSHELF_SERVER_VISITOR_H
