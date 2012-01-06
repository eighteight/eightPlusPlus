/*
 * IHandTracker.h
 *
 *  Created on: Apr 17, 2011
 *      Author: eight
 */
#pragma once
#ifndef ITRACKER_H_
#define ITRACKER_H_

#include "cinder/app/KeyEvent.h"
#include "cinder/app/MouseEvent.h"
#include "cinder/Timer.h"

using namespace cinder;

const float TWEEN_SPEED = 0.05f;
class ITrackerOp {
public:
	virtual void setup(int *currentPosition){};
	virtual void setup(){};
	virtual void update(const double timeLapsed){};
	virtual void draw(){};
	virtual void keyDown(cinder::app:: KeyEvent event ){};
	virtual void mouseDown(cinder::app::MouseEvent event){};
	virtual void mouseDrag(cinder::app:: MouseEvent event){};
	virtual void mouseUp(cinder::app:: MouseEvent event){};
	virtual Vec3f getShift(){return Vec3f(0,0,0);};

	float easing;
protected:
	virtual double getElapsedSeconds(){return 1;};
	virtual void   resetElapsedSeconds(){};


	Timer mTimer;
};

#endif /* ITRACKER_H_ */
