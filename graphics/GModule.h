#ifndef GMODULE_H
#define GMODULE_H

#include <SDL2/SDL.h>

class GModule {
public:
    GModule(int width, int height);
    ~GModule();

    void clear(int red, int green, int blue);
    void render_rectangle(int x, int y, int width, int height, int red, int green, int blue);
    void render_triangle();
    void draw();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif