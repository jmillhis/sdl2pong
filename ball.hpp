#ifndef BALL_HPP
#define BALL_HPP
#include "game.hpp"
#include <ctime>

#define BALL_V 10
#define BALL_W 10
#define BALL_H 10
#define RESET_TIME 2

class PongBall {
public:
    PongBall();
    ~PongBall();
    void getMovement(SDL_Rect& lPaddle, SDL_Rect& rPaddle);
    void applyMovement();
	void reset();
	int checkGoal();
	SDL_Rect& getPosition();
private:
    int x, y, vx, vy;
	time_t resetTime;
	bool lgoal, rgoal;
    SDL_Rect pos;
};
#endif
