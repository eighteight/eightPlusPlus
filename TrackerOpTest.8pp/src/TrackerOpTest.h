#pragma once
#include "cinder/app/AppBasic.h"

#include "cinder/gl/Texture.h"
#include "cinder/Utilities.h"
#include "cinder/qtime/QuickTime.h"

#include "TrackerFactory.h"

#include "boost/signals2.hpp"
#include <boost/lambda/lambda.hpp>


using namespace ci;
using namespace ci::app;
using namespace std;

#define APP_INITIAL_WIDTH 1024.0f
#define APP_INITIAL_HEIGHT 768.0f

extern int currentShift;
extern bool startEasing;

class TrackerOpTest : public AppBasic {
	qtime::MovieGl	  mMovie;
 public:
	void    setup();
	void    setupTracker();
	void    resize( ResizeEvent event );
	void    mouseDown( MouseEvent event );
	void    mouseUp( MouseEvent event );
	void    mouseDrag( MouseEvent event );
	void    keyDown( KeyEvent event );
    void    draw();
	void    update();
	void	prepareSettings( Settings* settings );

	gl::Texture	      mTexture;

	float             easing;

	struct PositionListener {
	    void updatePosition(int shift) {
	    	currentShift = shift;
	    }
	};

	PositionListener	positionListener;

	ITrackerOp* tracker;

};
