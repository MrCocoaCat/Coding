all:producer
CC=g++
CPPFLAGS=-Wall -std=c++11 -g
LDFLAGS=-pthread
producer:producer.o
    $(CC) $(LDFLAGS) -o $@ $^
producer.o:producer.cpp
    $(CC) $(CPPFLAGS) -o $@ -c $^
clean:
    rm *.o
