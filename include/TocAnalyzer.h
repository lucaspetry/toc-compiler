#ifndef TOCANALYZER_H_
#define TOCANALYZER_H_

#include "ErrorLogger.h"
#include <ctype.h>
#include <string>

extern ErrorLogger* ERROR_LOGGER;

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
