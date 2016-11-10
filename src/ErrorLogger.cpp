#include "ErrorLogger.h"

ErrorLogger::ErrorLogger() {
    this->errorCount[ErrorLogger::LEXICAL] = 0;
    this->errorCount[ErrorLogger::SEMANTIC] = 0;
    this->errorCount[ErrorLogger::SYNTAX] = 0;
    this->errorCount[ErrorLogger::WARNING] = 0;
}

ErrorLogger::~ErrorLogger() {
}

void ErrorLogger::log(ErrorLogger::Type type, std::string message) {
    this->errorCount[type]++;
    std::string line = "[Line " + std::to_string(yylineno) + "]";
    std::string errorType = typeToString(type);
    
    std::cerr << line << " " << errorType << ": " << message << std::endl;
}

std::string ErrorLogger::typeToString(ErrorLogger::Type type) const {
    switch(type) {
        case ErrorLogger::LEXICAL:
            return "Lexical error";
        case ErrorLogger::SEMANTIC:
            return "Semantic error";
        case ErrorLogger::SYNTAX:
            return "Syntax error";
        case ErrorLogger::WARNING:
            return "Warning";
    }
}

void yyerror(const char *s, ...) {
    std::string syntaxError = "syntax error";
    if(syntaxError.compare(s))
        return;
        
    ERROR_LOGGER->log(ErrorLogger::SYNTAX, "Unknown error.");
}