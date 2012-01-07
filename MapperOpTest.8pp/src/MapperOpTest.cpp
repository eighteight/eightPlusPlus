#include "MapperOpTest.h"

using namespace ci;
using namespace ci::app;
using namespace std;
int currentShift;
void MapperOpTest::setup()
{

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	gl::enableAlphaBlending();
	gl::enableDepthRead();
	gl::enableDepthWrite();

	mapper = new MapperOp(10,10,100,200,0.2, 0.4);
	loadImageFile();
	currentShift = 0;
}

void MapperOpTest::loadMovieFile()
{
	string moviePath = "/Users/eight/Desktop/water.mov";//getOpenFilePath();
	console() << "Path: " << moviePath << std::endl;
	if( ! moviePath.empty() )
	try {
		// load up the movie, set it to loop, and begin playing
		mMovie = qtime::MovieGl( moviePath );
		mMovie.setLoop();
		mMovie.play();
	}
	catch( ... ) {
		console() << "Unable to load the movie." << std::endl;
		mMovie.reset();
	}
}

void MapperOpTest::update() {
	if (mMovie){
		mTexture = mMovie.getTexture();
	}

	if (mTexture){
		mapper->setTexture(mTexture);
	}
}


void MapperOpTest::resize( ResizeEvent event )
{

}

void MapperOpTest::keyDown( KeyEvent event )
{
	int evCode = event.getCode();
	switch(evCode)
	{
	case KeyEvent::KEY_f:
		setFullScreen( !isFullScreen() );
		break;
	default:

		break;
	}
}

void MapperOpTest::mouseDown( MouseEvent event )
{
	mapper->mouseDown(event);
}

void MapperOpTest::mouseDrag( MouseEvent event )
{
	mapper->mouseDrag(event);
}

void MapperOpTest::mouseUp( MouseEvent event )
{
	mapper->mouseUp(event);
}

void MapperOpTest::draw()
{
	gl::setMatricesWindow(getWindowSize());
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	if (mTexture){
		gl::color(Color(1, 1, 1));

		mapper->draw();

		gl::color(Color(1, 1, 1));
	}

	mapper->drawControls();

}

MapperOpTest::~MapperOpTest()
{
	delete mapper;
}

void MapperOpTest::prepareSettings( Settings* settings )
{
	settings->setWindowSize( APP_INITIAL_WIDTH, APP_INITIAL_HEIGHT );
}

CINDER_APP_BASIC( MapperOpTest, RendererGl );

void MapperOpTest::loadImageFile()
{
		try {
			fs::path path = getOpenFilePath( "", ImageIo::getLoadExtensions() );
			if( ! path.empty() ) {
				mTexture = gl::Texture( loadImage( path ) );
			}
		}
		catch( ... ) {
			console() << "unable to load the texture file!" << std::endl;
		}
}


