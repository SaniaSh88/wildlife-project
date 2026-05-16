# ============================================================
# Makefile - Wildlife Photography Catalog & Conservation Platform
# Usage:
#   make        → compile the project
#   make run    → compile and run
#   make clean  → remove compiled files
# ============================================================

CXX      = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -g
TARGET   = wildlife_catalog
SRCS     = main.cpp Photo.cpp Animal.cpp Species.cpp Habitat.cpp Catalog.cpp
OBJS     = $(SRCS:.cpp=.o)

# Default target: compile
all: $(TARGET)
	@echo ""
	@echo "  ✅ Build successful! Run with: ./$(TARGET)"
	@echo ""

# Link object files into final executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Compile individual source files
main.o:     main.cpp Catalog.h Animal.h Species.h Habitat.h Photo.h
	$(CXX) $(CXXFLAGS) -c main.cpp

Photo.o:    Photo.cpp Photo.h
	$(CXX) $(CXXFLAGS) -c Photo.cpp

Animal.o:   Animal.cpp Animal.h Photo.h
	$(CXX) $(CXXFLAGS) -c Animal.cpp

Species.o:  Species.cpp Species.h Animal.h
	$(CXX) $(CXXFLAGS) -c Species.cpp

Habitat.o:  Habitat.cpp Habitat.h
	$(CXX) $(CXXFLAGS) -c Habitat.cpp

Catalog.o:  Catalog.cpp Catalog.h Animal.h Species.h Habitat.h Photo.h
	$(CXX) $(CXXFLAGS) -c Catalog.cpp

# Compile and run
run: all
	./$(TARGET)

# Clean compiled files
clean:
	rm -f $(OBJS) $(TARGET)
	@echo "  🧹 Cleaned build artifacts."

.PHONY: all run clean