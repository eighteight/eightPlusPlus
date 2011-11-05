/*
 * IHandTrackerFactory.h
 *
 *  Created on: Apr 17, 2011
 *      Author: eight
 */
#pragma once
#include <string>
#include "HandOpenCVTrackerOp.h"
#include "HandGestureTrackerOp.h"
#include "EasyingTrackerOp.h"

#ifndef ITRACKERFACTORY_H_
#define ITRACKERFACTORY_H_

#define HAND_GESTURE_TRACKER "HandGestureTracker"
#define HAND_OPENCV_TRACKER "HandOpenCVTracker"
#define EASY_TRACKER "EasyTracker"

class TrackerFactory {
public:
	static ITrackerOp* makeTracker(string type);
};

#endif /* ITRACKERFACTORY_H_ */
