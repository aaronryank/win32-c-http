OBJ := src/defaults.o src/error.o src/header.o src/request.o src/response.o src/server.o
CC := gcc
CFLAGS := -lws2_32 -g

EXECUTABLE := server

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXECUTABLE) -lws2_32