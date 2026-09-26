CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = pcspeaker
SOURCE = pcspeaker.c

.PHONY: all clean install

all: $(TARGET)

$(TARGET): $(SOURCE)
	$(CC) $(CFLAGS) $(SOURCE) -o $(TARGET)

clean:
	rm -f $(TARGET)

install: $(TARGET)
	install -m 755 $(TARGET) /usr/bin/$(TARGET)
