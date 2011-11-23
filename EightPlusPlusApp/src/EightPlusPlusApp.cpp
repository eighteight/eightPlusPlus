#include "EightPlusPlusApp.h"
int currentShift;
void EightPlusPlusApp::setup() {

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	if (getArgs().size()<2) {
	    cerr << "usage: " << getArgs()[0] << " <applicationFilePath>\n. Exiting." << endl;
		exit(0);
	}

	appFactory = AppFactory(getAppPath().string(),getArgs()[1]);

	currentShift = 0;
	setupTracker();

	gl::enableAlphaBlending();
	gl::enableDepthRead();
	gl::enableDepthWrite();

	mediaOp.setMediaFilePaths(appFactory.mediaFilePaths);
	mediaOp.load();

	int tW = mediaOp.getCurrentMovie().getWidth();
	int tH = mediaOp.getCurrentMovie().getHeight();

	vector<MapperOp>::iterator mapr;
		for(mapr= appFactory.mappers.begin();mapr !=appFactory.mappers.end();++mapr)
			(*mapr).setTextureSize(tW, tH);
}

void EightPlusPlusApp::setupTracker(){

	vector<ITrackerOp*>::iterator itr;
	for (itr = appFactory.trackers.begin(); itr != appFactory.trackers.end(); ++itr) {
		(*itr)->setup(&currentShift);
		(*itr)->signalPositionUpdate.connect(bind(&PositionListener::updatePosition,&positionListener, boost::lambda::_1));
	}
}

void EightPlusPlusApp::update() {
	if (mediaOp.hasCurrentMovie()) {
		mTexture = mediaOp.getCurrentMovie().getTexture();
	}
	vector<ITrackerOp*>::iterator itr;
	for (itr = appFactory.trackers.begin(); itr != appFactory.trackers.end(); ++itr)
		(*itr)->update(getElapsedSeconds());
}


void EightPlusPlusApp::resize( ResizeEvent event )
{

}

void EightPlusPlusApp::keyDown( KeyEvent event )
{

	vector<ITrackerOp*>::iterator itr;
	for (itr = appFactory.trackers.begin(); itr != appFactory.trackers.end(); ++itr)
		(*itr)->keyDown(event);

	switch( event.getCode() ) {
		case 276:
			currentShift ++;
		break;
		case 275:
			currentShift --;
		break;
	}

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

	if ('r' == event.getChar()){
		currentShift = 0;
	}
}

void EightPlusPlusApp::mouseDown( MouseEvent event )
{
	vector<MapperOp>::iterator itr;
	for (itr = appFactory.mappers.begin(); itr != appFactory.mappers.end(); ++itr)
		(*itr).mouseDown(event);
}

void EightPlusPlusApp::mouseDrag( MouseEvent event )
{
	vector<MapperOp>::iterator itr;
	for (itr = appFactory.mappers.begin(); itr != appFactory.mappers.end(); ++itr)
		(*itr).mouseDrag(event);
}

void EightPlusPlusApp::mouseUp( MouseEvent event )
{
	vector<MapperOp>::iterator itr;
	for (itr = appFactory.mappers.begin(); itr != appFactory.mappers.end(); ++itr)
		(*itr).mouseUp(event);
}

void EightPlusPlusApp::draw()
{
	gl::setMatricesWindow(getWindowSize());
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	if (mTexture){
		gl::color(Color(1, 1, 1));

		vector<MapperOp>::iterator mapper;
		for (mapper = appFactory.mappers.begin(); mapper != appFactory.mappers.end(); ++mapper) {
			(*mapper).draw(mTexture, currentShift);
		}

		gl::color(Color(1, 1, 1));
	}

	vector<MapperOp>::iterator mapprItr;
	for (mapprItr = appFactory.mappers.begin(); mapprItr != appFactory.mappers.end(); ++mapprItr)
		(*mapprItr).draw();

	vector<ITrackerOp*>::iterator trackerItr;
	for (trackerItr = appFactory.trackers.begin(); trackerItr != appFactory.trackers.end(); ++trackerItr)
		(*trackerItr)->draw();

}

void EightPlusPlusApp::prepareSettings( Settings* settings )
{
	settings->setWindowSize( APP_INITIAL_WIDTH, APP_INITIAL_HEIGHT );
}

CINDER_APP_BASIC( EightPlusPlusApp, RendererGl );
