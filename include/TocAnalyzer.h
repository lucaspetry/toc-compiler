#ifndef TOCANALYZER_H_
#define TOCANALYZER_H_

#include "ErrorLogger.h"
#include <ctype.h>
#include <stdarg.h>
#include <string>

/**
  Class TocAnalyzer
**/

extern ErrorLogger* ERROR_LOGGER;

class TocAnalyzer {

    public:
        TocAnalyzer();
        virtual ~TocAnalyzer();
        void analyzeVariable(std::string id);
        void analyzeSpaces(int n_args, ...);

};

#endif
