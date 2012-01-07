#pragma once
#include "cinder/app/AppBasic.h"
#include "cinder/ImageIo.h"

#include "cinder/gl/Texture.h"
#include "cinder/Utilities.h"

#include "MapperOp.h"


#define APP_INITIAL_WIDTH 1024.0f
#define APP_INITIAL_HEIGHT 768.0f

class MapperOpTest : public cinder::app::AppBasic {
 public:
	~MapperOpTest();
	void    setup();

	void    resize(cinder::app::ResizeEvent event );
	void    mouseDown(cinder::app::MouseEvent event );
	void    mouseUp(cinder::app::MouseEvent event );
	void    mouseDrag(cinder::app::MouseEvent event );
	void    keyDown(cinder::app::KeyEvent event );
	virtual void    draw();
	void    update();
	void	prepareSettings( Settings* settings );

	cinder::gl::Texture	      mTexture;

	MapperOp *mapper;

};
