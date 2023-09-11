#ifndef GMODULE_H
#define GMODULE_H

#include <SDL2/SDL.h>

class GModule {
public:
    GModule(int width, int height);
    ~GModule();

    void clear(int red, int green, int blue);
    void render_line(int x1, int y1, int x2, int y2, int red, int green, int blue);
    void render_rectangle(int x, int y, int width, int height, int red, int green, int blue);
    void draw();

private:
    SDL_Window* window;
    SDL_Renderer* renderer;
};

#endif