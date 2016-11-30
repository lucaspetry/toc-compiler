#include "ErrorLogger.h"
#include <stdlib.h>
#include <fstream>

ErrorLogger::ErrorLogger() {
    this->errorCount[ErrorLogger::LEXICAL] = 0; //peso = 2
    this->errorCount[ErrorLogger::SEMANTIC] = 0;//peso = 8
    this->errorCount[ErrorLogger::SYNTAX] = 0;//peso = 5
    this->errorCount[ErrorLogger::WARNING] = 0; //peso = 1
    this->error = false;
}

ErrorLogger::~ErrorLogger() {
}

void ErrorLogger::log(ErrorLogger::Type type, std::string message) {
    this->errorCount[type]++;
    std::string line = "[Line " + std::to_string(yylineno) + "]";
    std::string errorType = typeToString(type);

    // Se erros são detectados, executa som de erro
    if(!this->error && type != ErrorLogger::WARNING) {
        this->playErrorSound();
        this->error = true;
    }

    if(type == ErrorLogger::WARNING)
        std::cout << line << " " << errorType << ": " << message << std::endl;
    else
        std::cerr << line << " " << errorType << ": " << message << std::endl;
}

bool ErrorLogger::hasErrors() const {
    return this->error;
}
float ErrorLogger::getScore() const {
    float x = 0;
    float result = 0;
    if(this->error){
      x = (float) ((errorCount[ErrorLogger::LEXICAL]*2 + errorCount[ErrorLogger::SEMANTIC]*8 +errorCount[SYNTAX]*5)/15)/yylineno;
      if (x> 1)
        x = 1;
      result = 6-x*6;
    } else{
      x = (float) errorCount[ErrorLogger::WARNING]/yylineno;
      if (x>1)
       x = 1;
      result = 10-x*4;
    }
    return result;
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

void ErrorLogger::playErrorSound() const {
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
