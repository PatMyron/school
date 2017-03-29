#include "tank.h"
#include "../cpp/randgen.h"
#include "../CMUgraphicsLib/cmugraphics.h"
#include "../CMUgraphicsLib/auxil.h"
#include <math.h>
#include <cmath>
using namespace std;

tank::tank() : angle(45), velocity(25), x(100), y(100), COLORE(BLACK), LEFT(true) {
    RandGen r;
    double length = 25;
    double angleRadiansLeft;
    angleRadiansLeft = angle * cdPi / 180;
    xStart = x - 2;
    yStart = y - 14;
    xEnd = cos(angleRadiansLeft) * length + xStart;
    yEnd = -sin(angleRadiansLeft) * length + yStart;
}

tank::tank(window &w, color skycolor, color groundcolor, color tankcolor, bool isLeft) : angle(45), velocity(25), COLORE(tankcolor), LEFT(isLeft) {
    RandGen r;
    double length = 25;
    double angleRadiansLeft;
    double angleRadiansRight;
    if (isLeft) {
        angleRadiansLeft = angle * cdPi / 180;
        x = r.RandInt(30, w.GetWidth() / 3);
        y = 0;
        while (w.GetColor(x, y) == LIGHTBLUE) y++;
        //w.SetBrush(BLACK);
        //w.SetPen(BLACK);
        //w.DrawEllipse(x-27,y+3,x+27,y-17,FILLED);
        //w.DrawCircle(x-2,y-14,14,FILLED);
        //w.SetPen(BLACK,5);
        xStart = x - 2;
        yStart = y - 14;
        xEnd = cos(angleRadiansLeft) * length + xStart;
        yEnd = -sin(angleRadiansLeft) * length + yStart;
        //w.DrawLine(leftX,leftY,leftXend,leftYend);
    } else {
        angleRadiansRight = ((180 - angle) * cdPi / 180);
        x = r.RandInt(2 * w.GetWidth() / 3, w.GetWidth() - 30);
        y = 0;
        while (w.GetColor(x, y) == LIGHTBLUE) y++;
        //w.SetBrush(BLACK);
        //w.SetPen(BLACK);
        //w.DrawEllipse(x-27,y+3,x+27,y-17,FILLED);
        //w.DrawCircle(x+2,y-14,14,FILLED);
        //w.SetPen(BLACK,5);
        xStart = x + 2;
        yStart = y - 14;
        xEnd = cos(angleRadiansRight) * length + xStart;
        yEnd = -sin(angleRadiansRight) * length + yStart;
        //w.DrawLine(rightX,rightY,rightXend,rightYend);
    }

}

int tank::getAngle() {
    return angle;
}

int tank::getSpeed() {
    return velocity;
}

void tank::setAngle(int a) {
    double length = 25;
    double angleRadiansLeft;
    double angleRadiansRight;
    if (LEFT) {
        angleRadiansLeft = angle * cdPi / 180;
        xEnd = cos(angleRadiansLeft) * length + xStart;
        yEnd = -sin(angleRadiansLeft) * length + yStart;
    } else {
        angleRadiansRight = ((180 - angle) * cdPi / 180);
        xEnd = cos(angleRadiansRight) * length + xStart;
        yEnd = -sin(angleRadiansRight) * length + yStart;
    }
    angle = a;
}

void tank::setSpeed(int v) {
    velocity = v;
}

void tank::drawTank(window &w) {
    if (LEFT) {
        w.SetBrush(COLORE);
        w.SetPen(COLORE);
        w.DrawEllipse(x - 27, y + 3, x + 27, y - 17, FILLED);
        w.DrawCircle(x - 2, y - 14, 14, FILLED);
        w.SetPen(COLORE, 5);
        w.DrawLine(xStart, yStart, xEnd, yEnd);
    } else {
        w.SetBrush(COLORE);
        w.SetPen(COLORE);
        w.DrawEllipse(x - 27, y + 3, x + 27, y - 17, FILLED);
        w.DrawCircle(x + 2, y - 14, 14, FILLED);
        w.SetPen(COLORE, 5);
        w.DrawLine(xStart, yStart, xEnd, yEnd);
    }
}

int tank::getXstart() {
    return xStart;
}

int tank::getYstart() {
    return yStart;
}

int tank::getXend() {
    return xEnd;
}

int tank::getYend() {
    return yEnd;
}

color tank::getColor() {
    return COLORE;
}
