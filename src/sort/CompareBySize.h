#ifndef COMPARE_BY_SIZE_H
#define COMPARE_BY_SIZE_H

#include "CompareFunction.h"

class CompareBySize : public CompareFunction {
public:
    CompareBySize();
    virtual CompareResult compare(const FileListElement& first, const FileListElement& second) const;
    virtual ~CompareBySize() {};
};


#endif //GTKMM_FILE_MANAGER_COMPAREBYSIZE_H
