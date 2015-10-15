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

set(TEST_SOURCES_COMMON
        Asserts.cc Asserts.h Runner.h Runner.cc
        ../debug.cc ../debug.h)

ADD_EXECUTABLE( readDirTest readDirTest.cc
        ${TEST_SOURCES_COMMON}
        ../PathResolver.cc ../PathResolver.h
        ../SelectionHistory.h ../SelectionHistory.cc)

ADD_EXECUTABLE( readMultiThreadDirs readMultiThreadDirs.cc
        ${TEST_SOURCES_COMMON})

ADD_EXECUTABLE( sizeDisplayTest sizeDisplayTest.cc
        ../SizeFormatter.h
        ../SizeFormatterSimple.h ../SizeFormatterSimple.cc
        ../SizeFormatterSpaces.cc ../SizeFormatterSpaces.h
        ${TEST_SOURCES_COMMON} ../SizeFormatterHr.cc ../SizeFormatterHr.h)

ADD_EXECUTABLE(sortChainTest sortChainTest.cc
        ../SortChain.h ../SortChain.cc
        ../FileListElement.h ../FileListElement.cc
        ../CompareByName.h ../CompareByName.cc
        ../CompareDirsFirst.h ../CompareDirsFirst.cc
        ${TEST_SOURCES_COMMON}
)

target_link_libraries(readDirTest ${GTKMM_LIBRARIES}  )
target_link_libraries(sizeDisplayTest ${GTKMM_LIBRARIES}  )
target_link_libraries(sortChainTest ${GTKMM_LIBRARIES}  )
