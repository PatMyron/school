#include <iostream>
#include "../cpp/apvector.h"
#include "../cpp/apstring.h"
#include "../cpp/randgen.h"
#include <math.h> 
#include <cmath>
#include "tank.h"
#include "../CMUgraphicsLib/cmugraphics.h"
#include "../CMUgraphicsLib/auxil.h"

using namespace std;

apvector<int> drawLandscape(window &, color skycolor, color groundcolor); // creates landscape. returns height of ground at every x-value. only called once
bool getInput(window &, color skycolor, tank &left, tank &right, bool &leftTurn); // gets input for 2 parameters. returns true when enter key (shoot) is pressed
color bullet(window &, color skycolor, tank &left, tank &right, bool &leftTurn); // goes through bullets path. returns color of what is hit.

void setBrushAndPenColor(window &w, color brushAndPenColor) {
    w.SetBrush(brushAndPenColor);
    w.SetPen(brushAndPenColor);
}

void main() {
    color whatIsHit = color(7, 7, 7); // set to a known, but useless value
    bool leftTurn = true;
    color skycolor = LIGHTBLUE;
    color groundcolor = WHITE;
    // tanks must be different colors!
    color tankcolor1 = color(5, 5, 5); // clubs
    color tankcolor2 = color(40, 40, 40); // left parentheses
    window w(1250, 900);
    w.SetBuffering(true);
    drawLandscape(w, skycolor, groundcolor); // only called once. can return array of ground heights[]
    tank left(w, skycolor, groundcolor, tankcolor1, 1);  // angle initialized to 45
    tank right(w, skycolor, groundcolor, tankcolor2, 0); // speed initialized to 25
    left.drawTank(w);
    right.drawTank(w);
    w.UpdateBuffer();

    while (whatIsHit != left.getColor() && whatIsHit != right.getColor()) { // until a tank is hit
        getInput(w, skycolor, left, right, leftTurn);
        whatIsHit = bullet(w, skycolor, left, right, leftTurn);
    }

    // clearing angle/power info
    setBrushAndPenColor(w, skycolor);
    w.DrawRectangle(0, 0, w.GetWidth(), 200, FILLED);
    w.SetFont(50, PLAIN, ROMAN);

    setBrushAndPenColor(w, BLACK);
    // drawing winner message
    if (whatIsHit == left.getColor()) {
        w.DrawString(w.GetWidth() / 2 - 75, w.GetHeight() / 2 - 66, "player 2 wins!");
    } else {
        w.DrawString(w.GetWidth() / 2 - 75, w.GetHeight() / 2 - 66, "player 1 wins!");
    }
    w.UpdateBuffer();
}

apvector<int> drawLandscape(window &w, color skycolor, color groundcolor) { // creates landscape. returns height of ground at every x-value. only called once
    setBrushAndPenColor(w, skycolor);
    w.DrawRectangle(0, 0, w.GetWidth(), w.GetHeight(), FILLED);
    RandGen r;
    apvector<int> heights(w.GetWidth()); // height of ground at every x-value
    int ystart = r.RandInt((double) w.GetHeight() * 0.666, (double) w.GetHeight() * 0.75); // semi random height of ground near bottom of screen
    setBrushAndPenColor(w, groundcolor);
    for (double x = 0; x < w.GetWidth(); x++) { // filling heights[]
        int yval = ystart + sin((double) (x / 60)) * 15; // ground will be sin curve
        w.DrawLine(x, yval, x, w.GetHeight());    // draws line from ground level to bottom of screen
        heights[x] = yval;
    }
    return heights;
}

