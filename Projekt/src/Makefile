OBJS=Event.o GUI.o main.o libalgorithms.a

all: $(OBJS)
	gcc $(FLAGS) $^ -o ../visualizer

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

libalgorithms.a:
	cd algorithms; make FLAGS="$(FLAGS)"

clean:
	rm -f *.o *.a algorithms/*.o
