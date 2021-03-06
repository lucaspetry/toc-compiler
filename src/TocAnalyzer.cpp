#include "TocAnalyzer.h"

TocAnalyzer::TocAnalyzer() {
}

TocAnalyzer::~TocAnalyzer() {
}

void TocAnalyzer::analyzeProgram() {
    // TODO
}

void TocAnalyzer::analyzeComment(Comment* comment){
    std::string value = comment->getValue();
    // Encontra a primeira letra do comentário
    for(int i = 0; i < value.size(); i++) {
        if(isalpha(value.at(i))) { // Verifica se é letra do alfabeto

            if(!isupper(value.at(i))) // Se não for maiúscula, gera erro
                ERROR_LOGGER->log(ErrorLogger::WARNING, "TOC recommends that comments initiate with an uppercase character.");

            break;
        }
    }
}

void TocAnalyzer::analyzeVariable(std::string id){
    if(isupper(id.at(0)))
        ERROR_LOGGER->log(ErrorLogger::WARNING, "Variable " + id + " initiates with an uppercase character. "
            "TOC recommends that variable's name initiates with a lowercase character.");
}

void TocAnalyzer::analyzeObject(std::string id){
  if(islower(id.at(0)))
        ERROR_LOGGER->log(ErrorLogger::WARNING, "Object " + id + " initiates with a lowercase character. "
            "TOC recommends that class' name initiates with an uppercase character.");
}
void TocAnalyzer::analyzeSpaces(int n_args, ...) {
    va_list ap;
    va_start(ap, n_args);

    for(int i = 1; i <= n_args; i++) {
        switch(va_arg(ap, int)) {
            case 1:
                break;
            default:
                ERROR_LOGGER->log(ErrorLogger::WARNING,
                    "TOC recommends that you leave exactly one space in between operands and/or operators, and after commas.");
                i = n_args;
                break;
        }
    }

    va_end(ap);
}
