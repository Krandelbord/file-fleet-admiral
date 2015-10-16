DEBUG='true'
OUT=gfm

ifdef DEBUG
	CXXFLAGS+=-g3 -DDEBUG 
endif

CXXFLAGS+=-Wall -std=c++11


CXXFLAGS+=`pkg-config --cflags gtkmm-3.0`
LDFLAGS+=`pkg-config --libs gtkmm-3.0`

$(OUT): CompareByName.o CompareBySize.o CompareDirsFirst.o CompareFunction.o debug.o FileListElement.o \
	FilePanelFooter.o FilesColumns.o FilesNavigationPanel.o FilesTreeView.o GuiReader.o main.o \
  	MainWindow.o MenuBar.o PanelHeader.o PathResolver.o Preconditions.o Rectangle.o SelectionHistory.o \
	Settings.o SettingsWindow.o SinglePanel.o SizeFormatterFactory.o SizeFormatterHr.o SizeFormatterSimple.o \
	SizeFormatterSpaces.o SortChain.o ThreadCalculation.o ThreadMessage.o
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
	
