#ifndef TANK_H_
#define TANK_H_
using namespace std; // Because of iostream
#include <s:/cpp/apvector.h> 	 	
#include <s:/cpp/randgen.h>
#include <s:/Graphics Project Folder/CMUgraphicsLib\cmugraphics.h>		// This will include all of the CMUGraphics Library
#include <s:/Graphics Project Folder/CMUgraphicsLib\auxil.h>

class tank
{
public:
	tank();
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
