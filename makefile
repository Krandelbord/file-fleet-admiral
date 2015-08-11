DEBUG='true'

OUT=gfm

ifdef DEBUG
	CXXFLAGS+=-g3 -DDEBUG
endif

CXXFLAGS+=-Wall


CXXFLAGS+=`pkg-config --cflags gtkmm-2.4`
LDFLAGS+=`pkg-config --libs gtkmm-2.4`

$(OUT): main.o 
	$(CXX) $(LDFLAGS) $^ -o $@

include makefile.dep

dep:
	$(CXX) -MM *.cc >makefile.dep

.PHONY: clean

clean:
	-rm *.o
	-rm $(OUT)
