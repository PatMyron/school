/*
A simple graphics library for CSE 20211 
Originally created by Prof. Doug Thain.
Modified by Prof. Ramzi Bualuan
Do not change this file!
*/

#ifndef GFX_H
#define GFX_H

/* Open a new graphics window. */
void gfx_open( int width, int height, const char *title );

/* Draw a point at (x,y) */
void gfx_point( int x, int y );

/* Draw a line from (x1,y1) to (x2,y2) */
void gfx_line( int x1, int y1, int x2, int y2 );

/* Draw a circle centered at (xc,yc) with radius r */
void gfx_circle( int xc, int yc, int r);

/* Change the current drawing color. */
void gfx_color( int red, int green, int blue );

/* Clear the graphics window to the background color. */
void gfx_clear();

/* Change the current background color. */
void gfx_clear_color( int red, int green, int blue );

/* Wait for the user to press a key or mouse button. */
char gfx_wait();

/* Return the X and Y coordinates of the last event. */
int gfx_xpos();
int gfx_ypos();

/* Return the X and Y dimensions of the window. */
int gfx_xsize();
int gfx_ysize();

/* Check to see if an event is waiting. */
int gfx_event_waiting();

/* Flush all previous output to the window. */
void gfx_flush();

/* Display a string at (x,y) */
/* example of usage:  gfx_text(x, y, "hi there!"); */
void gfx_text( int x, int y , char *text );

#endif
