CXXFLAGS = -g -Wall -Wextra -pedantic -std=c++20 -fsanitize=address -rdynamic
CXX := g++
SRCDIR := src
BINDIR := bin
DEPDIR := deps
LEXER_SRC := $(SRCDIR)/ast/lexer.l
PARSER_SRC := $(SRCDIR)/ast/parser.y

# Find all .cpp files in the src directory and its subdirectories
SRCS := $(shell find $(SRCDIR) -type f -name '*.cpp')
SRCS += $(SRCDIR)/ast/lexer.yy.cpp
SRCS += $(SRCDIR)/ast/parser.tab.cpp

# Object files (preserve directory structure)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(BINDIR)/%.o,$(SRCS))

# Dependency files (preserve directory structure)
DEPS := $(OBJS:.o=.d)

OUTPUT := ucc

# Phony targets
.PHONY: all clean gdb run

# Default target
all: $(OUTPUT)

# Linking rule
$(OUTPUT): $(OBJS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Compilation rule
$(BINDIR)/%.o: $(SRCDIR)/%.cpp $(SRCDIR)/ast/lexer.yy.cpp $(SRCDIR)/ast/parser.tab.cpp $(SRCDIR)/ast/parser.tab.hpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

# Flex rule for generating lexer
$(SRCDIR)/ast/lexer.yy.cpp: $(LEXER_SRC) $(SRCDIR)/ast/parser.tab.hpp
	flex -o $@ $<

# Bison rule for generating parser
$(SRCDIR)/ast/parser.tab.cpp $(SRCDIR)/ast/parser.tab.hpp: $(PARSER_SRC)
	bison -o $(SRCDIR)/ast/parser.tab.cpp -d $<

# Additional dependencies for lexer and parser
$(SRCDIR)/lexer.yy.o: $(SRCDIR)/ast/lexer.yy.cpp $(SRCDIR)/ast/parser.tab.hpp
$(SRCDIR)/parser.tab.o: $(SRCDIR)/ast/parser.tab.cpp $(SRCDIR)/ast/parser.tab.hpp

# Include dependency files
-include $(DEPS)

# Clean target
clean:
	@echo -e "\ncleaning project\n"
	@rm -rf $(BINDIR) $(DEPDIR)
	@rm $(SRCDIR)/ast/lexer.yy.cpp
	@rm $(SRCDIR)/ast/parser.tab.hpp
	@rm $(SRCDIR)/ast/parser.tab.cpp

gdb: $(OUTPUT)
	gdb --args ./$(OUTPUT) -Stestsrc.c -otestout.s

run: $(OUTPUT)
	./$(OUTPUT) -Stestsrc.c -otestout.s

#test:
#export ASAN_OPTIONS=abort_on_error=1


