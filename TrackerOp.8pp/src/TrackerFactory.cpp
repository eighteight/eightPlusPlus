/*
 * TrackerFactory.cpp
 *
 *  Created on: Apr 17, 2011
 *      Author: eight
 */

#include <string>
#include "TrackerFactory.h"

using namespace std;


ITrackerOp* TrackerFactory::makeTracker(string type){
	if (HAND_GESTURE_TRACKER == type){
		return new HandGestureTracker;
	}
	else
		if (HAND_OPENCV_TRACKER == type){
		return new HandOpenCVTracker;
	}
	else
		if (EASY_TRACKER == type){
			return new EasyingTracker;
		}
	return NULL;
}
