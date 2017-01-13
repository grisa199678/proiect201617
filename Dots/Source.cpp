/*
#include <SDL.h>
#include <iostream>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#define WIDTH  300
#define HEIGHT  400
using namespace std;
struct dots {
	double r1;
	double r2;
	dots* next;
};
dots* prim;
void updatePlayArea(SDL_Renderer*renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 240, 255, 255);
	SDL_Rect PlayArea;
	PlayArea.x = 0;
	PlayArea.y = 100;
	PlayArea.w = WIDTH;
	PlayArea.h = HEIGHT;
	SDL_RenderFillRect(renderer, &PlayArea);
}
void createDot(SDL_Renderer *renderer, double x, double y) {
	filledCircleRGBA(renderer, x, y, 5, 0, 0, 0, 255);
}
int main(int argc, char* args[]) {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer;
	int Width = 400;
	int Height = 500;
	window = SDL_CreateWindow("Dots", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
	if (window == nullptr) {
		cout << "Creating windows failed." << endl << SDL_GetError() << endl;
	}
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
	updatePlayArea(renderer);

	bool running = true;
	while (running) {
		double r = 0; int pos = 0; int space = 0; float start, stop; float complexity = 0.5; bool key_pressed = false;
		double dot = 0; double x, y, z, m; int rr;
		while (running) {
			double r = 0;
			bool increase = true;
			float start, stop;
			do {
				updatePlayArea(renderer);
				aacircleRGBA(renderer, WIDTH / 2, HEIGHT / 2 + 50, r + 0.1, 0, 0, 0, 255);
				aacircleRGBA(renderer, WIDTH / 2, HEIGHT / 2 + 50, r, 0, 0, 0, 255);
				SDL_RenderPresent(renderer);
				r += (increase) ? complexity : -complexity;
				if (r >= 100) increase = false;
				if (r < 0) increase = true;
				SDL_Delay(10 - complexity);

				SDL_Event event;
				if (SDL_PollEvent(&event)) {
					if (event.type == SDL_QUIT) {
						running = false;
					}
					if (event.type == SDL_KEYDOWN && !key_pressed) {
						if (event.key.keysym.sym == SDLK_SPACE) {
							space = 5;
							if (complexity<0.7)complexity += 0.01;
							key_pressed = true;
						}

					}
					if (event.type == SDL_KEYUP) {
						key_pressed = false;
					}
				}
			} while (running);
		}
	}
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;

}*/