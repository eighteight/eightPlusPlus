/*
 * EasyTracker.h
 *
 *  Created on: Apr 19, 2011
 *      Author: eight
 */

#pragma once
#ifndef EASYTRACKER_H_
#define EASYTRACKER_H_

#include "cinder/Easing.h"
#include "ITrackerOp.h"

using namespace ci;
using namespace std;

class EasyingTracker: public ITrackerOp {
public:
	EasyingTracker();
	virtual ~EasyingTracker();
	void update(const double elapsedTime);
	void draw();
	void keyDown(cinder::app:: KeyEvent event );
    void mouseDown(cinder::app::MouseEvent event);
	void mouseDrag(cinder::app:: MouseEvent event);
	void mouseUp(cinder::app:: MouseEvent event);
	void setup(int* curPosPtr);
	void reset();
    Vec3f getShift();

	bool startEase;

	bool startEaseLeft;

	int shift;

	int easingStart;

	int* currentPositionPtr;
protected:
	double getElapsedSeconds();
	void   resetElapsedSeconds();

};

#endif /* EASYTRACKER_H_ */
