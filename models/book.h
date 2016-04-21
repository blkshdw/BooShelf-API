//
// Created by tetofag on 02.04.16.
//
#include <string>
#ifndef BOOSHELF_SERVER_BOOK_MODEL_H
#define BOOSHELF_SERVER_BOOK_MODEL_H
static std::string const BOOK_SCHEMA =
        R"({
  "$schema": "http://json-schema.org/draft-04/schema#",
  "id": "/",
  "type": "object",
  "properties": {
    "author": {
      "id": "author",
      "type": "string",
      "minLength": 1,
      "maxLength": 100
    },
    "title": {
      "id": "title",
      "type": "string",
      "minLength": 1,
      "maxLength": 100
    },
    "description": {
      "id": "description",
      "type": "string",
      "minLength": 10,
      "maxLength": 100000
    },
    "genre": {
        "id": "finishedReading",
        "type": "string",
        "format": "date-time"
    },
    "writtenOn": {
        "id": "writtenOn",
        "type": "string",
        "format": "date-time"
    }
  },
  "additionalProperties": false
})";
#endif //BOOSHELF_SERVER_BOOK_MODEL_H
