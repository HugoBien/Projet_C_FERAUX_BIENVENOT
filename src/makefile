OBJS	= main.o
SOURCE	= main.cpp
HEADER	= player.h carte.h pile.h
OUT	= jeu.out
CC	 = g++
LIBS = -L./SDL2_ttf/.libs L./SDL2_image/.libs
LDFLAGS = `sdl2-config --cflags --libs`
INCLUDES = -I./SDL2_ttf -I./SDL2_image
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS)

main.o: main.cpp
	$(CC) $(FLAGS) main.cpp -lcppunit


clean:
	rm -f $(OBJS) $(OUT)
