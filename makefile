LDIR=./lib
CC=gcc
CFLAGS= 
LDFLAGS= -Llib -lcrypto -lciphers -linfodef -lrandombytes -lm
TARGET= server client color
SOURCE= graph_coloring.c
OBJECT=$(SOURCE:.c=.o)

.PHONY: all clean $(TARGET)

default: $(TARGET) clean
all: default

$(SOURCE):
	$(CC) $(CFLAGS) -c $@
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): %: %.o $(OBJECT)
	$(CC) $< $(OBJECT)  $(LDFLAGS) -o $@

clean:
	-rm -f *.o
