//
// Created by tetofag on 02.04.16.
//

#include "headers.h"

BooShelf::Middleware::Headers::Headers() {

}

void BooShelf::Middleware::Headers::before_handle(crow::request &req, crow::response &res,
                                                  BooShelf::Middleware::Headers::context &ctx) {

}

void BooShelf::Middleware::Headers::after_handle(crow::request &req, crow::response &res,
                                                 BooShelf::Middleware::Headers::context &ctx) {
    res.add_header("Content-Type", "application/json");
}
