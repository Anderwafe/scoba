CC ?= gcc
CFLAGS += -Wall -Wextra -Wconversion-extra -Wchkp -pedantic -fpic
LDFLAGS = -shared 
OBJECTS = dynarr.o


all: scoba.so

scoba.so: $(OBJECTS)
	$(CC) $(LDFLAGS) %^ -o scoba.so

$(OBJECTS): %.o: %.c %.h
	$(CC) $(CFLAGS) -c %<
