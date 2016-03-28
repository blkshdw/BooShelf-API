//
// Created by blkshdw on 28.03.16.
//

#include <string>
#include <jwt.h>

using namespace std;

#ifndef BOOSHELF_SERVER_TOKEN_H
#define BOOSHELF_SERVER_TOKEN_H

namespace BooShelf {
    namespace Token {
        std::string generate(std::string username, std::string password);
        jwt* decode(string);
        std::string getField(std::string field, std::string token);
        std::string getUsername(std::string token);
        std::string getPassword(std::string token);
    }
}

#endif //BOOSHELF_SERVER_TOKEN_H
