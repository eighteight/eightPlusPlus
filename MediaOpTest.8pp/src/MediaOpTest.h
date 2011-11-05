#pragma once

#include "MediaOp.h"

#include "cinder/app/AppBasic.h"
#include "cinder/ImageIo.h"
#
#include "cinder/gl/Texture.h"
#include "cinder/Utilities.h"
#include "cinder/Thread.h"

#include <boost/lambda/lambda.hpp>



using namespace ci;
using namespace ci::app;
using namespace std;

#define APP_INITIAL_WIDTH 1024.0f
#define APP_INITIAL_HEIGHT 768.0f

class MediaOpTest : public AppBasic {
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

	MediaOp       mediaOp;
};
