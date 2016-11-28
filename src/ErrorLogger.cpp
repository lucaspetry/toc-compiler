#include "ErrorLogger.h"
#include <stdlib.h>
#include <fstream>

ErrorLogger::ErrorLogger() {
    this->errorCount[ErrorLogger::LEXICAL] = 0;
    this->errorCount[ErrorLogger::SEMANTIC] = 0;
    this->errorCount[ErrorLogger::SYNTAX] = 0;
    this->errorCount[ErrorLogger::WARNING] = 0;
    this->error = false;
}

ErrorLogger::~ErrorLogger() {
}

void ErrorLogger::log(ErrorLogger::Type type, std::string message) {
    this->errorCount[type]++;
    std::string line = "[Line " + std::to_string(yylineno) + "]";
    std::string errorType = typeToString(type);

    if(!this->error || type != ErrorLogger::WARNING) {
        this->playSound();
        this->error = true;
    }

    if(type == ErrorLogger::WARNING)
        std::cout << line << " " << errorType << ": " << message << std::endl;
    else
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

void ErrorLogger::playSound() const {
    std::string command = "aplay -c 1 -q -t wav ";
    std::ifstream soundFile("data/sound/ErrorSound_FaustaoErrou.wav");

    if(soundFile.good()) {
        command += "data/sound/ErrorSound_FaustaoErrou.wav &";
        system(command.c_str());
    }
}

void yyerror(const char *s, ...) {
    std::string syntaxError = "syntax error";
    if(syntaxError.compare(s))
        return;

    ERROR_LOGGER->log(ErrorLogger::SYNTAX, "Unknown error.");
}
