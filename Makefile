CC = gcc
CFLAGS = -Wall -g

build: test_sse test_nosse

test_sse: test_sse

test_nosse: test_nosse.o
	$(CC) $^ -lm -o $@

.PHONY: clean

clean:
	rm -rf test_sse test_nosse *.o
