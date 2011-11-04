#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/ImageIo.h"

#include "cinder/gl/Texture.h"
#include "cinder/Utilities.h"
#include "cinder/Thread.h"

#include "cinder/Utilities.h"

#include "MapperOp.h"

//#include <signals2.hpp>
#include <boost/lambda/lambda.hpp>


using namespace ci;
//using namespace ci::app;
using namespace cinder;
//using namespace std;


#define APP_INITIAL_WIDTH 1024.0f
#define APP_INITIAL_HEIGHT 768.0f

class MapperOpTest : public AppBasic {
 public:
	~MapperOpTest();
	void    setup();

	void    resize( ResizeEvent event );
	void    mouseDown( MouseEvent event );
	void    mouseUp( MouseEvent event );
	void    mouseDrag( MouseEvent event );
	void    keyDown( KeyEvent event );
	virtual void    draw();
	void    update();
	void	prepareSettings( Settings* settings );

	gl::Texture	      mTexture;

	MapperOp *mapper;

};
