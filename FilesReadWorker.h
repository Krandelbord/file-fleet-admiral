#ifndef FILES_READ_WORKER_H
#define FILES_READ_WORKER_H

#include <glibmm.h>

/** Aby pokręcone zależnosci działały **/
class SinglePanel;

/**
 * Thread that reads directory content 
 * **/
class FilesReadWorker {
    public:
        FilesReadWorker(const Glib::ustring& pathToRead);

        void thread_function(SinglePanel* caller);
        const Glib::ustring getDataFromThread() const;
    private:
        Glib::ustring dirToRead;

        //mutex for data read/write
        mutable Glib::Threads::Mutex mutexForData;
        Glib::ustring fileDataRead;
        

};
#endif /** FILES_READ_WORKER_H **/
