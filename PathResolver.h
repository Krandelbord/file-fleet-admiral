#ifndef PATH_RESOLVER
#define PATH_RESOLVER

#include <glibmm.h>

class PathResolver {
    public:
        PathResolver(const Glib::ustring& startPath);
        PathResolver changeDirBy(const Glib::ustring& changeDirPath);
        Glib::ustring toString() const;

    private:
        Glib::ustring pathAsString;
};
#endif /** PATH_RESOLVER **/
