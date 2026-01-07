CXX = g++
CXXFLAGS = -std=c++11 -Wall -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib -lraylib -framework IOKit -framework Cocoa -framework OpenGL

programmet: wordle.cpp wordlefunc.cpp wordlefunc.h
	$(CXX) $(CXXFLAGS) wordle.cpp wordlefunc.cpp $(LDFLAGS) -o programmet

run: programmet
	./programmet

clean:
	rm -f programmet