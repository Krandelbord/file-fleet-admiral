#include "FilePanelFooter.h"
#include <gtkmm.h>

FilePanelFooter::FilePanelFooter() {
    directoryLabel.set_label("");
    this->add(directoryLabel);
    this->show_all();
}

void FilePanelFooter::changeFooterValue(Glib::ustring ustring) {
    directoryLabel.set_label(ustring);
}
