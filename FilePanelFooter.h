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
    searchDataSignal singalOnQuickSearchChanged();

private:
    Gtk::Label directoryLabel;
    Gtk::Entry searchInput;
    searchDataSignal newQuickSearchTextSignal;

    bool onKeyPressedInSearch(const GdkEventKey *key_event);

    void closeQuickSearch();

};

#endif //GTKMM_FILE_MANAGER_FILEPANELFOOTER_H
