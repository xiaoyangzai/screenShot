#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <string.h>

#include "capture.h"

/*
	Screen width and hieght;
*/
int get_window_size(uint32_t *screen_width,uint32_t *screen_height)
{
	Window desktop;
	Display* dsp;
	dsp = XOpenDisplay(NULL);/* Connect to a local display */
	if(NULL==dsp)
	{
		printf("%s:%s\n","CaptureDesktop","Cannot connect to local display");
		exit(-1);
	}
	desktop = RootWindow(dsp,0);/* Refer to the root window */
	if(0==desktop)
	{
		//printf("cannot get root window\n");
		fprintf(stderr,"%s:%s\n","CaptureDesktop","cannot get root window");
		exit(-1);
	}


	/* Retrive the width and the height of the screen */
	*screen_width = DisplayWidth(dsp,0);
	*screen_height = DisplayHeight(dsp,0);
	XCloseDisplay(dsp);
	return 0;
}

/*
Capture a local screenshot of the desktop,
This returns an array for a 24 bit image.

Return Value:
	success: 0 
	failed : -1 
*/
int CaptureDesktop(uint8_t *rgb24)
{
	assert(rgb24 != NULL);
	Window desktop;
	Display* dsp;
	XImage* img;

	int screen_width;
	int screen_height;

	dsp = XOpenDisplay(NULL);/* Connect to a local display */
	if(NULL==dsp)
	{
		printf("%s:%s\n","CaptureDesktop","Cannot connect to local display");
		exit(-1);
	}
	desktop = RootWindow(dsp,0);/* Refer to the root window */
	if(0==desktop)
	{
		//printf("cannot get root window\n");
		fprintf(stderr,"%s:%s\n","CaptureDesktop","cannot get root window");
		exit(-1);
	}

	/* Retrive the width and the height of the screen */
	screen_width = DisplayWidth(dsp,0);
	screen_height = DisplayHeight(dsp,0);

	/* Get the Image of the root window.
	   ZPixmap Format:
			绿-蓝-红-透明度
	*/

	img = XGetImage(dsp,desktop,0,0,screen_width,screen_height,~0,ZPixmap);

	int i = 0;
	uint8_t* rgb_begin = rgb24;
	uint8_t* img_begin = (uint8_t*)img->data;
	for(i = 0;i < screen_width*screen_height;i++)
	{
		rgb_begin = rgb24 + 3*i;
		img_begin = (uint8_t *)img->data + 4*i;

		//R
		rgb_begin[0] = img_begin[2];

		//B
		rgb_begin[1] = img_begin[1];

		//G
		rgb_begin[2] = img_begin[0];
	}
	XDestroyImage(img);
	XCloseDisplay(dsp);
	return 0;
}
