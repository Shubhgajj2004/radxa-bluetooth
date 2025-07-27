CC=gcc
CFLAGS=-I.
DEPS = bluetooth_host.h
LIBS = -lbluetooth

all: bluetooth_host

bluetooth_host: bluetooth_host.c
	$(CC) -o bluetooth_host bluetooth_host.c $(LIBS)

clean:
	rm -f bluetooth_host
