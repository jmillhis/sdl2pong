// main.cpp
#include "game.hpp"
#include "pong.hpp"
#include <iostream>

int main(int argc, char** argv) {
	// Create SDL Session
	SDLPong Pong;
	if (!Pong.beginSDL_all()) { return 1; }
	Pong.debug();

	bool quit = false;
	SDL_Event e;

	Pong.getBallTexture((char*)"media/png/ball.png");
	while(!quit) {
		// Events
		while(SDL_PollEvent(&e) != 0) {
			quit = Pong.checkQuit(e);
			Pong.getPaddleMovement(e);
		}
		Pong.applyPaddleMovement();

		Pong.getBallMovement();
		Pong.applyBallMovement();

		Pong.drawCourt();
		Pong.drawPaddles();
		Pong.drawBall();

		if (!Pong.checkWin()) { // dumb programming
			Pong.drawScore();
			Pong.updateScore();
		}
		else if (Pong.checkWin()) {
			Pong.endGame();
			quit = true;	
		}
		Pong.presentRenderer();
		if(Pong.checkWin()) {
			SDL_Delay(2000);
		}

	}
	return 0;
}
