#include "SortChain.h"
#include "config.h"


SortChain::SortChain(std::shared_ptr<CompareFunction> compareFunction) {
    this->comparatorList.push_back(compareFunction);
}

bool SortChain::operator()(const FileListElement& first, const FileListElement& second) const {
    for (std::shared_ptr<CompareFunction> oneOfCmpFunction : comparatorList) {
        gfm_debug("Sorotwanie %s i %s \n", first.toString().c_str(), second.toString().c_str());
        const CompareResult &compareResult = oneOfCmpFunction->compare(first, second);
        if (compareResult == CompareResult::FIRST_IS_LESS) {
            return false;
        } else if (compareResult == CompareResult::SECOND_IS_LESS) {
            return true;
        }
        //else nothing will move to another comparator in chain will check
    }
    gfm_debug("Compare result undefined for %s and %s\n", first.toString().c_str(), second.toString().c_str());
    return false;
}

void SortChain::add(std::shared_ptr<CompareFunction> compareFunctionToAdd) {
    this->comparatorList.push_back(compareFunctionToAdd);
}

SortChain::~SortChain() {
    gfm_debug("Destrcutor of sortChain\n");
    comparatorList.clear ();
}

void SortChain::sort(std::vector<FileListElement>& dataToSort) {
    std::sort(dataToSort.begin(), dataToSort.end(), *this);
}
