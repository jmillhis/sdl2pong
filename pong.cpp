#include "pong.hpp"
#include <iostream>
#include <stdlib.h>
#include <string>

SDLPong::SDLPong() {
	p1.setP1(); // create p1 and p2 paddles
	p2.setP2();
	score1 = 0;
	score2 = 0;
	theScore.x = (SCREEN_W / 2) - (SCORE_W / 2);
	theScore.y = SCORE_H / 2;
	theScore.w = SCORE_W;
	theScore.h = SCORE_H;
	textColor = {255,255,255};
	ballTexture = nullptr;
	helvetica = nullptr;
}

SDLPong::~SDLPong() {
	// else done by major class
}

void SDLPong::drawCourt() {
	SDL_SetRenderDrawColor(gameRenderer, 30, 30, 30, 255);
	SDL_RenderClear(gameRenderer);
	SDL_SetRenderDrawColor(gameRenderer, 200, 200, 200, 255);
	SDL_RenderDrawLine(gameRenderer, SCREEN_W/2, 0, SCREEN_W/2, SCREEN_H);
	return;
}

void SDLPong::drawPaddles() {
	SDL_SetRenderDrawColor(gameRenderer, 220, 220, 220, 255); // draw as white
	SDL_RenderFillRect(gameRenderer, &p1.getPosition());
	SDL_RenderFillRect(gameRenderer, &p2.getPosition());
	SDL_RenderDrawRect(gameRenderer, &p1.getPosition());
	SDL_RenderDrawRect(gameRenderer, &p2.getPosition());
	return;
}

void SDLPong::drawBall() {
	SDL_RenderCopy(gameRenderer, ballTexture, NULL, &b1.getPosition());
	return;
}

void SDLPong::drawScore() {
	static bool font_open = false;
	std::string scoreString = std::to_string(score1) + "\t\t\t\t" + std::to_string(score2);
	if(!font_open) {//bad programming
		helvetica = TTF_OpenFont("Helvetica.ttf",120);
		font_open = true;
	}
	if (helvetica == nullptr) {
		std::cerr << ERROR_PROMPT << "Could not open Helvetica.ttf TTF_ERROR: " << TTF_GetError() << std::endl;
	}
	SDL_Surface* theMessage =  TTF_RenderText_Solid(helvetica, scoreString.c_str(), textColor);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(gameRenderer,theMessage);
	SDL_FreeSurface(theMessage);
	SDL_RenderCopy(gameRenderer, Message, NULL, &theScore);
	return;
}

bool SDLPong::getBallTexture(const char* path) {
    SDL_Surface* temp = IMG_Load(path);
    if (!temp) {
        std::cerr << ERROR_PROMPT << " IMG_Load: Failed to load surface." << IMG_GetError() << std::endl;
		SDL_FreeSurface(temp);
		return false;
    }
    else {
        ballTexture = SDL_CreateTextureFromSurface(gameRenderer, temp);
		SDL_FreeSurface(temp);
		return true;
    }

}

void SDLPong::updateScore(int print) {
	int flag = b1.checkGoal();
	if (flag == 1) {
		score1++;
		b1.reset();
		//p1.reset();
		//p2.reset();
	}
	if (flag == 2) {
		score2++;
		b1.reset();
		//p1.reset();
		//p2.reset();
	}
	if (print == 1) {
		std::cout << CLEAR;
		std::cout << CRED << "P1:\t" << CEND << score1 << std::endl;
		std::cout << CBLUE << "P2:\t" << CEND << score2 << std::endl;
	}
}

bool SDLPong::checkWin() {
	if (score1 >= WIN_SCORE) {
		return 1;
	}
	else if (score2 >= WIN_SCORE) {
		return 1;
	}
	else
		return 0;

}

void SDLPong::endGame() {
	if (score1 > score2) {
		std::string winString = "P1 Wins!";
		SDL_Surface* theMessage =  TTF_RenderText_Solid(helvetica, winString.c_str(), textColor);
		SDL_Texture* Message = SDL_CreateTextureFromSurface(gameRenderer,theMessage);
		SDL_FreeSurface(theMessage);
		SDL_RenderCopy(gameRenderer, Message, NULL, &theScore);
	}
	else if (score2 > score1){
		std::string winString = "P2 Wins!";
		SDL_Surface* theMessage =  TTF_RenderText_Solid(helvetica, winString.c_str(), textColor);
		SDL_Texture* Message = SDL_CreateTextureFromSurface(gameRenderer,theMessage);
		SDL_FreeSurface(theMessage);
		SDL_RenderCopy(gameRenderer, Message, NULL, &theScore);
	}
	return;
}

void SDLPong::getBallMovement() {
	b1.getMovement(p1.getPosition(),p2.getPosition());
	return;
}

void SDLPong::getPaddleMovement(SDL_Event& e) {
	p1.getMovement(e);
	p2.getMovement(e);
	return;
}

void SDLPong::applyPaddleMovement() {
	p1.applyMovement();
	p2.applyMovement();
	return;
}

void SDLPong::applyBallMovement() {
	b1.applyMovement();
	return;
}
