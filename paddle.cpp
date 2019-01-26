#include "paddle.hpp"

PongPaddle::PongPaddle() {
	mode = 0; // start as cpu
	x = 0;
	y = (SCREEN_H - PADDLE_H) / 2;
	v = 0; // no velocity
	pos.x = x;
	pos.y = y;
	pos.w = PADDLE_W;
	pos.h = PADDLE_H;
}

PongPaddle::~PongPaddle() {
	// nothing to do 
}

void PongPaddle::setP1() {
	x = SCREEN_W / 10;
	mode = 1;
}

void PongPaddle::setP2() {
	x = ((SCREEN_W * 9) / 10) - PADDLE_W;
	mode = 2;
}

void PongPaddle::reset() {
	if (mode == 1) {
		x = SCREEN_W / 10;
	}
	else {
		x = ((SCREEN_W * 9) / 10) - PADDLE_W;
	}
	y = (SCREEN_H - PADDLE_H) / 2;
	v = 0; // no velocity
	pos.x = x;
	pos.y = y;
}

void PongPaddle::getMovement(SDL_Event& e) {
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
		switch(e.key.keysym.sym) {
			case SDLK_q:
				if (mode == 1) v -= PADDLE_V;
				break;
			case SDLK_a:
				if (mode == 1) v += PADDLE_V;
				break;
			case SDLK_p:
				if (mode == 2) v -= PADDLE_V;
				break;
			case SDLK_l:
				if (mode == 2) v += PADDLE_V;
				break;
			default:
				break;
		}
	}
	if (e.type == SDL_KEYUP && e.key.repeat == 0) {
		switch(e.key.keysym.sym) {
			case SDLK_q:
				if (mode == 1) v += PADDLE_V;
				break;
			case SDLK_a:
				if (mode == 1) v -= PADDLE_V;
				break;
			case SDLK_p:
				if (mode == 2) v += PADDLE_V;
				break;
			case SDLK_l:
				if (mode == 2) v -= PADDLE_V;
				break;
			default:
				break;
		}
	}
}

void PongPaddle::applyMovement() {
	y += v;
	if((y < 0) || (y + PADDLE_H > SCREEN_H)) { // undo if exiting screen
		y -= v;
	}
	return;
}

SDL_Rect& PongPaddle::getPosition() {
	pos.x = x;
	pos.y = y;
	return pos;
}
