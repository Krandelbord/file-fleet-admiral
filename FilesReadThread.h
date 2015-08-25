#ifndef FILES_READ_THREAD_H
#define FILES_READ_THREAD_H

#include <glibmm.h>

/**
 * Thread that reads directory content 
 * **/
class FilesReadThread {
    public:
        FilesReadThread(const Glib::ustring& pathToRead);
        //launches reading data
        void launch();

        //signal emited when thread prepares new portion of data 
        sigc::signal<void> &singalNewDataFromThread();

    private:
        sigc::signal<void>	m_signal_on_new_data;

        void thread_function();
};
#endif /** FILES_READ_THREAD_H **/
