#ifndef ERRORLOGGER_H_
#define ERRORLOGGER_H_

#include <iostream>
#include <string>

class ErrorLogger;

extern ErrorLogger* ERROR_LOGGER;
extern int yylineno;
void yyerror(const char* s, ...);

/**
 * Logger de erros
 */
class ErrorLogger {

    public:
        /**
         * Tipos de erros
         */
        enum Type {
            LEXICAL = 0,
            SEMANTIC = 1,
            SYNTAX = 2,
            WARNING = 3
        };

        /**
         * Construir um logger de erros
         */
        ErrorLogger();

        /**
         * Destruir o logger de erros
         */
        virtual ~ErrorLogger();

        /**
         * Registrar um erro
         * @param type tipo do erro
         * @param message mensagem de erro
         */
        void log(ErrorLogger::Type type, std::string message = "Unknown error.");

        /**
         * Verificar se o programa contém erros
         * @return true se erros foram capturados
         */
        bool hasErrors() const;

        /**
         * Calcula a pontuação do programa
         * @return pontuacao
         */
        float getScore() const;

    private:
        /**
         * Converter o tipo do erro para texto
         * @param type tipo de erro
         * @return texto correspondente ao tipo
         */
        std::string typeToString(ErrorLogger::Type type) const;

        /**
         * Executar som de erro
         */
        void playErrorSound() const;

        int errorCount[4];
        bool error;

};

#endif
