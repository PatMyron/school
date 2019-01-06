#include <math.h>
#include <stdio.h>
#include "gfx2.h"       // simple graphics library given by instructors. included in repository
#include <unistd.h>

float lateral();    // big circle left and right
void circular();    // carriages clockwise
void swing();        // carriage slight swing
void vert();        // people bounce

// global vars
float t = 0;        // time
int w = 1000, h = 700;    // width,height
int r = 200;         // big radius
int miniR = 50;        // carriage radius
int beam = 60;        // carriage+wheel connector length
int y = 250;        // center of big wheel height
int i, j;        // counters
float pi = 3.1415926;
float bTX[5], bTY[5];  // top of beam coordinates
float bBX[5], bBY[5];  // bottom of beam coordinates
float cX[5], cY[5];   // center of carriage

int main() {
    char c = '0';

    gfx_open(w, h, "carnival");
    while (c != 'q') {
        gfx_clear();
        circular();
        swing();

        for (i = 0; i < 5; i++) {
            cX[i] = bBX[i];
            cY[i] = bBY[i] + miniR;
        }
        for (i = 0; i < 5; i++) {
            gfx_line(bTX[i], bTY[i], bBX[i], bBY[i]);  // support
            gfx_circle(bBX[i], cY[i], miniR);      // carriage

            int numLines = 80;
            float part = pi / 2 / numLines;
            for (j = 0; j < numLines; j++) {      // lines covering bottom half
                gfx_line(bBX[i] + cos(pi + part * j) * miniR, cY[i] - sin(pi + part * j) * miniR, bBX[i] + cos(2 * pi - part * j) * miniR,
                         cY[i] - sin(2 * pi - part * j) * miniR); // lines covering bottom
            }
            vert();
        }
        gfx_circle(lateral(), y, r);  // ferris wheel main wheel
        gfx_flush();
        t += 0.1;
        usleep(30000);
        if (gfx_event_waiting()) {
            c = gfx_wait();
        }
    }
}

float lateral() {
    return (w / 2 + (w / 2 - r - miniR) * sin(t / 2));
}

void circular() {
    float x = lateral();
    for (i = 0; i < 5; i++) {
        bTX[i] = x + r * cos(t / 3 + i * 2 * pi / 5);
        bTY[i] = y + r * sin(t / 3 + i * 2 * pi / 5);
    }
}

void swing() {
    for (i = 0; i < 5; i++) {
        bBX[i] = bTX[i] + beam * cos(3 * pi / 2 + sin(6 * t) / 6);
        bBY[i] = bTY[i] - beam * sin(3 * pi / 2 + sin(6 * t) / 6);
    }
}

void vert() {
    // drawing people
    float bounce = 3 + 5 * sin(t * 2);
    gfx_line(bBX[i] + miniR / 2.5, cY[i] + bounce, bBX[i] + miniR / 2.5, cY[i] - 20 + bounce);
    gfx_line(bBX[i] - miniR / 2.5, cY[i] + bounce, bBX[i] - miniR / 2.5, cY[i] - 20 + bounce);
    gfx_circle(bBX[i] + miniR / 2.5, cY[i] - 30 + bounce, 10);
    gfx_circle(bBX[i] - miniR / 2.5, cY[i] - 30 + bounce, 10);
    gfx_line(bBX[i] + miniR / 2.5, cY[i] - 7 + bounce, bBX[i] + miniR / 2.5 + 7, cY[i] - 12 + bounce);
    gfx_line(bBX[i] + miniR / 2.5, cY[i] - 7 + bounce, bBX[i] + miniR / 2.5 - 7, cY[i] - 12 + bounce);
    gfx_line(bBX[i] - miniR / 2.5, cY[i] - 7 + bounce, bBX[i] - miniR / 2.5 + 7, cY[i] - 12 + bounce);
    gfx_line(bBX[i] - miniR / 2.5, cY[i] - 7 + bounce, bBX[i] - miniR / 2.5 - 7, cY[i] - 12 + bounce);
}
