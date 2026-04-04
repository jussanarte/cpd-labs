CC = gcc
CFLAGS = -Wall -g

TARGET = cpd-terminal

all: $(TARGET)

$(TARGET): main.o commandlinereader.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o commandlinereader.o

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

commandlinereader.o: commandlinereader.c
	$(CC) $(CFLAGS) -c commandlinereader.c

clean:
	rm -f *.o $(TARGET)