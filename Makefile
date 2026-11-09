CXX ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall -Wextra

glyphbreak: src/*.cpp src/*.h
	$(CXX) $(CXXFLAGS) -o glyphbreak src/*.cpp

clean:
	rm -f glyphbreak
