//
// Created by tetofakun on 29.03.16.
//

#include <string>
#include "../crow_all.h"

#ifndef BOOSHELF_SERVER_MIDDLEWARE_AUTH_H
#define BOOSHELF_SERVER_MIDDLEWARE_AUTH_H
struct ExampleMiddleware {
    ExampleMiddleware();
    std::string message;
    void setMessage(std::string newMsg);
    struct context {

    };
    void before_handle(crow::request& req, crow::response& res, context& ctx);
    void after_handle(crow::request& req, crow::response& res, context& ctx);
};
#endif //BOOSHELF_SERVER_MIDDLEWARE_AUTH_H
