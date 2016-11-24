#include "Data.h"

std::string Data::toString(Data::Type type) {
    switch(type) {
        case Data::UNKNOWN:
            return "unknown";
        case Data::BOO:
            return "boo";
        case Data::FLT:
            return "flt";
        case Data::INT:
            return "int";
        case Data::STR:
            return "str";
        case Data::VOID:
            return "void";
    }
}