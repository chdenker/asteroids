CC=g++
CFLAGS=-std=c++17 -pedantic -Wall -Wextra -O3
LDFLAGS=-lSDL2 -lSDL2_ttf

all: asteroids

asteroids:
	$(CC) $(CFLAGS) Main.cpp Input.cpp Utils.cpp game/Asteroid.cpp game/Player.cpp game/Rocket.cpp graphics/GModule.cpp graphics/Rendering.cpp graphics/Screen.cpp -o asteroids $(LDFLAGS)

clean:
	rm asteroids
