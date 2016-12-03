#ifndef TOCANALYZER_H_
#define TOCANALYZER_H_

#include "ErrorLogger.h"
#include "Comment.h"
#include <ctype.h>
#include <stdarg.h>
#include <string>

extern ErrorLogger* ERROR_LOGGER;

/**
 * Analisador TOC
 */
class TocAnalyzer {

    public:
        /**
         * Construir o analisador TOC
         */
        TocAnalyzer();

        /**
         * Destruir o analisador TOC
         */
        virtual ~TocAnalyzer();

        /**
         * Analisar o programa (última função executada na análise sintática)
         */
        void analyzeProgram();

        /**
         * Analisar um comentário
         * @param comment comentário
         */
        void analyzeComment(Comment* comment);

        /**
         * Analisar uma variável
         * @param id identificador da variável
         */
        void analyzeVariable(std::string id);
        /**
         * Analisar um objeto
         * @param id identificador da variável
         */
        void analyzeObject(std::string id);

        /**
         * Analisar espaços em branco
         * @param n_args número de espaços em branco
         * @param ... os parâmetros com espaços a serem analisados
         */
        void analyzeSpaces(int n_args, ...);

};

#endif
