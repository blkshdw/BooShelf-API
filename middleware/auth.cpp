//
// Created by tetofakun on 29.03.16.
//

#include "auth.h"

using namespace std;

ExampleMiddleware::ExampleMiddleware()
    {
        message = "foo";
    }

    void ExampleMiddleware::setMessage(std::string newMsg)
    {
        message = newMsg;
    }

    struct context
    {
    };

    void ExampleMiddleware::before_handle(crow::request& req, crow::response& res, context& ctx)
    {
        CROW_LOG_DEBUG << " - MESSAGE: " << message;
    }

    void ExampleMiddleware::after_handle(crow::request& req, crow::response& res, context& ctx)
    {
        // no-op
    }
