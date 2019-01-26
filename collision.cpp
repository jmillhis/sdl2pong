#include "collision.hpp"

bool checkCollision(SDL_Rect& a, SDL_Rect& b) {
	/* t = top
	 * b = bottom
	 * l = left 
	 * r = right
	 * */
	int la, lb, ra, rb, ta, tb, ba, bb;
	// get a
	la = a.x;
	ra = la + a.w;
	ta = a.y;
	ba = ta + a.h;
	// get b
	lb = b.x;
	rb = lb + b.w;
	tb = b.y;
	bb = tb + b.h;

	// collision condtions are not met
	if(ba <= tb)
		return false;
	if(ta >= bb)
		return false;
	if(ra <= lb)
		return false;
	if(la >= rb)
		return false;
	
	// true if above condtions don't exit
	return true;
}
