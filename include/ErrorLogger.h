#ifndef ERRORLOGGER_H_
#define ERRORLOGGER_H_

#include <iostream>
#include <string>

/**
  Class ErrorLogger
**/

class ErrorLogger;

extern ErrorLogger* ERROR_LOGGER;
extern int yylineno;
void yyerror(const char* s, ...);

class ErrorLogger {

    public:
        enum Type {
            LEXICAL = 0,
            SEMANTIC = 1,
            SYNTAX = 2,
            WARNING = 3
        };

        ErrorLogger();
        virtual ~ErrorLogger();
        void log(ErrorLogger::Type type, std::string message = "Unknown error.");

    private:
        std::string typeToString(ErrorLogger::Type type) const;
        int errorCount[4];

};

#endif
