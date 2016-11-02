#ifndef TOCANALYZER_H_
#define TOCANALYZER_H_

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

};

#endif
