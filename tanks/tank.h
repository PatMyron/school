#ifndef TANK_H_
#define TANK_H_
using namespace std;
#include "../CMUgraphicsLib/CMUgraphics.h"

class tank {
public:
	tank(window&,color,color,color,bool);
	int getAngle();
	int getSpeed();
	void setAngle(int);
	void setSpeed(int);
	void drawTank(window& w);
	int getXstart();
	int getYstart();
	int getXend();
	int getYend();
	color getColor();
private:
	int angle;
	int velocity;
	int x;
	int y;
	int xStart;
	int yStart;
	int xEnd;
	int yEnd;
	color COLORE;
	bool LEFT;
};

#endif
