#include <iostream>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <GL/glew.h>
#include "screen.h"
#include "shader.h"


const int WIDTH = 1920;
const int HEIGHT = 1080;
const int FPS = 30;
enum State { RUNNING, EXIT };
Screen * screen = NULL;
ShaderProgram * p = NULL;
int maxIterations = 100;
float scale = 2.0f;
float xOff = 0.0f;
float yOff = 0.0f;


void run();
bool events();
void render();


int main()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	screen = createScreen(1920, 1080);
	if(glewInit() != GLEW_OK)
		std::cerr << "Glew did not initialize." << std::endl;

	p = createShaderProgram("./res/shaders/simple_vert.glsl", "./res/shaders/mandlebrot.glsl");
	useProgram(p);
	setUniform1f(p->pid, "screenWidth", (float)WIDTH);
	setUniform1f(p->pid, "screenHeight", (float)HEIGHT);
	setUniform1i(p->pid, "maxIteration", maxIterations);
	setUniform1f(p->pid, "scale", scale);
	setUniform1f(p->pid, "xOff", xOff);
	setUniform1f(p->pid, "yOff", yOff);

	run();

	destroyShaderProgram(p);
	destroyScreen(screen);
	SDL_Quit();

	return 0;
}


void run()
{
	double frameStart, frameEnd, frameTime;
	State state = RUNNING;
	while(state != EXIT)
	{
		frameStart = (double) SDL_GetTicks();

		if(!events()) state = EXIT;
		render();

		frameEnd = (double) SDL_GetTicks();
		frameTime = frameEnd - frameStart;
		if(frameTime < 1000.0 / FPS)
		{
			double delayTime = 1000.0 / FPS - frameTime;
			SDL_Delay((Uint32) delayTime);
		}
		std::cout << "FPS: " <<  1000.0 / ((double) SDL_GetTicks() - frameStart) << std::endl;
	}
}


bool events()
{
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		switch(e.type)
		{
			case SDL_QUIT:
				return false;
			case SDL_KEYDOWN:
				switch(e.key.keysym.sym)
				{
					case SDLK_a:
						xOff -= 1;
						setUniform1f(p->pid, "xOff", xOff);
						break;
					case SDLK_d:
						xOff += 1;
						setUniform1f(p->pid, "xOff", xOff);
						break;
					case SDLK_w:
						yOff += 1;
						setUniform1f(p->pid, "yOff", yOff);
						break;
					case SDLK_s:
						yOff -= 1;
						setUniform1f(p->pid, "yOff", yOff);
						break;
					case SDLK_UP:
						scale -= 0.1f;
						setUniform1f(p->pid, "scale", scale);
						break;
					case SDLK_DOWN:
						scale += 0.1f;
						setUniform1f(p->pid, "scale", scale);
						break;
				}
		}
	}

	return true;
}


void render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);
	glVertex2f(-1.0f, -1.0f);
	glVertex2f(-1.0f,  1.0f);
	glVertex2f( 1.0f,  1.0f);
	glVertex2f( 1.0f, -1.0f);
	glEnd();
		
	SDL_GL_SwapWindow(screen->window);
}
