FLAGS = -std=c++20
FILES = ../util.cpp main.cpp

.PHONY: all main clean
all: main
main: $(FILES)
	g++ -o $@.out $(FLAGS) $^

clean:
	rm -f main.out
