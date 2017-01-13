#include "MainGame.h"
#include <fstream>
#include <iostream>
#include <math.h>
#include <time.h> 
#include <string>
#include <stdlib.h>
using namespace std;
MainGame::MainGame()
{
	_best = 0;
	_score = 0;
	_complexity = 0;
	_dotsList = new MainGame::Dot;
	_dotsList->x = 0;
	_dotsList->y = 0;
	_dotsList->next = nullptr;
	_dotsListLast = _dotsList;
	_window = nullptr;
	_screenWidth = 300;
	_screenHeight = 400;
	_maxRadius = 100;
	_minRadius = 0;
	_circleRadius = _maxRadius;
	_increase = false;
	_gameState = GameState::PLAY;
	_circleX = _screenWidth / 2;
	_circleY = _screenHeight / 2 + 50;
	_dotAppear = 0;
	_keyPressed = 0;
	_key = false;
	//Circle moving Area
	_circleArea.x = 0;
	_circleArea.y = 100;
	_circleArea.w = _screenWidth;
	_circleArea.h = _screenHeight;
	//....
	//ScoreArea
	_scoreArea.x = 0;
	_scoreArea.y = 0;
	_scoreArea.h = 100;
	_scoreArea.w = _screenWidth;
	//.......
	//currentScore
	_currentScore.x = 15;
	_currentScore.y = 18;
	_currentScore.h = 40;
	_currentScore.w = 120;
	//bestArea
	_bestArea.x = 165;
	_bestArea.y = 18;
	_bestArea.h = 40;
	_bestArea.w = 120;
	//....
	_defaultColor  = {215, 220, 250, 255};
	_redColor = { 255, 0, 0, 255 };
	_blackColor = { 0, 0, 0, 255 };
	_whiteColor = { 255, 255, 255, 255 };

}
void MainGame::setCircleColor() {
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
}
void MainGame::updateCircleArea() {
	SDL_SetRenderDrawColor(_renderer, 215, 220, 250, 255);
	SDL_RenderFillRect(_renderer, &_circleArea);
}
void MainGame::updateScoreArea() {
	SDL_SetRenderDrawColor(_renderer, _defaultColor.r, _defaultColor.g, _defaultColor.b, _defaultColor.a);
	SDL_RenderFillRect(_renderer, &_scoreArea);
}
void MainGame::initSystem() {
	SDL_Init(SDL_INIT_EVERYTHING);
	_surface = SDL_CreateRGBSurface(0, _screenWidth, 100, 32, 0, 0, 0, 0);
	_window = SDL_CreateWindow("Dots", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);
	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
	SDL_SetRenderDrawColor(_renderer, 0, 0, 0, 255);
	SDL_UpdateWindowSurface(_window);
	SDL_RenderClear(_renderer);
	SDL_RenderPresent(_renderer); 
	srand(time(0));
}

