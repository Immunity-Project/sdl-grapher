/*  sdl-grapher - SDL library
 *  Copyright (C) 2009 - Hans-Kristian Arntzen
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *  
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *  
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */


#ifndef GRAPH_H
#define GRAPH_H

#include <SDL/SDL.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

/* TODO: 
 * Better error handling
 */

typedef struct graph {
	
	float xMin;          /* Indicates the smallest value the graph window will show on the x-axis. */
	float xMax;			 /* Largest x */
	float xScale;		 /* Indicates the distance between the "landmarks" on the x-axis */
	float yMin;			 /* Same as indicated over, just on the y-axis */
	float yMax;
	float yScale;
	int width;			 /* When the SDL window is initialized, these values will decide the size of it in pixels */
	int height;
    
	Uint32 color;        /* When a pixel is printed to the screen, this variable will be used to determine which color
						  * is to be printed on the screen */
    
	SDL_Surface * workingSurface; /* This is the main SDL_Surface that is used transparently in most functions below */
} Graph;


void draw_grid(Graph *, int, int);
/* This function will draw a grid to the SDL_Surface in the graph-struct. The function also takes
 * thickness of grid and length of the "landmarks" on the grid. 0 length/thickness indicates smallest possible
 * e.g. ( 1 pixel width ) */

Uint32 * get_pixel_from_coordinates ( Graph *, float, float );
/* Returns a pointer to a certain pixel by the means of giving it coordinates on the graph */

Uint32 * get_pixel_from_window ( Graph *, int, int );
/* Returns a pointer to a certain pixel by the means of giving it the coorinates on the SDL window itself. 
 * e.g ( 0, 0) will always return the top-left pixel */

int get_width_from_coordinate ( Graph *, float x );
/* Returns the x coordinate on the SDL window itself by using a graph coordinate */

int get_height_from_coordinate ( Graph *, float y );
/* Returns the y coordinate */

void init_graph ( Graph * );
/* Initializes the graph. Sets up an SDL window. This function must be executed before any other API functions!
 * The struct it takes as input must be properly filled in before calling this. */

void print_pixel ( Graph *, float, float );
/* Prints a pixel to the surface in the struct by using graph coordinates */

void print_pixel_by_window ( Graph *, int, int );
/* Prints a pixel to the surface in the struct by using SDL window coordinates */

void update_screen(Graph *);
/* Updates the screen. Performance tip: When printing many points to the screen, do not
 * refresh screen for every print. Print some points, then refresh. */

void delay ( int );
/* Halts further execution of the application. (Useful for animation)
 * Input is given in milliseconds. e.g. delay(1000); halts for 1 second. */

void clear_graph(Graph *);
/* Clears the graph, returning it to the initial black state.
 * (Still need to update_screen to see the result! */

void idle();
/* Will idle here until user quits program. */

int write_BMP_header(FILE *, int, int );

int write_BMP_data(FILE *, Graph * );

void write_BMP(Graph *, char *);



void set_color(Graph *, int, int, int);
/* Sets the color in the struct given in normal 24-bit RGB format */

void quit();
/* Instantly quits the program */
	
#endif