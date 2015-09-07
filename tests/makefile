#include ../makefile.dep
CXXFLAGS+=-Wall -std=c++11 -DDEBUG

CXXFLAGS+=-I/home/emil/programy/snowhouse/
CXXFLAGS+=`pkg-config --cflags gtkmm-3.0`
LDFLAGS+=`pkg-config --libs gtkmm-3.0`

#$(OBJDIR)/%.o: %.cc | $(OBJDIR)
#	$(COMPILE.cc) $(OUTPUT_OPTION) $<

readDirTest: readDirTest.o ../PathResolver.o ../SelectionHistory.o ../debug.o
	$(CXX) $(LDFLAGS) $^ -o $@
	./$@

clean:
	-rm *.o
	-rm readDirTest

.PHONY: readDirTest clean

