//Pat Myron
#include <iostream> // Not required - but lets me print to and read from the console
#include "../cpp/apvector.h"
#include "../cpp/apstring.h"
#include "../cpp/randgen.h"
#include <math.h> 
#include <cmath>
#include "tank.h"
using namespace std; // Because of iostream
#include "../CMUgraphicsLib/cmugraphics.h"		// This will include all of the CMUGraphics Library
#include "../CMUgraphicsLib/auxil.h"
apvector<int> drawLandscape(window&,color,color);
//void placeTanks(window&,color,int);
bool getInput(window&,int&,int&,color,color,color,tank&,tank&,bool&);
//void moveCannon(window&,int&,int&,color,color,color);
color bullet(window&,int&,int&,color,color,color,tank&,tank&,bool&);
void main() 
{ 
	color whatIsHit=color(7,7,7);
	bool leftTurn=true;
	int angle=45;
	int velocity=25;
	color skycolor=LIGHTBLUE;
	color groundcolor=WHITE;
	color tankcolor1=color(5,5,5);
	color tankcolor2=color(40,40,40);
	window w(1250,900);
	w.SetBuffering(true);
	drawLandscape(w,skycolor,groundcolor);
	tank left(w,skycolor,groundcolor,tankcolor1,1);
	tank right(w,skycolor,groundcolor,tankcolor2,0);
	left.drawTank(w);
	right.drawTank(w);
	w.UpdateBuffer();
	//placeTanks(w,skycolor,angle);
	//w.UpdateBuffer();
	cout<<tankcolor1.ucBlue<<endl; //clubs
	cout<<tankcolor1.ucGreen<<endl;
	cout<<tankcolor1.ucRed<<endl;
	cout<<tankcolor2.ucBlue<<endl; //left parentheses
	cout<<tankcolor2.ucGreen<<endl;
	cout<<tankcolor2.ucRed<<endl;
	//moveCannon(w,angle,velocity,skycolor,groundcolor,tankcolor);
	while(whatIsHit!=left.getColor() && whatIsHit!=right.getColor())
	{
		getInput(w,angle,velocity,skycolor,groundcolor,tankcolor1,left,right,leftTurn);
		whatIsHit=bullet(w,angle,velocity,skycolor,groundcolor,tankcolor1,left,right,leftTurn);
		cout<<"fuy"<<endl;
		cout<<whatIsHit.ucBlue<<endl;
		cout<<whatIsHit.ucGreen<<endl;
		cout<<whatIsHit.ucRed<<endl;
	}

	w.SetBrush(skycolor);
	w.SetPen(skycolor);	//erasing up top
	w.DrawRectangle(0,0,w.GetWidth(),200,FILLED);

	w.SetFont(50,PLAIN,ROMAN);
	w.SetBrush(BLACK);
	w.SetPen(BLACK);
	
	

	if (whatIsHit==left.getColor())
	{

		w.DrawString(w.GetWidth()/2-75,w.GetHeight()/2-66,"player 2 wins!");
	}
	else
	{
		w.DrawString(w.GetWidth()/2-75,w.GetHeight()/2-66,"player 1 wins!");
	}
	w.UpdateBuffer();
} 
apvector<int> drawLandscape(window& w,color skycolor,color groundcolor)
{
	w.SetBrush(skycolor);
	w.SetPen(skycolor);
	w.DrawRectangle(0,0,w.GetWidth(),w.GetHeight(),FILLED);
	RandGen r;
	apvector<int> heights(w.GetWidth());
	int ystart; 
	ystart=r.RandInt((double)w.GetHeight()*0.666,(double)w.GetHeight()*0.75);
	w.SetBrush(groundcolor);
	w.SetPen(groundcolor);
	for (double x=0;x<w.GetWidth();x++)
	{
		int yval=ystart+sin((double)(x/60))*15;
		w.DrawLine(x,yval,x,w.GetHeight());
		heights[x]=yval;
	}
	return heights;
}

