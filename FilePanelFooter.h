#ifndef GTKMM_FILE_MANAGER_FILEPANELFOOTER_H
#define GTKMM_FILE_MANAGER_FILEPANELFOOTER_H


#include <gtkmm/hvbox.h>
#include <gtkmm/label.h>

/**
 * Foot in one files panel displays currently highlited element
 */
class FilePanelFooter : public Gtk::VBox {
public:
    FilePanelFooter();

    void changeFooterValue(Glib::ustring ustring);

private:
    Gtk::Label directoryLabel;
};

#endif //GTKMM_FILE_MANAGER_FILEPANELFOOTER_H
