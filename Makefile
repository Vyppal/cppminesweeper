LD_DEBUG=all make

all:
	g++ -I sdl2/include -L sdl2/lib -o main src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -I include
