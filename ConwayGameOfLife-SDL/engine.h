#include <SDL.h>
#include <cstdlib>
#include <iostream>
#include <time.h>  
#include <vector>
#include <tuple>
#include <algorithm>

#pragma once 


class Engine {

    SDL_Window* window;
    SDL_Renderer* renderer;
    std::vector<SDL_FPoint> points;
    std::vector<SDL_Color> colors;
    SDL_Event event;
public:
    Engine(int h, int w)
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(w * 4, h * 4, SDL_WINDOW_ALLOW_HIGHDPI, &window, &renderer);
        SDL_RenderSetScale(renderer, 4, 4);
    }

    void drawpixel(double xm, double ym, uint8_t r = 255, uint8_t g = 255, uint8_t b = 255, uint8_t a = 255)
    {
        points.emplace_back(SDL_FPoint{ static_cast<float>(xm), static_cast<float>(ym) });
        colors.emplace_back(SDL_Color{ r, g, b, a });
    }
    void clearpixels()
    {
        points.clear();
        colors.clear();
    }

    void update()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        for (long unsigned int i = 0; i < points.size(); i++)
        {
            SDL_SetRenderDrawColor(renderer, colors[i].r, colors[i].g, colors[i].b, colors[i].a);
            SDL_RenderDrawPointF(renderer, points[i].x, points[i].y);
        }
        SDL_RenderPresent(renderer);
    }
    void input() {
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                SDL_Quit();
                std::exit(0);
                break;

            default:
                break;
            }
        }
    }

};
