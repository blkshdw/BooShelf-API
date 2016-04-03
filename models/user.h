//
// Created by blkshdw on 02.04.16.
//
#include <string>

#ifndef BOOSHELF_SERVER_USER_MODEL_H
#define BOOSHELF_SERVER_USER_MODEL_H

static std::string const USER_SCHEMA =
R"({
  "$schema": "http://json-schema.org/draft-04/schema#",
  "id": "/",
  "type": "object",
  "properties": {
    "password": {
      "id": "password",
      "type": "string",
      "maxLength": 100
    },
    "fullName": {
      "id": "fullName",
      "type": "string",
      "maxLength": 100
    },
    "age": {
        "id": "age",
        "type": "number",
        "minimum": 0,
        "maximum": 100
    },
    "about": {
        "id": "about",
        "type": "string",
        "maxLength": "10000"
    }
  },
  "additionalProperties": false
})";
#endif //BOOSHELF_SERVER_USER_H
