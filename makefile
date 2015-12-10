EXECUTABLE=main

INC=-Iheaders
SRCDIR=sources
OBJDIR=obj
DEPDIR=dependencies
SOURCES=$(wildcard $(SRCDIR)/*.cpp)
OBJECTS=$(addprefix $(OBJDIR)/,$(notdir $(SOURCES:.cpp=.o)))

CC=g++
CFLAGS=-c -Wall -g -std=c++11
LDFLAGS=-lm 
#-lSDL2 -lSDL2_image
DEPFLAGS = -MMD $(DEPDIR)/$*.Td

$(shell mkdir -p $(OBJDIR))
$(shell mkdir -p $(DEPDIR))

all: $(SOURCES) $(EXECUTABLE)

tester: $(OBJECTS) tester.cpp
	$(CC) $(filter-out $(OBJDIR)/main.o, $(OBJECTS)) tester.cpp $(LDFLAGS) -o tester
    
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) $(CFLAGS) $(INC) -MMD -c -o $@ $<

clean:
	rm $(EXECUTABLE) $(OBJDIR)/* $(DEPDIR)/*

$(DEPDIR)/dependencies.d: ;