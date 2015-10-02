DEBUG='true'
OUT=gfm

ifdef DEBUG
	CXXFLAGS+=-g3 -DDEBUG 
endif

CXXFLAGS+=-Wall -std=c++11


CXXFLAGS+=`pkg-config --cflags gtkmm-3.0`
LDFLAGS+=`pkg-config --libs gtkmm-3.0`

$(OUT): main.o MainWindow.o SinglePanel.o debug.o Settings.o Rectangle.o FilesNavigationPanel.o \
	FilesColumns.o MenuBar.o PanelHeader.o FilesReadWorker.o FileListElement.o PathResolver.o \
	FilesTreeView.o Preconditions.o SelectionHistory.o ThreadCalculation.o GuiReader.o ThreadMessage.o \
	$(CXX) $(LDFLAGS) $^ -o $@

include makefile.dep

dep:
	$(CXX) -std=c++11 -MM *.cc >makefile.dep

.PHONY: clean tests

clean:
	-rm *.o
	-rm $(OUT)
	make -C tests clean


#CXXFLAGS+=-I/home/emil/programy/snowhouse/
tests: 
	make -C tests

tests2: tests/readDirTest
	
