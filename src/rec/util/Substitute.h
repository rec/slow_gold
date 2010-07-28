#ifndef __REC_UTIL_SUBSTITUTE__
#define __REC_UTIL_SUBSTITUTE__

#include "juce_amalgamated.h"

inline String substituteVariables(const StringPairArray& variables, const String& format) {
    String result;
    const char *begin = format.toCString();
    const char *end = begin + format.length() + 1;  // Including the \0!
    const char *consumed = begin;

    bool escaped = false;
    bool evaluating = false;
    int brackets = 0;  // Number of levels of brackets in evaluating - only 0 or 1.

    for (const char *i = begin; i != end ; ++i)
    {
        if (!escaped)
        {
            if (*i == '\\')
            {
                escaped = true;
                continue;
            }

            if (evaluating)
            {
                if (*i == '{')
                  brackets = 1;

                if (brackets ? (*i == '}') : (!isalnum(*i) && (*i != '_')))
                {
                    String name = String(consumed + brackets, i - consumed - brackets);
                    result += variables.getValue(name, "");
                    evaluating = false;
                    consumed = i + brackets;
                }
            }
            else if (*i == '$' || *i == '\0')
            {
                result += String(consumed, i - consumed);
                evaluating = true;
                consumed = i + 1;
            }
        }
    }
    return result;
}

#endif  // __REC_UTIL_SUBSTITUTE__