void MainGame::processInput() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type)
		{
		case SDL_QUIT: 
			_gameState = GameState::EXIT;
			break;
		
		}
			if (event.type == SDL_KEYDOWN && _key==false) {
				if (event.key.keysym.sym == SDLK_SPACE) {
					_keyPressed = 1;
					_key = true;
					if (_gameState == GameState::TRYAGAIN) _gameState = GameState::PLAY; else {
						if (_complexity < 12) _complexity += 0.3;
						checkDots();
					}
				}
			}
			if (event.type == SDL_KEYUP && event.key.keysym.sym == SDLK_SPACE) _key = false;
				
	}
}
void MainGame::drawDots() {
	MainGame::Dot* prim;
	prim = _dotsList->next;
	while (prim != nullptr) {
		filledCircleRGBA(_renderer, prim->x, prim->y, 5, 0, 0, 0, 255);
		prim = prim->next;
	}
}
void MainGame::checkDots() {
	MainGame::Dot* prim;
	prim = _dotsList->next;
	int dots = 0;
	while (prim != nullptr) {
		if (abs(prim->r - _circleRadius-2) < 5) {
		filledCircleRGBA(_renderer, prim->x, prim->y, 5, _defaultColor.r, _defaultColor.g, _defaultColor.b, _defaultColor.a);
		prim->r = 0;
		prim->x = -10;
		prim->y = -10;
		cout << abs(prim->r - _circleRadius) << "-------" << _circleRadius << endl;
		dots++;
	}
		prim = prim->next;
	}
	_score = _score + dots;
	if (dots == 0) _gameState = GameState::TRYAGAIN;
}
int MainGame::random(int k) {
	return (rand() % k);
}
void MainGame::newDot() {
	if (_dotAppear == 0) {
		int x, y, r, k;
		r = random(9);
		if (r == 0) x = 0; else {
			x = random(r);
		}
		y = (int)sqrtf((r*r) - (x*x));
		k = random(10);
		x *= 12 * ((k >= 5) ? 1 : -1);
		k = random(10);
		y *= 12 * ((k >= 5) ? 1 : -1);
		MainGame::Dot* newD;
		newD = new MainGame::Dot;
		newD->r = r * 12;
		newD->x = _circleX + x;
		newD->y = _circleY + y;
		cout << newD->r << " " << newD->x << " " << newD->y << endl;
		newD->next = nullptr;
		_dotsListLast->next = newD;
		_dotsListLast = newD;
		_dotAppear = 200;
	}
	else _dotAppear--;
}
void MainGame::drawCircle() {
	if (_keyPressed > 0) {
		aacircleRGBA(_renderer, _circleX, _circleY, _circleRadius, 255, 255, 255, 255);
		_keyPressed--;
	} else aacircleRGBA(_renderer, _circleX, _circleY, _circleRadius, 0, 0, 0, 255);
	if (_increase) _circleRadius ++; else _circleRadius--;
	if (_circleRadius == _minRadius) _increase = true;
	if (_circleRadius == _maxRadius) _increase = false;
	SDL_Delay(20-_complexity);
}
void MainGame::updateWindow() {
	SDL_RenderPresent(_renderer);
}
void MainGame::updateCurrentScore() {
	TTF_Init();
	char score[10];
	for (int i = 0; i < 10; i++) score[i] = NULL;
	score[0] = 'S';score[1] = 'C';score[2] = 'O';score[3] = 'R';score[4] = 'E';
	score[5] = ':';  
	if (_score < 10) score[6] = _score + 48; else 
	if (_score < 100) {
		score[7] = _score % 10 + 48;
		score[6] = _score / 10 % 10 + 48;
	} else {
		int k = _score, m = 0;

		while (k > 0) {
			score[8 - m] = k % 10 + 48;
			m++;
			k = k / 10;
		}
		}
	TTF_Font *Sans = TTF_OpenFont("sans.ttf", 24);
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, score, _blackColor);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(_renderer, surfaceMessage);
	SDL_QueryTexture(Message, NULL, NULL, &_currentScore.w, &_currentScore.h);
	SDL_RenderCopy(_renderer, Message, NULL, &_currentScore);
	TTF_Quit();
}
void MainGame::tryAgain() {
	TTF_Init();
	TTF_Font *Sans = TTF_OpenFont("sans.ttf", 28);
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, "TRY AGAIN!", _blackColor);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(_renderer, surfaceMessage);
	SDL_Rect again;
	_score = 0;
	again.x = 80;
	again.y = 200;
	SDL_QueryTexture(Message, NULL, NULL, &again.w, &again.h);
	SDL_RenderCopy(_renderer, Message, NULL, &again);
	TTF_Quit();
	MainGame::Dot*prim;
	prim = _dotsList;
	prim->next->next = nullptr;
	_dotAppear = 0;
	_circleRadius = _maxRadius;
	_increase = false;
}
void MainGame::updateBestScore() {
	TTF_Init();
	ifstream fin("bestscore.ini");
	fin >> _best;
	fin.close();
	if (_score > _best) {
		ofstream fout;
		fout.open("bestscore.ini");
		_best = _score;
		fout << _score;
		fout.close();
	}
	char score[10];
	for (int i = 0; i < 10; i++) score[i] = NULL;
	score[0] = 'B';score[1] = 'E';score[2] = 'S';score[3] = 'T';score[4] = ':';
	if (_best < 10) score[5] = _best + 48; else
		if (_best < 100) {
			score[6] = _best % 10 + 48;
			score[5] = _best / 10 % 10 + 48;
		}
		else {
			int k = _best, m = 0;

			while (k > 0) {
				score[7 - m] = k % 10 + 48;
				m++;
				k = k / 10;
			}
		}
	TTF_Font *Sans = TTF_OpenFont("sans.ttf", 24);
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, score, _blackColor);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(_renderer, surfaceMessage);
	SDL_QueryTexture(Message, NULL, NULL, &_bestArea.w, &_bestArea.h);
	SDL_RenderCopy(_renderer, Message, NULL, &_bestArea);
	TTF_Quit();
}
//Magic Happens.......
void MainGame::run() {
	initSystem();
	while (_gameState !=GameState::EXIT) gameLoop();
	quitSystem();
}
void MainGame::quitSystem(){
	_window = nullptr;
	SDL_QUIT;
}
void MainGame::gameLoop() {
	while (_gameState == GameState::PLAY) {
		updateCircleArea();
		updateScoreArea();
		updateCurrentScore();
		updateBestScore();
		newDot();
		drawDots();
		drawCircle();
		processInput();
		updateWindow();
	}
	if (_gameState == GameState::TRYAGAIN) {
		updateCircleArea();
		tryAgain();
		processInput();
		updateWindow();
	}
}
