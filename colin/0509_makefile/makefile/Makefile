app:add.o div.o mul.o sub.o main.o 
	gcc add.o div.o mul.o sub.o main.o  -o app
add.o:add.c
	gcc -c add.c
div.o:div.c
	gcc -c div.c
mul.o:mul.c
	gcc -c mul.c
sub.o:sub.cpp
	g++ -c sub.cpp
main.o:main.c
	gcc -c main.c


.PHONY:clean
clean:
	rm *.o
