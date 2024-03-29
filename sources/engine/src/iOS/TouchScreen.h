/*
Oolong Engine for the iPhone / iPod touch
Copyright (c) 2007-2008 Wolfgang Engel  http://code.google.com/p/oolongengine/

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from the use of this software.
Permission is granted to anyone to use this software for any purpose, 
including commercial applications, and to alter it and redistribute it freely, 
subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you wrote the original software. If you use this software in a product, an acknowledgment in the product documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such, and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.
*/
#include <TargetConditionals.h>
#include <Availability.h>

//#if __IPHONE_OS_VERSION_MAX_ALLOWED >= 30000
//#import "EAGLView2.h"
//#define _EAGLVIEW_ EAGLView2
//#else
#import "EAGLView.h"
#define _EAGLVIEW_ EAGLView
//#endif

@class EAGLCameraView;

typedef struct Touches
{ 
	float LocationXTouchesBegan;    // x and y coordinates where the touch began
	float LocationYTouchesBegan;
	float CountTouchesBegan;		// how many fingers are pressed
	float TapCountTouchesBegan;		// tap with one, two or three fingers or more at once
		
	float LocationXTouchesMoved;	// x and y coordinates where the touch moved
	float LocationYTouchesMoved;
	float CountTouchesMoved;
	float TapCountTouchesMoved;
	
	float LocationXTouchesEnded;	// x and y coordinates where the touch moved
	float LocationYTouchesEnded;
		
	bool TouchesEnd;				// nothing touches the screen anymore
} 
TouchScreenValues; 


@interface EAGLCameraView : _EAGLVIEW_
{
	TouchScreenValues TouchScreen;	
}

- (TouchScreenValues*) GetValuesTouchScreen;

@end


// C wrapper
TouchScreenValues* GetValuesTouchScreen();

