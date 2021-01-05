cmake_minimum_required(VERSION 3.3)
project(gtkmm-file-manager)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -DDEBUG")


find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0) # look into FindPkgConfig.cmake,
# it contains documentation
# Now the variables GTKMM_INCLUDE_DIRS, GTKMM_LIBRARY_DIRS and GTKMM_LIBRARIES
# contain what you expect

link_directories(
        ${GTKMM_LIBRARY_DIRS}  )
include_directories(
        ${GTKMM_INCLUDE_DIRS}  )

set(TEST_SOURCES_COMMON
        Asserts.cc Asserts.h Runner.h Runner.cc
        ../src/debug.cc ../src/debug.h)

ADD_EXECUTABLE( readDirTest readDirTest.cc
        ${TEST_SOURCES_COMMON}
        ../src/gui/PathResolver.cc ../src/gui/PathResolver.h
        ../src/gui/SelectionHistory.h ../src/gui/SelectionHistory.cc)

ADD_EXECUTABLE( readMultiThreadDirs readMultiThreadDirs.cc
        ../src/sort/CompareByName.h ../src/sort/CompareByName.cc
        ../src/sort/SortChain.h ../src/sort/SortChain.cc
        ../src/gui/GuiReader.h ../src/gui/GuiReader.cc
        ../src/gui/file_panel/FileListElement.h ../src/gui/file_panel/FileListElement.cc
        ../src/ThreadMessage.h ../src/ThreadMessage.cc
        ../src/ThreadCalculation.h ../src/ThreadCalculation.cc
        ../src/gui/SizeFormatterFactory.h ../src/gui/SizeFormatterFactory.cc
        ../src/settings/Settings.h ../src/settings/Settings.cc
        ../src/gui/PathResolver.h ../src/gui/PathResolver.cc
        ../src/gui/SizeFormatterSimple.h ../src/gui/SizeFormatterSimple.cc
        ../src/gui/SizeFormatterHr.h ../src/gui/SizeFormatterHr.cc
        ../src/gui/Rectangle.h ../src/gui/Rectangle.cc
        ../src/gui/SizeFormatterSpaces.h ../src/gui/SizeFormatterSpaces.cc
        ${TEST_SOURCES_COMMON})

ADD_EXECUTABLE( sizeDisplayTest sizeDisplayTest.cc
        ../src/gui/SizeFormatter.h
        ../src/gui/SizeFormatterSimple.h ../src/gui/SizeFormatterSimple.cc
        ../src/gui/SizeFormatterSpaces.cc ../src/gui/SizeFormatterSpaces.h
        ${TEST_SOURCES_COMMON} ../src/gui/SizeFormatterHr.cc ../src/gui/SizeFormatterHr.h)

ADD_EXECUTABLE(sortChainTest sortChainTest.cc
        ../src/sort/SortChain.h ../src/sort/SortChain.cc
        ../src/gui/file_panel/FileListElement.h ../src/gui/file_panel/FileListElement.cc
        ../src/sort/CompareByName.h ../src/sort/CompareByName.cc
        ../src/sort/CompareDirsFirst.h ../src/sort/CompareDirsFirst.cc
        ../src/sort/CompareBySize.h ../src/sort/CompareBySize.cc
        ${TEST_SOURCES_COMMON}
)

target_link_libraries(readDirTest ${GTKMM_LIBRARIES}  )
target_link_libraries(sizeDisplayTest ${GTKMM_LIBRARIES}  )
target_link_libraries(sortChainTest ${GTKMM_LIBRARIES}  )
target_link_libraries(readMultiThreadDirs ${GTKMM_LIBRARIES})
