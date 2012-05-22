/*
 * HandOpenCVTracker.h
 *
 *  Created on: Apr 17, 2011
 *      Author: eight
 */
#pragma once
#ifndef HANDOPENCVTRACKER_H_
#define HANDOPENCVTRACKER_H_

#include "ITrackerOp.h"

#include "cinder/gl/Texture.h"
#include "cinder/params/Params.h"

#include "Kinect.h"
#include "CinderOpenCv.h"

using namespace cinder;
using namespace ci;
using namespace std;

class HandOpenCVTracker: public ITrackerOp {
public:
	HandOpenCVTracker();
	virtual ~HandOpenCVTracker();

	void   setup();
	void   update();
	void   draw();
	Vec3f getShift();

private:
	Kinect mKinect;

	params::InterfaceGl mParams;

	float mThreshold, mBlobMin, mBlobMax;
	float mKinectTilt;

	gl::Texture mColorTexture, mDepthTexture, mCvTexture;
	Surface mDepthSurface;
};

#endif /* HANDOPENCVTRACKER_H_ */
