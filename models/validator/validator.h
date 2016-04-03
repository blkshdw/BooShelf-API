#include "../../exceptions/httpExceptions.h"
#include <rapidjson/stringbuffer.h>
#include <rapidjson/document.h>
#include <rapidjson/schema.h>
#include "rapidjson/error/en.h"
#include <string.h>
#ifndef BOOSHELF_SERVER_VALIDATOR_H
#define BOOSHELF_SERVER_VALIDATOR_H
using namespace rapidjson;
using namespace std;
namespace BooShelf {
    namespace Validator {
        inline void validate(string inputJSON, string schemaJSON) {
            Document sd;
            rapidjson::StringStream shema_s(schemaJSON.c_str());
            sd.ParseStream(shema_s);
            if (sd.HasParseError()) {
                throw BooShelf::Http::ServerErrorException("Provided schema is not valid: " + string(rapidjson::GetParseError_En(sd.GetParseError())));
            }
            SchemaDocument schema(sd);

            Document input_doc;
            rapidjson::StringStream input_s(inputJSON.c_str());
            input_doc.ParseStream(input_s);
            SchemaValidator validator(schema);
            if (!input_doc.Accept(validator)) {
                // Input JSON is invalid according to the schema
                // Output diagnostic information
                StringBuffer sb;
                validator.GetInvalidSchemaPointer().StringifyUriFragment(sb);
                string message;
                message += "Invalid schema: ";
                message += sb.GetString();
                message += ", ";
                message += "Invalid keyword: ";
                message += validator.GetInvalidSchemaKeyword();
                sb.Clear();
                message += ", ";
                validator.GetInvalidDocumentPointer().StringifyUriFragment(sb);
                message += "Invalid document: ";
                message += sb.GetString();
                throw BooShelf::Http::UnprocessableEntityException(message);
            }
        }
    }
}

#endif // BOOSHELF_SERVER_VALIDATOR_H