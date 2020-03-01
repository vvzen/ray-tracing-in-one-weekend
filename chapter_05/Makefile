CC=g++
VERBOSE=--verbose

main: main.cpp
	rm -f main
	$(CC) -std=c++11 main.cpp -o main

run: main
	rm -f chapter_05.ppm
	./main

clean:
	rm -f main
	rm -f chapter_05.ppm