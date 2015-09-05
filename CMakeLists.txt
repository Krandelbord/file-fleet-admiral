cmake_minimum_required(VERSION 3.3)
project(gtkmm-file-manager)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")


find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0) # look into FindPkgConfig.cmake,
# it contains documentation
# Now the variables GTKMM_INCLUDE_DIRS, GTKMM_LIBRARY_DIRS and GTKMM_LIBRARIES
# contain what you expect

link_directories(
        ${GTKMM_LIBRARY_DIRS}  )
include_directories(
        ${GTKMM_INCLUDE_DIRS}  )

set(SOURCE_FILES main.cc
        FilesTreeView.cc
        MainWindow.cc
        PanelHeader.cc
        PathResolver.cc
        Settings.cc
        SinglePanel.cc
        FileListElement.cc
        FilesColumns.cc
        FilesNavigationPanel.cc
        FilesReadWorker.cc
        debug.cc
        MenuBar.cc
        Rectangle.cc
        Preconditions.cc)
add_executable(gtkmm-file-manager ${SOURCE_FILES})

target_link_libraries(gtkmm-file-manager
        ${GTKMM_LIBRARIES}  )