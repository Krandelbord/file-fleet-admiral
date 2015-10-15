#include "SortChain.h"
#include "config.h"

/**
 * Class that implements SortChain.
 * The only problem with that class is that it create COPY of itself every comparsion.
 *
 */
SortChain::SortChain(std::shared_ptr<CompareFunction> compareFunction) {
    this->comparatorList.push_back(compareFunction);
}

bool SortChain::operator()(const FileListElement& first, const FileListElement& second) const {
    for (std::shared_ptr<CompareFunction> oneOfCmpFunction : comparatorList) {
        const CompareResult &compareResult = oneOfCmpFunction->compare(first, second);
        if (compareResult == CompareResult::FIRST_IS_LESS) {
            return !normalOrder;
        } else if (compareResult == CompareResult::SECOND_IS_LESS) {
            return normalOrder;
        }
        //else nothing will move to another comparator in chain will check
    }
    return !normalOrder;
}

void SortChain::addSorting(std::shared_ptr<CompareFunction> compareFunctionToAdd) {
    this->comparatorList.push_back(compareFunctionToAdd);
}

SortChain::~SortChain() {
    gfm_debug("Destrcutor of sortChain\n");
    comparatorList.clear ();
}

void SortChain::sort(std::vector<FileListElement>& dataToSort) {
    std::sort(dataToSort.begin(), dataToSort.end(), *this);
}

void SortChain::reverseOrder() {
    this->normalOrder = false;
}
