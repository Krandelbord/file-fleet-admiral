#ifndef SORT_CHAIN
#define SORT_CHAIN

#include "CompareFunction.h"
#include "FileListElement.h"

class SortChain {
    public:
        SortChain(CompareFunction* compareFunction);
        void add(CompareFunction* compreFunctionToAdd);

        bool operator()(const FileListElement& first, const FileListElement& second) const;
        ~SortChain();
    private:
        std::vector<CompareFunction*> comparatorList;
       
};
#endif /** SORT_CHAIN **/
