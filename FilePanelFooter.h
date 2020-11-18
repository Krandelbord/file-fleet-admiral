#ifndef GTKMM_FILE_MANAGER_FILEPANELFOOTER_H
#define GTKMM_FILE_MANAGER_FILEPANELFOOTER_H


#include <gtkmm/hvbox.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>

/**
 * Foot in one files panel displays currently highlited element
 */
class FilePanelFooter : public Gtk::VBox {
public:
    FilePanelFooter();

    void changeFooterValue(Glib::ustring ustring);

    void showQuickSearch();

    typedef sigc::signal<void, Glib::ustring> searchDataSignal;
    searchDataSignal signalOnQuickSearchChanged();
    searchDataSignal signalOnEnterPressedInQuickSearch();
    searchDataSignal signalOnSearchNext();
    sigc::signal<void()> signalOnQuickSearchClosed();

private:
    Gtk::Label directoryLabel;
    Gtk::Entry searchInput;
    bool quickSearchIsVisible;
    searchDataSignal signalQuickSearchHashNewValue;
    searchDataSignal signalEnterPressedInQuickSearch;
    searchDataSignal signalSearchNext;
    sigc::signal<void()> signalQuickSearchClosed;

    bool keyShouldBeIgnored(GdkEventKey key_event);
    bool onKeyPressedInSearch(const GdkEventKey *key_event);
    void closeQuickSearch();

};

#endif //GTKMM_FILE_MANAGER_FILEPANELFOOTER_H
