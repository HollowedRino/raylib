all: build

build:
	g++ -Wall -I./include -L./lib -c estructuras.cpp -lraylib -lopengl32 -lgdi32 -lwinmm
	g++ -Wall -I./include -L./lib estructuras.o main.cpp -o main -lraylib -lopengl32 -lgdi32 -lwinmm
	./main.exe
clean:
	-rm -rf *.o
	-rm -rf *.exe