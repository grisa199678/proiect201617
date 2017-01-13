#pragma once
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_ttf.h>
#include <math.h>
enum class GameState{PLAY,EXIT,TRYAGAIN};
class MainGame
{
public:
	MainGame();

	void run();
private:
	struct Dot {
		float x, y, r;
		Dot*next;
	};
	SDL_Window* _window;
	SDL_Renderer* _renderer;
	SDL_Surface* _surface;
	SDL_Rect _circleArea, _scoreArea, _bestArea, _currentScore;
	GameState _gameState;
	double _complexity;
	bool _key;
	int _keyPressed;
	int _dotAppear;
	int _score;
	int _best;
	int _circleRadius;
	int _screenWidth;
	int _screenHeight;
	int _maxRadius, _minRadius;
	int _circleX, _circleY;
	Dot* _dotsList;
	Dot* _dotsListLast;
	bool _increase;
	SDL_Color _defaultColor, _redColor, _blackColor, _whiteColor;



	void drawCircle();
	void initSystem();
	void quitSystem();
	void processInput();
	void gameLoop();
	void updateCircleArea();
	void updateWindow();
	void setCircleColor();
	void drawDots();
	void newDot();
	void updateScoreArea();
	void updateCurrentScore();
	void updateBestScore();
	void tryAgain();
	void checkDots();
	int random(int k);
};

