#include "FilePanelFooter.h"
#include <gtkmm.h>
#include "../../config.h"

FilePanelFooter::FilePanelFooter() {
    directoryLabel.set_label("");
    quickSearchIsVisible = false;
    add(directoryLabel);
}

void FilePanelFooter::changeFooterValue(Glib::ustring ustring) {
    directoryLabel.set_label(ustring);
}

void FilePanelFooter::showQuickSearch() {
    if (quickSearchIsVisible) {
        signalSearchNext.emit(searchInput.get_text());
    } else {
        directoryLabel.hide();
        add(searchInput);
        searchInput.show();
        searchInput.grab_focus();
        searchInput.signal_key_release_event().connect(sigc::mem_fun(*this, &FilePanelFooter::onKeyPressedInSearch));
        quickSearchIsVisible = true;
    }
}

typedef std::shared_ptr<std::function<bool(GdkEventKey)> > KeyVerifier;

template <class Functor> KeyVerifier createDelegate(Functor f) {
    return KeyVerifier(new std::function<bool(GdkEventKey)>(f));
}

bool isCtrl_S(const GdkEventKey key_event) {
    return key_event.state & GDK_CONTROL_MASK && (key_event.keyval == GDK_KEY_s || key_event.keyval == GDK_KEY_S);
}

bool FilePanelFooter::keyShouldBeIgnored(const GdkEventKey key_event) {
    std::vector<KeyVerifier> ignoreRules = std::vector<KeyVerifier>();
    ignoreRules.push_back(createDelegate(isCtrl_S));
    ignoreRules.push_back(createDelegate([](GdkEventKey k){ return k.keyval == GDK_KEY_Control_L;}));

    for (const KeyVerifier& oneIgnoreRule : ignoreRules) {
        if (oneIgnoreRule->operator()(key_event)) {
            return true;
        }
    }
    return false;
}

bool FilePanelFooter::onKeyPressedInSearch(const GdkEventKey *key_event) {
    gfm_debug("Pressed key inside panel footer %x\n", key_event->keyval);
    if (keyShouldBeIgnored(*key_event)) {
        return true;
    } else if (key_event->keyval == GDK_KEY_Escape) {
        this->closeQuickSearch();
    } else if (key_event->keyval == GDK_KEY_KP_Enter || key_event->keyval == GDK_KEY_Return) {
        signalEnterPressedInQuickSearch.emit(searchInput.get_text());
        this->closeQuickSearch();
    } else if (key_event->keyval != GDK_KEY_Tab) {
        signalQuickSearchHashNewValue.emit(searchInput.get_text());
    }
    return true;
}

void FilePanelFooter::closeQuickSearch() {
    if (quickSearchIsVisible) {
        this->remove(searchInput);
        directoryLabel.show();
        this->queue_draw();
        signalQuickSearchClosed.emit();
        quickSearchIsVisible = false;
    }
}

FilePanelFooter::searchDataSignal FilePanelFooter::signalOnQuickSearchChanged() {
    return signalQuickSearchHashNewValue;
}

FilePanelFooter::searchDataSignal  FilePanelFooter::signalOnEnterPressedInQuickSearch() {
    return signalEnterPressedInQuickSearch;
}

FilePanelFooter::searchDataSignal  FilePanelFooter::signalOnSearchNext() {
    return signalSearchNext;
}

sigc::signal<void()> FilePanelFooter::signalOnQuickSearchClosed() {
    return signalQuickSearchClosed;
}
