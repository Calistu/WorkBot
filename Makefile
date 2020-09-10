CC=gcc -g
TARGET=WorkBot.c
RESULT=WorkBot
PKG_LIBS=`pkg-config --libs --cflags libxml-2.0 gtk+-3.0`
INCLUDES=-I include
CC_FLAGS=$(INCLUDES) $(PKG_LIBS)
OBJECTS=main.o

all: objects.o

main.o: src/main.c
	$(CC) src/main.c $(CC_FLAGS) -c

objects.o: $(OBJECTS)
	$(CC) $(OBJECTS) $(TARGET) -o $(RESULT) $(CC_FLAGS)

clear:
	rm *.o
