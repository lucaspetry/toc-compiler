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

void TocAnalyzer::analyzeAssign(int sp1, int sp2) {
    if (sp1 == 0 || sp2 == 0)
        ERROR_LOGGER->log(ErrorLogger::WARNING, "TOC recommends that you leave one space between the "
            "operands of an assignment, declaration or expression.");

}

void TocAnalyzer::analyzeCommas(int sp){
    if (sp == 0)
        ERROR_LOGGER->log(ErrorLogger::WARNING, "TOC recommends that you leave one space after commas.");

}
