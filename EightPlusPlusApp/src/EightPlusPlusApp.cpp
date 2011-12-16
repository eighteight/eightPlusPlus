#include "EightPlusPlusApp.h"
int currentShift;
void EightPlusPlusApp::setup() {

	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	if (getArgs().size()<2) {
	    cerr << "usage: " << getArgs()[0] << " <applicationFilePath>\n. Exiting." << endl;
		exit(0);
	}

	executable = (new AppFactory(getResourcePath().string(),getArgs()[1]))->createExecutable();
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
	if (executable->getMediaOp()->hasCurrentMovie()) {
		mTexture = executable->getMediaOp()->getTexture();
	}
	vector<ITrackerOp*>::iterator itr;
	for (itr = executable->getTrackerOps()->begin(); itr != executable->getTrackerOps()->end(); ++itr)
		(*itr)->update(getElapsedSeconds());

	if (mTexture) {
		vector<MapperOpPtr>::iterator m;
		for (m = executable->getMapperOps().begin();
				m != executable->getMapperOps().end(); ++m) {
			//cout << "xx " << &mTexture << endl;
			//(*m).setTexture(mTexture);
		}
	}
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
		executable->getMediaOp()->update(0);
		break;
	case KeyEvent::KEY_b:
		executable->getMediaOp()->update(1);
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
				executable->getMediaOp()->update(currentVideoNum);
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
	vector<MapperOpPtr>::iterator itr;
	for (itr = executable->getMapperOps().begin(); itr != executable->getMapperOps().end(); ++itr)
		(*itr).get()->mouseDown(event);
}

void EightPlusPlusApp::mouseDrag( MouseEvent event )
{
	vector<MapperOpPtr>::iterator itr;
	for (itr = executable->getMapperOps().begin(); itr != executable->getMapperOps().end(); ++itr)
		(*itr).get()->mouseDrag(event);
}

void EightPlusPlusApp::mouseUp( MouseEvent event )
{
	vector<MapperOpPtr>::iterator itr;
	for (itr = executable->getMapperOps().begin(); itr != executable->getMapperOps().end(); ++itr)
		(*itr).get()->mouseUp(event);
}

void EightPlusPlusApp::draw()
{
	gl::setMatricesWindow(getWindowSize());
	glClearColor( 0.0f, 0.0f, 0.0f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
	executable->draw(currentShift);
}

void EightPlusPlusApp::prepareSettings( Settings* settings )
{
	settings->setWindowSize( APP_INITIAL_WIDTH, APP_INITIAL_HEIGHT );
}

CINDER_APP_BASIC( EightPlusPlusApp, RendererGl );
