#include "TrackerOpTest.h"
int currentShift;
void TrackerOpTest::setup()
{
	currentShift = 0;
	setupTracker();

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );


	gl::enableAlphaBlending();
	gl::enableDepthRead();
	gl::enableDepthWrite();

	mMovie = cinder::qtime::MovieGl( "data/sample_sorenson.mov" );
	mMovie.setLoop();
	mMovie.play();
}

void TrackerOpTest::setupTracker(){
	tracker = TrackerFactory::makeTracker(EASY_TRACKER);
	tracker->setup(&currentShift);
//	tracker->signalPositionUpdate.connect(bind(&PositionListener::updatePosition,&positionListener, boost::lambda::_1));
}

void TrackerOpTest::update() {
	tracker->update(getElapsedSeconds());
	mTexture = mMovie.getTexture();
}


void TrackerOpTest::resize( ResizeEvent event )
{

}

void TrackerOpTest::keyDown( KeyEvent event )
{
	tracker->keyDown(event);

	int evCode = event.getCode();
	switch(evCode)
	{
	case KeyEvent::KEY_ESCAPE:
		quit();
		break;
	case KeyEvent::KEY_f:
		setFullScreen( !isFullScreen() );
		break;
	default: break;
	}
}

void TrackerOpTest::mouseDown( MouseEvent event )
{
	tracker->mouseDown(event);

}

void TrackerOpTest::mouseDrag( MouseEvent event )
{
	tracker->mouseDrag(event);
}

void TrackerOpTest::mouseUp( MouseEvent event )
{
	tracker->mouseUp(event);
}

void TrackerOpTest::draw()
{
	gl::clear( Color( 0, 0, 0 ) );
	gl::enableAlphaBlending();

	if( mTexture ) {
		Rectf centeredRect = Rectf( mTexture.getBounds() );
		centeredRect.offset(Vec2f(currentShift, 0));

		gl::draw( mTexture, centeredRect  );
	}
}

void TrackerOpTest::prepareSettings( Settings* settings )
{
	settings->setWindowSize( APP_INITIAL_WIDTH, APP_INITIAL_HEIGHT );
}

CINDER_APP_BASIC( TrackerOpTest, RendererGl );
