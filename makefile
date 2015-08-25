DEBUG='true'

OUT=gfm

ifdef DEBUG
	CXXFLAGS+=-g3 -DDEBUG 
endif

CXXFLAGS+=-Wall -std=c++11


CXXFLAGS+=`pkg-config --cflags gtkmm-3.0`
LDFLAGS+=`pkg-config --libs gtkmm-3.0`

$(OUT): main.o MainWindow.o SinglePanel.o debug.o Settings.o Rectangle.o FilesNavigationPanel.o \
	FilesColumns.o MenuBar.o PanelHeader.o
	$(CXX) $(LDFLAGS) $^ -o $@

include makefile.dep

dep:
	$(CXX) -MM *.cc >makefile.dep

.PHONY: clean

clean:
	-rm *.o
	-rm $(OUT)
