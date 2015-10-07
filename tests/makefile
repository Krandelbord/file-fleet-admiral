#include ../makefile.dep
CXXFLAGS+=-Wall -std=c++11 -DDEBUG -g3

CXXFLAGS+=-I/home/emil/programy/snowhouse/
CXXFLAGS+=`pkg-config --cflags gtkmm-3.0`
LDFLAGS+=`pkg-config --libs gtkmm-3.0`

#$(OBJDIR)/%.o: %.cc | $(OBJDIR)
#	$(COMPILE.cc) $(OUTPUT_OPTION) $<

runTests: readDirTest readMultiThreadDirs
	./readDirTest
	./readMultiThreadDirs

readDirTest: Asserts.o Runner.o readDirTest.o ../PathResolver.o ../SelectionHistory.o ../debug.o
	$(CXX) $(LDFLAGS) $^ -o $@


readMultiThreadDirs: Asserts.o Runner.o readMultiThreadDirs.o ../PathResolver.o ../SelectionHistory.o ../debug.o \
	../FileListElement.o ../ThreadMessage.o ../GuiReader.o ../ThreadCalculation.o
	$(CXX) $(LDFLAGS) $^ -o $@

clean:
	-rm *.o
	-rm readDirTest
	-rm readMultiThreadDirs

.PHONY: readDirTest clean

