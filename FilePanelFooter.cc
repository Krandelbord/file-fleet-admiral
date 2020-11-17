#include "FilePanelFooter.h"
#include <gtkmm.h>
#include "config.h"

FilePanelFooter::FilePanelFooter() {
    directoryLabel.set_label("");
    add(directoryLabel);
}

void FilePanelFooter::changeFooterValue(Glib::ustring ustring) {
    directoryLabel.set_label(ustring);
}

void FilePanelFooter::showQuickSearch() {
//    directoryLabel.hide();
    add(searchInput);
    searchInput.show();
    searchInput.grab_focus();
    searchInput.signal_key_release_event().connect(sigc::mem_fun(*this, &FilePanelFooter::onKeyPressedInSearch));
}

bool FilePanelFooter::onKeyPressedInSearch(const GdkEventKey *key_event) {
    gfm_debug("\nPressed %x\n", key_event->keyval);
    if (key_event->keyval == GDK_KEY_Escape) {
        this->closeQuickSearch();
    } else if (key_event->keyval == GDK_KEY_KP_Enter || key_event->keyval == GDK_KEY_Return) {
        gfm_debug("Enter pressed");
        signalEnterPressedInQuickSearch.emit(searchInput.get_text());
        this->closeQuickSearch();
    } else if (key_event->keyval != GDK_KEY_Tab) {
        signalQuickSearchHashNewValue.emit(searchInput.get_text());
    }
    return true;
}

void FilePanelFooter::closeQuickSearch() {
    this->remove(searchInput);
    directoryLabel.show();
    this->queue_draw();
}

FilePanelFooter::searchDataSignal FilePanelFooter::signalOnQuickSearchChanged() {
    return signalQuickSearchHashNewValue;
}

FilePanelFooter::searchDataSignal  FilePanelFooter::signalOnEnterPressedInQuickSearch() {
    return signalEnterPressedInQuickSearch;
}
