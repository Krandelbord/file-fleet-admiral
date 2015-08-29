#ifndef COMPARE_FUNCTION_H
#define COMPARE_FUNCTION_H

#include "CompareResult.h"
#include "FileListElement.h"

class CompareFunction {
    public:
        virtual CompareResult compare(const FileListElement& first, const FileListElement& second) const = 0;
        virtual ~CompareFunction() {};
};
#endif /** COMPARE_FUNCTION_H **/
