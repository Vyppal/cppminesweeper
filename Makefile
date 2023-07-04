LD_DEBUG=all make
all:
	g++ -I src/sdl2/include -L src/sdl2/lib -o main src/main.cpp -lmingw32 -lSDL2main -lSDL2
