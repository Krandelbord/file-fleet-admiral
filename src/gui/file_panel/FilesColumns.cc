#include "FilesColumns.h"

FilesColumns::FilesColumns() {
    this->add(file_name_column);
    this->add(size_column);
    this->add(font_weight);
    this->add(backgroundColor);
    this->add(inodeNumber);
}
