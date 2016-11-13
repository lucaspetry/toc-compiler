#include "TocAnalyzer.h"

TocAnalyzer::TocAnalyzer() {
}

TocAnalyzer::~TocAnalyzer() {
}

void TocAnalyzer::analyzeVariable(std::string id){
    if(isupper(id.at(0)))
        ERROR_LOGGER->log(ErrorLogger::WARNING, "Variable " + id + " initiates with a uppercase."
            "TOC recommends that variable, function and object’s names initiate with a lowercase character.");
}

//void TocAnalyzer::analyzeAssign(int sp1, int sp2) {
//    if (sp1 == 0 || sp2 == 0)
//        ERROR_LOGGER->log(ErrorLogger::WARNING, "TOC recommends that you leave one space between the "
//            "operands of an assignment, declaration or expression.");
//
//}
//
//void TocAnalyzer::analyzeCommas(int sp){
//    if (sp == 0)
//        ERROR_LOGGER->log(ErrorLogger::WARNING, "TOC recommends that you leave one space after commas.");
//
//}

void TocAnalyzer::analyzeSpaces(int n_args, ...) {    
    va_list ap;
    va_start(ap, n_args);
        
    for(int i = 1; i <= n_args; i++) {
        switch(va_arg(ap, int)) {
            case 1:
                break;
            default:
                ERROR_LOGGER->log(ErrorLogger::WARNING,
                    "TOC recommends that you leave exactly one space in between operands and/or operators.");
                i = n_args;
                break;
        }
    }
    
    va_end(ap);
}