#ifndef PADDLE_HPP
#define PADDLE_HPP

#include "game.hpp"
#define PADDLE_W 20
#define PADDLE_H 70
#define PADDLE_V 12

class PongPaddle {
public:
	PongPaddle();
	~PongPaddle();
	void setP1();
	void setP2();
	void reset();
	void getMovement(SDL_Event& e);
	void applyMovement();
	SDL_Rect& getPosition();
private:
	int mode;
	/* 0 = cpu controlled
	 * 1 = player 1
	 * 2 = player 2
	 * else = no control
	 * */
	int x, y; // paddle position
	int v; // paddle velocity 
	SDL_Rect pos;
};

#endif
