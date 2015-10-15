#ifndef SORT_CHAIN
#define SORT_CHAIN

#include "CompareFunction.h"
#include "FileListElement.h"

class SortChain {
    public:
        SortChain(std::shared_ptr<CompareFunction> compareFunction);
        void add(std::shared_ptr<CompareFunction> compareFunctionToAdd);

        bool operator()(const FileListElement& first, const FileListElement& second) const;
        ~SortChain();

    void sort(std::vector<FileListElement>& vector);

private:
        std::vector<std::shared_ptr<CompareFunction>> comparatorList;

};
#endif /** SORT_CHAIN **/