/*void placeTanks(window& w,color skycolor,int angle)
{
	double length=25;
	double angleRadiansLeft;
    double angleRadiansRight;
    angleRadiansLeft=angle*cdPi/180;
	angleRadiansRight=((180-angle)*cdPi/180);
	
	//left tank
	RandGen r;
	int x=r.RandInt(30,w.GetWidth()/3);
	int y=0;
	while(w.GetColor(x,y)==LIGHTBLUE) y++;
	w.SetBrush(BLACK);
	w.SetPen(BLACK);	
	w.DrawEllipse(x-27,y+3,x+27,y-17,FILLED);
	w.DrawCircle(x-2,y-14,14,FILLED);
	w.SetPen(BLACK,5);

	//w.DrawLine(x-2,y-14,x+20,y-25);
	leftX=x-2;
	leftY=y-14;
	leftXend=cos(angleRadiansLeft)*length+leftX;
	leftYend=-sin(angleRadiansLeft)*length+leftY;
	w.DrawLine(leftX,leftY,leftXend,leftYend);


	//RIGHT TANK


	x=r.RandInt(2*w.GetWidth()/3,w.GetWidth()-30);
	y=0;
	while(w.GetColor(x,y)==LIGHTBLUE) y++;
	w.SetBrush(BLACK);
	w.SetPen(BLACK);	
	w.DrawEllipse(x-27,y+3,x+27,y-17,FILLED);
	w.DrawCircle(x+2,y-14,14,FILLED);
	w.SetPen(BLACK,5);
	rightX=x+2;
	rightY=y-14;
	rightXend=cos(angleRadiansRight)*length+rightX;
	rightYend=-sin(angleRadiansRight)*length+rightY;
	w.DrawLine(rightX,rightY,rightXend,rightYend);
	//w.DrawLine(x+2,y-14,x-20,y-25);

} */   
bool getInput(window& w,int& angle,int& velocity,color skycolor,color groundcolor,color tankcolor,tank& left,tank& right,bool& leftTurn)
{
	char k='#';  // for key, set to a known, but useless value
	angle = 45;   // some starting for the angle value (or these two are passed in from previous shot)
	velocity = 25;  // some starting value for the velocity
	w.SetFont(50,PLAIN,ROMAN);
	w.SetPen(BLACK);
	w.SetBrush(BLACK);
	while(k!=13)  // that's the return key
	{
		w.SetFont(50,PLAIN,ROMAN);
		w.SetBrush(BLACK);
		w.SetPen(BLACK);
		w.DrawString(w.GetWidth()/2-60,100,"angle:");
		w.DrawInteger(w.GetWidth()/2+60,100,angle);
		w.DrawString(w.GetWidth()/2-60,150,"speed:");
		w.DrawInteger(w.GetWidth()/2+60,150,velocity);

		w.UpdateBuffer();
		w.SetBrush(skycolor);
		w.SetPen(skycolor);	//erasing up top
		w.DrawRectangle(0,0,w.GetWidth(),200,FILLED);
		//redraw tank
		
		if(leftTurn) w.DrawRectangle(left.getXstart()-3,left.getYstart()+3,left.getXend()+3,left.getYend()-3,FILLED);
		else w.DrawRectangle(right.getXstart()+3,right.getYstart()+3,right.getXend()-3,right.getYend()-3,FILLED);
		w.SetBrush(BLACK);
		w.SetPen(BLACK);	
		w.DrawEllipse(left.getXstart()+2-27,left.getYstart()+14+3,left.getXstart()+2+27,left.getYstart()+14-17,FILLED);
		w.DrawCircle(left.getXstart()+2-2,left.getYstart()+14-14,14,FILLED);

		w.WaitKeyPress(k);
		 if(k==8) angle++;
	     if(k==2) angle--;
		 if(k==6) velocity++;
	     if(k==4) velocity--;
		
		 if(angle<1) angle=1;
		 if(angle>90) angle=90;
		 if (velocity<1) velocity=1;
		 if (velocity>35) velocity=35;
		 if (leftTurn)
		 {
			 left.setAngle(angle);
			 left.drawTank(w); 
		 }
		 else
		 {
			 right.setAngle(angle);
			 right.drawTank(w);
		 }
		//moveCannon(w,angle,velocity,skycolor,groundcolor,tankcolor);
	}
		
	if(k==13) return true;
}
 /*
void moveCannon(window& w,int& angle,int& velocity,color skycolor,color groundcolor,color tankcolor)
{
	w.SetBrush(tankcolor);
	w.SetPen(tankcolor,5);
    double length=25;
	double angleRadiansLeft;
    double angleRadiansRight;
    angleRadiansRight=((180-angle)*cdPi/180);
	angleRadiansLeft=angle*cdPi/180;
	leftXend=cos(angleRadiansLeft)*length+leftX;
	leftYend=-sin(angleRadiansLeft)*length+leftY;
	
	w.DrawLine(leftX,leftY,leftXend,leftYend);
	w.UpdateBuffer();
	/*w.SetBrush(skycolor);
	w.SetPen(skycolor);
    w.DrawRectangle(leftX-3,leftY+3,leftXend+3,leftYend-3,FILLED);
	w.SetBrush(BLACK);
	w.SetPen(BLACK);	
	w.DrawEllipse(leftX+2-27,leftY+14+3,leftX+2+27,leftY+14-17,FILLED);
	w.DrawCircle(leftX+2-2,leftY+14-14,14,FILLED);
	
}*/

