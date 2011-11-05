#include "MediaOpTest.h"

void MediaOpTest::setup()
{

	std::vector<string> mediaFilePaths;
	mediaFilePaths.push_back("data/sample_sorenson.mov");
	mediaOp.setMediaFilePaths(mediaFilePaths);
	mediaOp.load();

	int tW = mediaOp.getCurrentMovie().getWidth();
	int tH = mediaOp.getCurrentMovie().getHeight();
}

void MediaOpTest::update() {
	if (mediaOp.hasCurrentMovie()) {
		mTexture = mediaOp.getCurrentMovie().getTexture();
	}
}


void MediaOpTest::resize( ResizeEvent event )
{

}

void MediaOpTest::keyDown( KeyEvent event )
{
	int evCode = event.getCode();
	switch(evCode)
	{
	case KeyEvent::KEY_a:
		mediaOp.update(0);
		break;
	case KeyEvent::KEY_b:
		mediaOp.update(1);
		break;
	case KeyEvent::KEY_ESCAPE:
		quit();
		break;
	case KeyEvent::KEY_f:
		setFullScreen( !isFullScreen() );
		break;
	default:
		try
			{
				uint currentVideoNum = lexical_cast<int>(evCode);
				mediaOp.update(currentVideoNum);
			}
			catch(bad_lexical_cast &)
			{
			   ;
			}
		break;
	}
}

void MediaOpTest::mouseDown( MouseEvent event )
{
}

void MediaOpTest::mouseDrag( MouseEvent event )
{

}

void MediaOpTest::mouseUp( MouseEvent event )
{

}

void MediaOpTest::draw()
{
	gl::setMatricesWindow(getWindowSize());
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	if (mTexture){
		gl::color(Color(1, 1, 1));
		Rectf centeredRect = Rectf( mTexture.getBounds() ).getCenteredFit( getWindowBounds(), true );
		gl::draw( mTexture, centeredRect  );

		gl::color(Color(1, 1, 1));
	}
}

void MediaOpTest::prepareSettings( Settings* settings )
{
	settings->setWindowSize( APP_INITIAL_WIDTH, APP_INITIAL_HEIGHT );
}

CINDER_APP_BASIC( MediaOpTest, RendererGl );
