#ifndef COMPARE_BY_NAME
#define COMPARE_BY_NAME

#include "CompareFunction.h"

class CompareByName : public CompareFunction {
    public:
        CompareByName();
        virtual CompareResult compare(const FileListElement& first, const FileListElement& second) const;
        virtual ~CompareByName();
};

#endif /** COMPARE_BY_NAME **/
