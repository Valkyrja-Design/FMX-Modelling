CC=g++

OPENGLLIB= -lGL
GLEWLIB= -lGLEW
GLFWLIB = -lglfw
LIBS=$(OPENGLLIB) $(GLEWLIB) $(GLFWLIB)
LDFLAGS=-L/usr/local/lib 
CPPFLAGS=-I/usr/local/include -I./src/include/

BIN1=./bin/a2-model-rider
BIN2=./bin/a2-model-bike
BIN3=./bin/a2-model-track
BIN=./bin/a2-model-bike ./bin/a2-model-bike ./bin/a2-model-track
SRCS=./src/utils/*.cpp ./src/glad.c
INCLUDES=./src/utils/*.h
BINFOLDER=./bin

all: $(BIN)

$(BIN): $(SRCS) $(INCLUDES) $(BINFOLDER)
	g++ ./src/a2-model-bike.cpp $(SRCS) $(CPPFLAGS) $(LDFLAGS) $(LIBS) -o $(BIN1)
	g++ ./src/a2-model-rider.cpp $(SRCS) $(CPPFLAGS) $(LDFLAGS) $(LIBS) -o $(BIN2)
	g++ ./src/a2-model-track.cpp $(SRCS) $(CPPFLAGS) $(LDFLAGS) $(LIBS) -o $(BIN3)
	
$(BINFOLDER):
	mkdir $@

clean:
	rm -r $(BINFOLDER)
