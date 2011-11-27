#include "EightPlusPlusApp.h"
int currentShift;
void EightPlusPlusApp::setup() {

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	if (getArgs().size()<2) {
	    cerr << "usage: " << getArgs()[0] << " <applicationFilePath>\n. Exiting." << endl;
		exit(0);
	}

	executable  = (new AppFactory(getResourcePath().string(),getArgs()[1]))->createExecutable();
    executable->setup();
	currentShift = 0;
	setupTracker();

	gl::enableAlphaBlending();
	gl::enableDepthRead();
	gl::enableDepthWrite();
}

void EightPlusPlusApp::setupTracker(){

	vector<ITrackerOp*>::iterator itr;
	for (itr = executable->getTrackerOps()->begin(); itr !=  executable->getTrackerOps()->end(); ++itr) {
		(*itr)->setup(&currentShift);
		(*itr)->signalPositionUpdate.connect(bind(&PositionListener::updatePosition,&positionListener, boost::lambda::_1));
	}
}

void EightPlusPlusApp::update() {
	executable->update();
	if (mediaOp->hasCurrentMovie()) {
		mTexture = mediaOp->getCurrentMovie().getTexture();
	}
	vector<ITrackerOp*>::iterator itr;
	for (itr = executable->getTrackerOps()->begin(); itr != executable->getTrackerOps()->end(); ++itr)
		(*itr)->update(getElapsedSeconds());
}


void EightPlusPlusApp::resize( ResizeEvent event )
{

}

void EightPlusPlusApp::keyDown( KeyEvent event )
{

	vector<ITrackerOp*>::iterator itr;
	for (itr = executable->getTrackerOps()->begin(); itr != executable->getTrackerOps()->end(); ++itr)
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
		mediaOp->update(0);
		break;
	case KeyEvent::KEY_b:
		mediaOp->update(1);
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
				mediaOp->update(currentVideoNum);
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
	for (itr = executable->getMapperOps()->begin(); itr != executable->getMapperOps()->end(); ++itr)
		(*itr).mouseDown(event);
}

void EightPlusPlusApp::mouseDrag( MouseEvent event )
{
	vector<MapperOp>::iterator itr;
	for (itr = executable->getMapperOps()->begin(); itr != executable->getMapperOps()->end(); ++itr)
		(*itr).mouseDrag(event);
}

void EightPlusPlusApp::mouseUp( MouseEvent event )
{
	vector<MapperOp>::iterator itr;
	for (itr = executable->getMapperOps()->begin(); itr != executable->getMapperOps()->end(); ++itr)
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
		for (mapper = executable->getMapperOps()->begin(); mapper != executable->getMapperOps()->end(); ++mapper) {
			(*mapper).draw(mTexture, currentShift);
		}

		gl::color(Color(1, 1, 1));
	}

	vector<MapperOp>::iterator mapprItr;
	for (mapprItr = executable->getMapperOps()->begin(); mapprItr != executable->getMapperOps()->end(); ++mapprItr)
		(*mapprItr).draw();

	vector<ITrackerOp*>::iterator trackerItr;
	for (trackerItr = executable->getTrackerOps()->begin(); trackerItr != executable->getTrackerOps()->end(); ++trackerItr)
		(*trackerItr)->draw();

}

void EightPlusPlusApp::prepareSettings( Settings* settings )
{
	settings->setWindowSize( APP_INITIAL_WIDTH, APP_INITIAL_HEIGHT );
}

CINDER_APP_BASIC( EightPlusPlusApp, RendererGl );
