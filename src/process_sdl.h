#ifndef PROCESS_SDL_H
#define PROCESS_SDL_H

#include "Scene.h"

#define SDL_MAIN_HANDLED
#include <SDL.h> 

class Process_SDL
{
	static inline constexpr const char* _name_programm = "SDL2 window";
private:
	SDL_Window* _window;
	SDL_Renderer* _renderer;

	SDL_Surface* _screen; //базовый экран
	SDL_Surface* _pixels; //rgb пиксели

public:
	Process_SDL();
	~Process_SDL() { clear(); }

	void init(const Screen& screen);
	bool handle_event(Vec3i& update_pos);
	bool handle_event();
	void update();		
private:
	void clear();
	bool exit_event(const SDL_Event& event);
};

#endif //PROCESS_SDL_H
