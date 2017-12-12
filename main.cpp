#include <iostream>
#include "player.hpp"

Player p;
clock_t prevFire;

void upImg(int event, int x, int y, int flags, void* a)
{
	if(event == EVENT_MOUSEMOVE)
	{
		Point pLoc = p.getLocation();
		float angle = atan2(y - pLoc.y, x - pLoc.x);
		p.setAim(angle);
	}
	else if(event == EVENT_LBUTTONDOWN && timeSinceFire >= fireRate)
	{
		prevFire = clock();
		p.shoot();
		p.draw();
		p.updateProjectiles();
	}
}

int main()
{
	namedWindow("Game",CV_WINDOW_AUTOSIZE);
	imshow("Game",img);
	setMouseCallback("Game", upImg, NULL);
	prevFire = clock();
	while(p.keyInput(waitKey(1)))
	{
		timeSinceFire = (double)(clock() - prevFire)/CLOCKS_PER_SEC;
		p.draw();
		p.updateProjectiles();
		drawRechargeRect();
	}
	return 0;
}

