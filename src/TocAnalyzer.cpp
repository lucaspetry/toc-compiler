#include "TocAnalyzer.h"

TocAnalyzer::TocAnalyzer() {
}

TocAnalyzer::~TocAnalyzer() {
}

void TocAnalyzer::analyzeVariable(std::string id){
  if(isupper(id.at(0)))
    yyerror("Warning: Variable %s initiate with a uppercase. TOC recommends that variable, function and object’s names initiate with a lowercase character.\n", id.c_str());
}

void TocAnalyzer::analyzeAssign(int sp1, int sp2) {
  if (sp1 == 0 || sp2 == 0)
    yyerror("Warning: TOC recommends that you leave one space between the operands of an assignment, declaration or expression.\n");

}

void TocAnalyzer::analyzeCommas(int sp){
  if (sp == 0)
    yyerror("Warning: TOC recommends that you leave one space between commas.\n");

}