color bullet(window& w,int& angle,int& velocity,color skycolor,color groundcolor,color tankcolor,tank& left,tank& right,bool& leftTurn)
{
	int bulletX,bulletY;
	if (leftTurn)
	{
		double radianAngle=angle*cdPi/180;
		double xVel=cos(radianAngle)*velocity;
		double yVel=sin(radianAngle)*velocity;
		bulletX=left.getXend()+3;
		bulletY=left.getYend()-3;
		double time=0;
		while(w.GetColor(bulletX,bulletY)==skycolor)
		{
			w.SetBrush(BLACK);
			w.SetPen(BLACK);
			w.DrawCircle(bulletX,bulletY,2,FILLED);
			w.UpdateBuffer();
			w.SetBrush(skycolor);
			w.SetPen(skycolor);
			w.DrawCircle(bulletX,bulletY,2,FILLED);
			time+=0.007;
			bulletX+=xVel*time;
			bulletY+=-yVel*time+40*time*time;
		}
		leftTurn=false;
	}
	else
	{
		double radianAngle=((180-angle)*cdPi/180);
		double xVel=cos(radianAngle)*velocity;
		double yVel=sin(radianAngle)*velocity;
		bulletX=right.getXend()-3;
		bulletY=right.getYend()-3;
		double time=0;

		while(w.GetColor(bulletX,bulletY)==skycolor)
		{
			w.SetBrush(BLACK);
			w.SetPen(BLACK);
			w.DrawCircle(bulletX,bulletY,2,FILLED);
			w.UpdateBuffer();
			w.SetBrush(skycolor);
			w.SetPen(skycolor);
			w.DrawCircle(bulletX,bulletY,2,FILLED);
			time+=0.007;
			bulletX+=xVel*time;
			bulletY+=-yVel*time+40*time*time;
		}
		leftTurn=true;
	}
	angle=45;
	velocity=25;

	w.SetFont(50,PLAIN,ROMAN);
	w.SetBrush(BLACK);
	w.SetPen(BLACK);
	w.DrawString(w.GetWidth()/2-60,100,"angle:");
	w.DrawInteger(w.GetWidth()/2+60,100,angle);
	w.DrawString(w.GetWidth()/2-60,150,"speed:");
	w.DrawInteger(w.GetWidth()/2+60,150,velocity);
	w.UpdateBuffer();

	return w.GetColor(bulletX,bulletY);
}
