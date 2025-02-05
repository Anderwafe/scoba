CC ?= gcc
CFLAGS += -Wall -Wextra -Wconversion-extra -Wchkp -pedantic -fpic
LDFLAGS = -shared 
OBJECTS = dynarr.o
BUILDDIR = ./
RESULT = scoba.so


all: $(RESULT)

$(RESULT): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $(BUILDDIR)$(RESULT)

$(OBJECTS): %.o: %.c %.h
	$(CC) $(CFLAGS) -c $< -o $(BUILDDIR)$@

clean:
	cd $(BUILDDIR)
	rm $(OBJECTS) $(RESULT)
	cd -
