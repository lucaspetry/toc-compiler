#ifndef TOCANALYZER_H_
#define TOCANALYZER_H_
#include <ctype.h>
#include <string>

class TocAnalyzer;

extern TocAnalyzer TOC_ANALYZER;
extern void yyerror(const char* s, ...);

/**
 * Analisador TOC.
 */
class TocAnalyzer {

    public:
        TocAnalyzer();
        virtual ~TocAnalyzer();
        void analyzeVariable(std::string id);
        void analyzeAssign(int sp1, int sp2);
        void analyzeCommas(int sp);
};

#endif
