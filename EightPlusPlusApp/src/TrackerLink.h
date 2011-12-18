/*
 * TrackerLink.h
 *
 *  Created on: Dec 17, 2011
 *      Author: eight
 */

#ifndef TRACKERLINK_H_
#define TRACKERLINK_H_

#include "EightPlusPlusTypes.h"

class TrackerLink {
public:
	TrackerLink();
	TrackerLink(ITrackerOpPtr, MapperOpPtr);
	virtual ~TrackerLink();
	void update();
    MapperOpPtr getMapper() const;
    ITrackerOpPtr getTracker() const;
    void setMapper(MapperOpPtr mapper);
    void setTracker(ITrackerOpPtr tracker);
private:
	ITrackerOpPtr tracker;
	MapperOpPtr mapper;
};

#endif /* TRACKERLINK_H_ */