bool getInput(window &w, color skycolor, tank &left, tank &right, bool &leftTurn) { // gets input for 2 parameters. returns true when enter key (shoot) is pressed
    char k = '#';  // for key, set to a known, but useless value
    int angle;
    int velocity;
    if (leftTurn) {
        angle = left.getAngle();
        velocity = left.getSpeed();
    } else {
        angle = right.getAngle();
        velocity = right.getSpeed();
    }
    w.SetFont(50, PLAIN, ROMAN);
    setBrushAndPenColor(w, BLACK);
    while (k != 13) { // return key
        w.SetBrush(skycolor); // erasing up top
        w.SetPen(skycolor);
        w.DrawRectangle(0, 0, w.GetWidth(), 200, FILLED);

        w.SetFont(50, PLAIN, ROMAN); // redrawing up top
        setBrushAndPenColor(w, BLACK);
        w.DrawString(w.GetWidth() / 2 - 60, 100, "angle:");
        w.DrawInteger(w.GetWidth() / 2 + 60, 100, angle);
        w.DrawString(w.GetWidth() / 2 - 60, 150, "speed:");
        w.DrawInteger(w.GetWidth() / 2 + 60, 150, velocity);

        w.UpdateBuffer();

        // redraw tank
        w.SetBrush(skycolor); // erasing around tank
        w.SetPen(skycolor);
        if (leftTurn) w.DrawRectangle(left.getXstart() - 3, left.getYstart() + 3, left.getXend() + 3, left.getYend() - 3, FILLED);
        else w.DrawRectangle(right.getXstart() + 3, right.getYstart() + 3, right.getXend() - 3, right.getYend() - 3, FILLED);

        // letting user change parameters
        w.WaitKeyPress(k);
        if (k == 8) angle++; // up
        if (k == 2) angle--; // down
        if (k == 6) velocity++; // right
        if (k == 4) velocity--; // left

        // setting limits
        if (angle < 1) angle = 1;
        if (angle > 90) angle = 90;
        if (velocity < 1) velocity = 1;
        if (velocity > 35) velocity = 35;

        if (leftTurn) {
            left.setAngle(angle);
            left.setSpeed(velocity);
            // changes pen color
            left.drawTank(w); // redrawing tank
        } else {
            right.setAngle(angle);
            right.setSpeed(velocity);
            // changes pen color
            right.drawTank(w); // redrawing tank
        }
        w.UpdateBuffer();
    }
    if (k == 13) return true;
}

color bullet(window &w, color skycolor, tank &left, tank &right, bool &leftTurn) { // goes through bullets path. returns color of what is hit.
    w.SetBrush(skycolor); // erasing up top to make sure it doesnt count hitting the text
    w.SetPen(skycolor);
    w.DrawRectangle(0, 0, w.GetWidth(), 200, FILLED);
    double pi = 3.1415926;
    double dtime = 0.007;
    int bulletRadius = 4;
    int bulletX, bulletY;
    if (leftTurn) {
        int angle = left.getAngle();
        int velocity = left.getSpeed();
        double radianAngle = angle * pi / 180;
        double xVel = cos(radianAngle) * velocity;
        double yVel = sin(radianAngle) * velocity;
        bulletX = left.getXend() + 3;
        bulletY = left.getYend() - 3;
        double time = 0;
        while (w.GetColor(bulletX, bulletY) == skycolor) {
            setBrushAndPenColor(w, BLACK);
            w.DrawCircle(bulletX, bulletY, bulletRadius, FILLED);
            w.UpdateBuffer();
            setBrushAndPenColor(w, skycolor);
            w.DrawCircle(bulletX, bulletY, bulletRadius + 1, FILLED);
            time += dtime;
            bulletX += xVel * time;
            bulletY += -yVel * time + 40 * time * time;
        }
        leftTurn = false;
    } else { // right
        int angle = right.getAngle();
        int velocity = right.getSpeed();
        double radianAngle = ((180 - angle) * pi / 180);
        double xVel = cos(radianAngle) * velocity;
        double yVel = sin(radianAngle) * velocity;
        bulletX = right.getXend() - 3;
        bulletY = right.getYend() - 3;
        double time = 0;
        while (w.GetColor(bulletX, bulletY) == skycolor) {
            setBrushAndPenColor(w, BLACK);
            w.DrawCircle(bulletX, bulletY, bulletRadius, FILLED);
            w.UpdateBuffer();
            setBrushAndPenColor(w, skycolor);
            w.DrawCircle(bulletX, bulletY, bulletRadius + 1, FILLED);
            time += dtime;
            bulletX += xVel * time;
            bulletY += -yVel * time + 40 * time * time;
        }
        leftTurn = true;
    }
    return w.GetColor(bulletX, bulletY);
}