#include "SortChain.h"
#include "FileListElement.h"
#include "config.h"


SortChain::SortChain(CompareFunction* compareFunction) {
    this->comparatorList.push_back(compareFunction);
}

bool SortChain::operator()(const FileListElement& first, const FileListElement& second) const {
    for (CompareFunction* oneOfCmpFunction : comparatorList) {
        gfm_debug("Sorotwanie %s\n", typeid(oneOfCmpFunction).name());
        if (oneOfCmpFunction->compare(first, second) == CompareResult::FIRST_IS_LESS) {
            return false;
        } else if (oneOfCmpFunction->compare(first, second) == CompareResult::SECOND_IS_LESS) {
            return true;
        }
        //else another comparator in chain will check
    }
    return false;
}

void SortChain::add(CompareFunction* compareFunctionToAdd) {
    this->comparatorList.push_back(compareFunctionToAdd);
}

SortChain::~SortChain() {
    gfm_debug("Destrcutor of sortChain\n");
    for (CompareFunction* oneOfCmpFunction : comparatorList) {
        delete(oneOfCmpFunction);
    }
    comparatorList.clear ();
}
