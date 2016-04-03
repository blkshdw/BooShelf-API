//
// Created by tetofag on 03.04.16.
//
#include <string>
#ifndef BOOSHELF_SERVER_TRACKING_MODEL_H
#define BOOSHELF_SERVER_TRACKING_MODEL_H

static std::string const TRACKING_SCHEMA =
        R"({
  "$schema": "http://json-schema.org/draft-04/schema#",
  "id": "/",
  "type": "object",
  "properties": {
    "status": {
      "id": "status",
      "type": "number",
      "minimum": 1,
      "maximum": 3
    },
    "progress": {
      "id": "progress",
      "type": "number",
      "minimum": 0,
      "maximum": 100
    },
    "startedReading": {
        "id": "startedReading",
        "type": "string",
    },
    "finishedReading": {
        "id": "finishedReading",
        "type": "string",
    }
  },
  "additionalProperties": false
})";
#endif //BOOSHELF_SERVER_TRACKING_MODEL_H
