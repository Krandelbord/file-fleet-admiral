cmake_minimum_required(VERSION 3.3)
project(gtkmm-file-manager)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -DDEBUG")


find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0) # look into FindPkgConfig.cmake,
# it contains documentation
# Now the variables GTKMM_INCLUDE_DIRS, GTKMM_LIBRARY_DIRS and GTKMM_LIBRARIES
# contain what you expect

link_directories(
        ${GTKMM_LIBRARY_DIRS}  )
include_directories(
        ${GTKMM_INCLUDE_DIRS}  )

ADD_SUBDIRECTORY( tests )

set(SOURCE_FILES
        config.h
        debug.cc
        debug.h
        CompareBySize.h CompareBySize.cc
        CompareDirsFirst.h CompareDirsFirst.cc
        CompareByName.h CompareByName.cc
        FileListElement.cc FileListElement.h
        FilePanelFooter.cc FilePanelFooter.h
        FilesColumns.cc FilesColumns.h
        FilesNavigationPanel.cc FilesNavigationPanel.h
        FilesSortType.h
        FilesTreeView.cc FilesTreeView.h
        FileType.h
        GuiReader.cc GuiReader.h
        main.cc
        MainWindow.cc MainWindow.h
        MenuBar.cc MenuBar.h
        PanelHeader.cc PanelHeader.h
        PathResolver.cc PathResolver.h
        Preconditions.cc Preconditions.h
        Rectangle.cc Rectangle.h
        SelectionHistory.cc SelectionHistory.h
        Settings.cc Settings.h
        SettingsWindow.cc SettingsWindow.h
        SinglePanel.cc SinglePanel.h
        SizeFormatterSpaces.cc SizeFormatterSpaces.h
        SizeFormatterSimple.cc SizeFormatterSimple.h
        SizeFormatterHr.cc SizeFormatterHr.h
        SizeFormatter.h
        SizeFormatterFactory.cc SizeFormatterFactory.h
        SortChain.h SortChain.cc
        ThreadCalculation.cc ThreadCalculation.h
        ThreadMessage.cc ThreadMessage.h
        CompareBySize.cc CompareBySize.h)
add_executable(gtkmm-file-manager ${SOURCE_FILES})

target_link_libraries(gtkmm-file-manager
        ${GTKMM_LIBRARIES}  )
