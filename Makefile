OBJ := defaults.o error.o header.o request.o response.o server.o
CC := gcc
CFLAGS := -lws2_32 -g

EXECUTABLE := server

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXECUTABLE) -lws2_32