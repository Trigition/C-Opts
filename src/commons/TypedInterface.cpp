#include <algorithm>
#include "C_Code.h"

bool TypedInterface::isInVector(std::string &type, std::vector<std::string> &vector) {
    bool check = std::find(vector.begin(), vector.end(), type) != vector.end();
    return check;
}

// TODO Make UTF-8 Compatible.
std::string TypedInterface::getTypeAlias(std::string &type) {
    std::transform(type.begin(),
                   type.end(),
                   type.begin(),
                   ::tolower);
    // Perform map lookup on specified type
    std::vector<std::string> intAliases = {"int", "integer"};
    std::vector<std::string> floatAliases = {"float", "decimal"};
    std::vector<std::string> stringAliases = {"str", "string", "text", "char*", "char *"};
    std::vector<std::string> fileAliases = {"file"};

    if (isInVector(type, intAliases)) return "int";
    if (isInVector(type, floatAliases)) return "float";
    if (isInVector(type, stringAliases)) return "char*";
    if (isInVector(type, fileAliases)) return "FILE*";

    // None found
    return "CUSTOM";
}

std::string TypedInterface::getTypeAlias(c_str &type) {
    std::string type_str = type;
    return getTypeAlias(type_str);
}
