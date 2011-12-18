/*
 * EasyTracker.cpp
 *
 *  Created on: Apr 19, 2011
 *      Author: eight
 */

#include "EasyingTrackerOp.h"
#include "cinder/gl/gl.h"
#include <iosfwd>

EasyingTracker::EasyingTracker() {

}

EasyingTracker::~EasyingTracker() {
}

void EasyingTracker::setup(int* curPosPtr){
	currentPositionPtr = curPosPtr;

	reset();
}

void EasyingTracker::update(const double elapsedTime){
	if (startEase || startEaseLeft){
		double ff = fmod( getElapsedSeconds() * TWEEN_SPEED, 1 );
		float time = math<float>::clamp( ff * 1.5f, 0, 1 );
		easing = easeInBounce(time);
		shift = easingStart + (int) ((startEase? 1:-1)*(easing*1200));

		signalPositionUpdate(shift);

		*currentPositionPtr = (int)shift;

		if (easing == 1.0f){
			startEase = false;
			startEaseLeft = false;
			easing = 0.0f;
		}
	}
}

void EasyingTracker::keyDown(cinder::app:: KeyEvent event ){

	if ('e' == event.getChar()){
		startEase = true;
		startEaseLeft = false;
		resetElapsedSeconds();
		easingStart = *currentPositionPtr;
	}
	if ('E' == event.getChar()){
		startEaseLeft = true;
		startEase = false;
		resetElapsedSeconds();
		easingStart = *currentPositionPtr;
	}

	if ('r' == event.getChar()){
		reset();
	}
}

void EasyingTracker::mouseDown(cinder::app::MouseEvent event){};
void EasyingTracker::mouseDrag(cinder::app:: MouseEvent event){};
void EasyingTracker::mouseUp(cinder::app:: MouseEvent event){};

void EasyingTracker::reset(){
	startEaseLeft = false;
	startEase = false;
	easing = 0;
	shift = 0;
	easingStart = *currentPositionPtr;
	resetElapsedSeconds();
}

double EasyingTracker::getElapsedSeconds(){
	return mTimer.getSeconds();
}

Vec3f EasyingTracker::getShift()
{
	return Vec3f(shift, 0, 0);
}

void   EasyingTracker::resetElapsedSeconds(){
	mTimer = Timer(true);
};

void EasyingTracker::draw()
{
	gl::setMatricesWindow(100,100 );
	// We'll set the color to an orange color
	glColor3f( 1.0f, 0.5f, 0.25f );

	gl::drawSolidCircle (Vec2f((float)shift, 200.0f), 4.0f );

	// tell OpenGL to actually draw the lines now
	glEnd();
}


