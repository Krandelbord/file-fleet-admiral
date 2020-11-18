#ifndef COMPARE_DIRS_FIRST_H
#define COMPARE_DIRS_FIRST_H

#include "CompareFunction.h"

class CompareDirsFirst : public CompareFunction {
    public:
        virtual CompareResult compare(const FileListElement& first, const FileListElement& second) const;
        virtual ~CompareDirsFirst();

    bool bothAreDirs(const FileListElement &element, const FileListElement &listElement) const;
};
#endif /** COMPARE_DIRS_FIRST_H */
