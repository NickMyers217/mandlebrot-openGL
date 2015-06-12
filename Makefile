CC = g++
FLAGS = -pedantic -Wall -lSDL2 -lGL -lGLEW
SRCPATH = ./src/
SOURCES = \
	$(SRCPATH)main.c \
	$(SRCPATH)shader.c
EXECUTABLE = opengl

all:
	$(CC) $(SOURCES) $(FLAGS) -o $(EXECUTABLE)

clean:
	rm $(EXECUTABLE)
