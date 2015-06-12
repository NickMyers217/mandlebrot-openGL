#ifndef SCREEN_H
#define SCREEN_H

#include <SDL2/SDL.h>

struct Screen
{
	SDL_Window * window;
	SDL_GLContext context;
};


Screen * createScreen(int width, int height);
void destroyScreen(Screen * s);


Screen * createScreen(int width, int height)
{
	Screen * s = NULL;
	s = new Screen();
	s->window = SDL_CreateWindow("NickEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	s->context = SDL_GL_CreateContext(s->window);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	if(s == NULL) printf("Error creating screen.");
	return s;
}


void destroyScreen(Screen * s)
{
	SDL_GL_DeleteContext(s->context);
	SDL_DestroyWindow(s->window);
	delete s;
}

#endif // SCREEN_H
