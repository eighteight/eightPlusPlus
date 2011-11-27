#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/Rand.h"
#include "cinder/Camera.h"
#include "cinder/Surface.h"
#include "cinder/gl/Vbo.h"
#include "cinder/ImageIo.h"
#include "cinder/qtime/MovieWriter.h"
#include "cinder/Easing.h"

#include "cinder/gl/Texture.h"
#include "cinder/Utilities.h"
#include "cinder/Thread.h"

#include "TrackerFactory.h"
#include "MediaOp.h"
#include "MapperOp.h"
#include "AppFactory.h"

#include "boost/signals2.hpp"
#include <boost/lambda/lambda.hpp>

//#include "eightPlusPlus.hxx"


using namespace ci;
using namespace ci::app;
using namespace std;

#define APP_INITIAL_WIDTH 1024.0f
#define APP_INITIAL_HEIGHT 768.0f

extern int currentShift;
extern bool startEasing;

class EightPlusPlusApp : public AppBasic {
 public:
	void    setup();
	void    setupTracker();
	void    resize( ResizeEvent event );
	void    mouseDown( MouseEvent event );
	void    mouseUp( MouseEvent event );
	void    mouseDrag( MouseEvent event );
	void    keyDown( KeyEvent event );
	virtual void    draw();
	void    update();
	void	prepareSettings( Settings* settings );

	gl::Texture	      mTexture;

	AppFactory* 		  appFactory;

	Executable* executable;

//	auto_ptr<EightPlusPlusApp_t> revolverApp;

	float             easing;

	struct PositionListener {
	    void updatePosition(int shift) {
	    	currentShift = shift;
	    }
	};

	PositionListener	positionListener;
};
