//
// Created by tetofag on 02.04.16.
//

#ifndef BOOSHELF_SERVER_USER_MODEL_H
#define BOOSHELF_SERVER_USER_MODEL_H

#include <string>

static std::string const USER_SCHEMA =
R"({
  "$schema": "http://json-schema.org/draft-04/schema#",
  "id": "/",
  "type": "object",
  "properties": {
    "password": {
      "id": "password",
      "type": "string"
    },
    "fullName": {
      "id": "fullName",
      "type": "string"
    },
    "books": {
      "id": "books",
      "type": "array",
      "items": {
        "id": "0",
        "type": "object",
        "properties": {
          "id": {
            "id": "id",
            "type": "string"
          },
          "progress": {
            "id": "progress",
            "type": "integer",
            "minimum": 0,
            "maximum": 10
          },
          "startedReading": {
            "id": "startedReading",
            "type": "integer"
          },
          "finishedReading": {
            "id": "finishedReading",
            "type": "integer"
          },
          "rating": {
            "id": "rating",
            "type": "integer"
          }
        },
        "additionalProperties": false
      },
      "additionalItems": false
    }
  },
  "additionalProperties": false
})";
#endif //BOOSHELF_SERVER_USER_H
