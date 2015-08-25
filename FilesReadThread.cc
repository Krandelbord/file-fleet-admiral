#include "FilesReadThread.h"
#include "config.h"

FilesReadThread::FilesReadThread(const Glib::ustring& dirToRead) {
    this->launch();
}

void FilesReadThread::launch() {
    gfm_debug("Thread was launched\n");
	Glib::Thread::create(sigc::mem_fun(*this, &FilesReadThread::thread_function), false);
}

void FilesReadThread::thread_function() {
	gfm_debug("Inside thread function \n");

    m_signal_on_new_data.emit();
	//m_signal_finished.emit();
}

sigc::signal<void>& FilesReadThread::singalNewDataFromThread() {
    return m_signal_on_new_data;
}
