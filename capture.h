#ifndef __CAPTURE_H__
#define __CAPTURE_H__

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <jpeglib.h>

/*
   Allocate the memory for rgb24 based on the desktop of the window.
   Description
   		screen_width The width of desktop shall be stored.	
   		screen_height The height of desktop shall be stored.	
   Return
   		Upon successfully completion, a pointer specified the buffer of the rgb24 buffer. Otherwise, NULL shall be returned.
*/
int get_window_size(uint32_t *screen_width,uint32_t *screen_height);

/*
Capture a local screenshot of the desktop,
This returns an array for a 24 bit image.

Return Value:
	success: pointer to rgb24 data 
	failed : NULL
*/
int CaptureDesktop(uint8_t *rgb24);

#endif
