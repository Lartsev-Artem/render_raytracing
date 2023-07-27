#include <iostream>
#include "process_sdl.h"


Process_SDL::Process_SDL() : _window(nullptr), _renderer(nullptr), _screen(nullptr), _pixels(nullptr)
{
    SDL_SetMainReady(); //обрабатока main() вручную, ( SDL с макросом SDL_MAIN_HANDLED)
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS))
    {
        std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }
}
void Process_SDL::init(const Screen& screen)
{
    if (SDL_CreateWindowAndRenderer(screen._width, screen._height, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS, &_window, &_renderer))
    {
        std::cerr << "Failed to create window and renderer: " << SDL_GetError() << std::endl;
        exit(1);
    }

    SDL_SetWindowTitle(_window, _name_programm);
    SDL_SetRenderDrawColor(_renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);

    _screen = SDL_GetWindowSurface(_window);
    _pixels = SDL_CreateRGBSurfaceWithFormat(0, screen._width, screen._height, 8, SDL_PIXELFORMAT_RGB24);
    _pixels->pixels = (void*)screen.data();
}
void Process_SDL::update()
{
    SDL_BlitSurface(_pixels, NULL, _screen, NULL);
    SDL_UpdateWindowSurface(_window);
}
void Process_SDL::clear()
{
    SDL_FreeSurface(_screen);
    SDL_FreeSurface(_pixels);

    SDL_DestroyRenderer(_renderer);
    SDL_DestroyWindow(_window);
    SDL_Quit();
}

bool Process_SDL::exit_event(const SDL_Event& event)
{
    if (SDL_QUIT == event.type || (SDL_KEYDOWN == event.type && SDLK_ESCAPE == event.key.keysym.sym))
    {
        return true; // quit
    }
    return false;
}
bool Process_SDL::handle_event()
{
    SDL_Event event; 
    SDL_PollEvent(&event); // handle event
    return exit_event(event);    
}

bool Process_SDL::handle_event(Vec3i& update_pos)
{
    SDL_Event event; 
    SDL_PollEvent(&event); // handle event
        
    if (exit_event(event))
    {
        return true; // quit
    }

    if (event.type == SDL_KEYDOWN)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
            update_pos = { 0, 1, 0 };
            break;
        case SDLK_s:
            update_pos = { 0, -1, 0 };
            break;
        case SDLK_a:
            update_pos = { 0, 0, 1 };
            break;
        case SDLK_d:
            update_pos = { 0, 0, -1 };
            break;
        case SDLK_z:
            update_pos = { 1, 0, 0 };
            break;
        case SDLK_x:
            update_pos = { -1, 0, 0 };
            break;
        }
    }

    if (event.type == SDL_KEYUP)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
            break;
        case SDLK_DOWN:
            break;
        case SDLK_RIGHT:
            break;
        case SDLK_LEFT:
            break;
        }
    }

    return false;
}