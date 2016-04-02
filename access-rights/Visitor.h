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
        virtual bool canEditOtherProfile(rapidjson::Document& user) = 0;
        virtual bool canEditOtherFullProfile(rapidjson::Document& user) = 0;

        // User
        virtual rapidjson::Document getuserJSON() = 0;
        virtual std::string getUserString() = 0;
        virtual std::string getUserId() = 0;

        // Books
        virtual bool canAddBook() = 0;
        virtual bool canEditBook(rapidjson::Document& book) = 0;
        virtual bool canGetBook() = 0;
        virtual bool canGetBooks() = 0;

        // Authors
        virtual bool canEditAuthor(rapidjson::Document& author) = 0;
        virtual bool canAddAuthor() = 0;
        virtual bool canGetAuthor() = 0;
        virtual bool canGetAuthors() = 0;

    };
}


#endif //BOOSHELF_SERVER_VISITOR_H
