#include "tank.h"
#include "../cpp/randgen.h"
#include "../CMUgraphicsLib/cmugraphics.h"
#include "../CMUgraphicsLib/auxil.h"
#include <math.h>
#include <cmath>

using namespace std;

tank::tank(window &w, color skycolor, color groundcolor, color tankcolor, bool isLeft) : angle(45), velocity(25), COLORE(tankcolor), LEFT(isLeft) {
    RandGen r;
    double length = 25;
    double angleRadians;
    if (isLeft) {
        angleRadians = angle * cdPi / 180;
        x = r.RandInt(30, w.GetWidth() / 3);
        xStart = x - 2;
    } else {
        angleRadians = ((180 - angle) * cdPi / 180);
        x = r.RandInt(2 * w.GetWidth() / 3, w.GetWidth() - 30);
        xStart = x + 2;
    }
    y = 0;
    while (w.GetColor(x, y) == LIGHTBLUE) y++;
    yStart = y - 14;
    xEnd = cos(angleRadians) * length + xStart;
    yEnd = -sin(angleRadians) * length + yStart;
}

void tank::drawTank(window &w) {
    w.SetBrush(COLORE);
    w.SetPen(COLORE);
    w.DrawEllipse(x - 27, y + 3, x + 27, y - 17, FILLED);
    if (LEFT) {
        w.DrawCircle(x - 2, y - 14, 14, FILLED);
    } else {
        w.DrawCircle(x + 2, y - 14, 14, FILLED);
    }
    w.SetPen(COLORE, 5);
    w.DrawLine(xStart, yStart, xEnd, yEnd);
}

void tank::setAngle(int a) {
    double length = 25;
    double angleRadians;
    if (LEFT) {
        angleRadians = angle * cdPi / 180;
    } else {
        angleRadians = ((180 - angle) * cdPi / 180);
    }
    xEnd = cos(angleRadians) * length + xStart;
    yEnd = -sin(angleRadians) * length + yStart;
    angle = a;
}

void tank::setSpeed(int v) {
    velocity = v;
}

int tank::getAngle() {
    return angle;
}

int tank::getSpeed() {
    return velocity;
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