//
// Created by tetofag on 02.04.16.
//
#include <string>

#ifndef BOOSHELF_SERVER_REVIEW_MODEL_H
#define BOOSHELF_SERVER_REVIEW_MODEL_H
static std::string const REVIEW_SCHEMA =
        R"({
  "$schema": "http://json-schema.org/draft-04/schema#",
  "id": "/",
  "type": "object",
  "properties": {
    "authorName": {
      "id": "author",
      "type": "string",
      "maxLength": 30
    },
    "bookId": {
      "id": "bookId",
      "type": "string"
    },
    "title": {
      "id": "title",
      "type": "string",
      "minLength": 5,
      "maxLength": 6
    },
    "description": {
      "id": "description",
      "type": "string",
      "minLength": 10,
      "maxLength": 100000
    "rating": {
        "id": "rating",
        "type": "number",
        "minimum": 0,
        "maximum": 10
    }
  "additionalProperties": false
})";
#endif //BOOSHELF_SERVER_REVIEW_MODEL_H
