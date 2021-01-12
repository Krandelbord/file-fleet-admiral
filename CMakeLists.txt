cmake_minimum_required(VERSION 3.3)
project(file-fleet-admiral)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -DDEBUG")

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
        src/config.h
        src/debug.cc
        src/debug.h
        src/sort/CompareBySize.h src/sort/CompareBySize.cc
        src/sort/CompareDirsFirst.h src/sort/CompareDirsFirst.cc
        src/sort/CompareByName.h src/sort/CompareByName.cc
        src/gui/file_panel/FileListElement.cc src/gui/file_panel/FileListElement.h
        src/gui/file_panel/FilePanelFooter.cc src/gui/file_panel/FilePanelFooter.h
        src/gui/file_panel/FilesColumns.cc src/gui/file_panel/FilesColumns.h
        src/gui/file_panel/FilesNavigationPanel.cc src/gui/file_panel/FilesNavigationPanel.h
        src/sort/FilesSortType.h
        src/gui/file_panel/FilesTreeView.cc src/gui/file_panel/FilesTreeView.h
        src/gui/FileType.h
        src/gui/GuiReader.cc src/gui/GuiReader.h
        src/gui/main.cc
        src/gui/MainWindow.cc src/gui/MainWindow.h
        src/gui/MenuBar.cc src/gui/MenuBar.h
        src/gui/PanelHeader.cc src/gui/PanelHeader.h
        src/gui/PathResolver.cc src/gui/PathResolver.h
        src/Preconditions.cc src/Preconditions.h
        src/gui/Rectangle.cc src/gui/Rectangle.h
        src/gui/SelectionHistory.cc src/gui/SelectionHistory.h
        src/settings/Settings.cc src/settings/Settings.h
        src/gui/SettingsWindow.cc src/gui/SettingsWindow.h
        src/gui/file_panel/SinglePanel.cc src/gui/file_panel/SinglePanel.h
        src/gui/SizeFormatterSpaces.cc src/gui/SizeFormatterSpaces.h
        src/gui/SizeFormatterSimple.cc src/gui/SizeFormatterSimple.h
        src/gui/SizeFormatterHr.cc src/gui/SizeFormatterHr.h
        src/gui/SizeFormatter.h
        src/gui/SizeFormatterFactory.cc src/gui/SizeFormatterFactory.h
        src/sort/SortChain.h src/sort/SortChain.cc
        src/ThreadCalculation.cc src/ThreadCalculation.h
        src/ThreadMessage.cc src/ThreadMessage.h
        src/sort/CompareBySize.cc src/sort/CompareBySize.h
        src/gui/RenamePopup.cc src/gui/RenamePopup.h
        src/operations/RenameExecutor.cc src/operations/RenameExecutor.h
        src/operations/InterThreadProgressPipe.cc src/operations/InterThreadProgressPipe.h
        src/operations/ThreadPerformingRename.cc src/operations/ThreadPerformingRename.h
        src/operations/NotifiableByContentChange.cc src/operations/NotifiableByContentChange.h
        src/gui/FileWithInode.cc src/gui/FileWithInode.h
        src/icon_provider/FileTypeIconProvider.cc src/icon_provider/FileTypeIconProvider.h
        src/icon_provider/FileAndDirectoryStaticIconProvider.cc src/icon_provider/FileAndDirectoryStaticIconProvider.h
        src/icon_provider/AlwaysSameIconProvider.cc src/icon_provider/AlwaysSameIconProvider.h
        src/icon_provider/IconProvider.cc src/icon_provider/IconProvider.h)
add_executable(file-fleet-admiral ${SOURCE_FILES})


target_compile_features(file-fleet-admiral PRIVATE cxx_std_14)


target_link_libraries(file-fleet-admiral
        pthread
        ${GTKMM_LIBRARIES}  )


include(CTest)
add_test(NAME Runs-readDirTest COMMAND tests/readDirTest)
add_test(NAME sizeDisplayTest COMMAND tests/sizeDisplayTest)
add_test(NAME sortChainTest COMMAND tests/sortChainTest)
add_test(NAME readMultiThreadDirs COMMAND tests/readMultiThreadDirs)