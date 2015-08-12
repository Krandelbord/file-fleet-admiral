DEBUG='true'

OUT=gfm

ifdef DEBUG
	CXXFLAGS+=-g3 -DDEBUG 
endif

CXXFLAGS+=-Wall -std=c++11


CXXFLAGS+=`pkg-config --cflags gtkmm-2.4`
LDFLAGS+=`pkg-config --libs gtkmm-2.4`

$(OUT): main.o MainWindow.o SinglePanel.o debug.o Settings.o Rectangle.o
	$(CXX) $(LDFLAGS) $^ -o $@

include makefile.dep

dep:
	$(CXX) -MM *.cc >makefile.dep

.PHONY: clean

clean:
	-rm *.o
	-rm $(OUT)
