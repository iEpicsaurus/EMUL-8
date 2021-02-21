NAME    := emul8
SOURCES := src src/controller src/cpu src/gpu src/logger src/memory src/timer src/ui
ARGS    := -O2 -no-pie
LIBS    := `wx-config --cxxflags --libs`

CPPFILES := $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.cpp))
HFILES   := $(foreach dir,$(SOURCES),$(wildcard $(dir)/*.h))

$(NAME): $(CPPFILES) $(HFILES)
	g++ -o $@ $(ARGS) $(CPPFILES) $(LIBS)

clean:
	rm -f $(NAME)
