Heap: main.o Heap.o Node.o
	g++ -g main.o Heap.o Node.o -o Heap

main.o: main.cpp Heap.h Node.h
	g++ -c -g main.cpp

Heap.o: Heap.h Heap.cpp Node.h
	g++ -c -g Heap.cpp

Node.o: Node.h Node.cpp
	g++ -c -g Node.cpp

clean:
	rm *.o
	rm Heap

debug: Heap
	gdb Heap

valgrind: Heap
	valgrind --leak-check=full ./Heap

run: Heap
	./Heap
