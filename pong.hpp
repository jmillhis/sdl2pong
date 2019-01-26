#ifndef PONG_HPP
#define PONG_HPP

#include "game.hpp"
#include "paddle.hpp"
#include "ball.hpp"
#include <string>

#define SCORE_W 100
#define SCORE_H 50
#define WIN_SCORE 11

class SDLPong : public SDLGame {
public:
	// using same ctor/dtor
	SDLPong();
	~SDLPong();

	void drawCourt();
	void drawBall();
	void drawPaddles(); 
	void drawScore();
	bool getBallTexture(const char* path);
	void getBallMovement();
	void getPaddleMovement(SDL_Event& e);
	void applyBallMovement();
	void applyPaddleMovement();
	void updateScore(int print = 0);
	bool checkWin();
	void endGame();

private:
	PongPaddle p1;
	PongPaddle p2;
	PongBall b1;

	SDL_Texture* ballTexture;

	TTF_Font* helvetica;
	SDL_Color textColor;
	SDL_Rect theScore;
	

	int score1;
	int score2;
};

#endif
