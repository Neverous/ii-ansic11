OBJS=mergesort.o quicksort.o insertionsort.o selectionsort.o bubblesort.o\
	 shellsort.o radixsort.o stoogesort.o oddevensort.o heapsort.o algorithms.o

all: $(OBJS)
	ar rcs ../libalgorithms.a $(OBJS)

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -f *.o
