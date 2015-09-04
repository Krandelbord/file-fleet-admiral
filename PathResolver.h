#ifndef PATH_RESOLVER
#define PATH_RESOLVER

#include <glibmm.h>

/** Symbol of parent directory **/
#define PARENT_DIR_SYMBOL ".."

class PathResolver {
    public:
        PathResolver(const Glib::ustring& startPath);
        void changeDirBy(const Glib::ustring& changeDirPath);
        Glib::ustring toString() const;

    private:
        Glib::ustring pathAsString;

        void changeDirUp();
};
#endif /** PATH_RESOLVER **/
