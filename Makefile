all: build

build:
	g++ -Wall -I./include -L./lib main.cpp -o main -lraylib -lopengl32 -lgdi32 -lwinmm
	./main.exe
clean:
	-rm -rf *.o
	-rm -rf *.exe