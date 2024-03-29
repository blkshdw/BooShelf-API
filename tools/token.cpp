//
// Created by blkshdw on 28.03.16.
//

#include <iostream>
#include "token.h"

std::string BooShelf::Token::generate(std::string username, std::string password) {
    jwt* jwt_data;
    jwt_new(&jwt_data);
    jwt_add_grant(jwt_data, "username", username.c_str());
    jwt_add_grant(jwt_data, "password", password.c_str());
    char *out;
    jwt_set_alg(jwt_data, jwt_alg::JWT_ALG_HS256, (unsigned char*)BooShelf::Token::secret_key, BooShelf::Token::key_length);
    jwt_encode_str(jwt_data);
    out = jwt_encode_str(jwt_data);
    cout << out;
    return out;
}

jwt* BooShelf::Token::decode(std::string token) {
    jwt* jwt_data;
    jwt_decode(&jwt_data, token.c_str(), (unsigned char*)BooShelf::Token::secret_key, BooShelf::Token::key_length);
    return jwt_data;
}

string BooShelf::Token::getField(std::string field, std::string token) {
    jwt* jwt_data = decode(token);
    return jwt_get_grant(jwt_data, token.c_str());
}

string BooShelf::Token::getUsername(std::string token) {
    return getField("username", token);
}

string BooShelf::Token::getPassword(std::string token) {
    return getField("password", token);
}
