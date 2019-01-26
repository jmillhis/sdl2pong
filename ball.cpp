#include "ball.hpp" 
#include "game.hpp"
#include "collision.hpp"
#include <iostream>
#include <cmath>

PongBall::PongBall() {
    x = (SCREEN_W - BALL_W) / 2;
    y = (SCREEN_H - BALL_H) / 2;
    vx = -BALL_V;
    vy = 0;
    pos.x = x;
    pos.y = y;
    pos.w = BALL_W;
    pos.h = BALL_H;
	lgoal = false;
	rgoal = false;
	time(&resetTime);
}

PongBall::~PongBall() {
    // nothing to do
}

void PongBall::getMovement(SDL_Rect& lPaddle, SDL_Rect& rPaddle) {
	if (difftime(time(nullptr),resetTime) <= RESET_TIME) {
		return;
	}
	double lPaddleMidPt[2];
	double rPaddleMidPt[2];
	double ballMidPt[2];
	double moveVector[2];
	double moveAngle;
	if (checkCollision(lPaddle,pos)) {
		//vx = -vx;
		lPaddleMidPt[0] = lPaddle.x + (0.5*lPaddle.w);
		lPaddleMidPt[1] = lPaddle.y + (0.5*lPaddle.h);
		ballMidPt[0] = pos.x + (0.5*pos.w);
		ballMidPt[1] = pos.y + (0.5*pos.h);
		moveVector[0] = ballMidPt[0] - lPaddleMidPt[0];
		moveVector[1] = ballMidPt[1] - lPaddleMidPt[1];
		if (ballMidPt[0] < lPaddleMidPt[0]) {
			// if ball behind paddle, do nothing. 
			// allows for better function.
		}
		else if (moveVector[0] < 0) {
			moveAngle = -atan(moveVector[1] / moveVector[0]);
		}
		else {
			moveAngle = atan(moveVector[1] / moveVector[0]);
		}
		vy = BALL_V * sin(moveAngle);
		vx = BALL_V * cos(moveAngle);
	}
	if (checkCollision(rPaddle,pos)) {
		//vx = -vx;
		rPaddleMidPt[0] = rPaddle.x + (0.5*rPaddle.w);
		rPaddleMidPt[1] = rPaddle.y + (0.5*rPaddle.h);
		ballMidPt[0] = pos.x + (0.5*pos.w);
		ballMidPt[1] = pos.y + (0.5*pos.h);
		moveVector[0] = ballMidPt[0] - rPaddleMidPt[0];
		moveVector[1] = ballMidPt[1] - rPaddleMidPt[1];
		if (ballMidPt[0] > rPaddleMidPt[0]) {}
		else if (moveVector[0] < 0) {
			moveAngle = -atan(moveVector[1] / moveVector[0]);
		}
		else {
			moveAngle = atan(moveVector[1] / moveVector[0]);
		}
		vy = BALL_V * sin(moveAngle);
		vx = -BALL_V * cos(moveAngle);// add minus sign as it seems to get lost along the way.
	}
}

void PongBall::applyMovement() {
	if (difftime(time(nullptr),resetTime) <= RESET_TIME) {
		return;
	}
	x += vx; 
	if (x < 0) {
		lgoal = true;
	}
	else if ((x + BALL_W) > SCREEN_W) {
		rgoal = true;
	}
	y += vy;
	if (y < 0 || (y + BALL_H) > SCREEN_H) {
		y -= vy;
		vy = -vy;
	}
	//std::cout << "Ball at (" << x << "," << y << ")\n";
}

int PongBall::checkGoal() {
	if (rgoal) {
		// right goal means player 1 scored.
		return 1;
	}
	else if (lgoal) {
		// left goal means player 2 scored.
		return 2;
	}
	else {
		return 0;
	}
}

void PongBall::reset() {
    x = (SCREEN_W - BALL_W) / 2;
    y = (SCREEN_H - BALL_H) / 2;
	if (lgoal) {vx = -BALL_V;}
	else if (rgoal) {vx = BALL_V;}
    vy = 0;
    pos.x = x;
    pos.y = y;
	lgoal = false;
	rgoal = false;
	time(&resetTime);
}

SDL_Rect& PongBall::getPosition() {
	pos.x = x;
	pos.y = y;
	return pos;
}
