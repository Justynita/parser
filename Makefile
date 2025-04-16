SRCDIR = src
OBJDIR = obj

SOURCES = $(shell find $(SRCDIR) -name "*.cpp")
OBJECTS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SOURCES))

TARGET = parser

all: $(TARGET)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	g++ -std=c++17 -g -Wall -c $< -o $@

$(TARGET): $(OBJECTS)
	g++ -std=c++17 -g -Wall $^ -o $@
