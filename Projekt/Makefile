FLAGS=-O2 -Wall -Wshadow -Woverflow -Wextra -Wstrict-overflow=5 -fPIC --std=c99 -lm -pthread `pkg-config --cflags gtk+-2.0 --libs gtk+-2.0`
DEBUG_FLAGS=-g -O0 -Wall -Wshadow -Woverflow -Wextra -Wstrict-overflow=5 -fPIC --std=c99 -lm -pthread `pkg-config --cflags gtk+-2.0 --libs gtk+-2.0`
all:
	cd src; FLAGS="$(FLAGS)" make

debug:
	cd src; FLAGS="$(DEBUG_FLAGS)" make

clean:
	rm -f src/*.o src/*.a src/algorithms/*.o visualizer
