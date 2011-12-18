/*
 * TrackerLink.cpp
 *
 *  Created on: Dec 17, 2011
 *      Author: eight
 */

#include "TrackerLink.h"

TrackerLink::TrackerLink() {
	// TODO Auto-generated constructor stub

}

TrackerLink::~TrackerLink() {
	// TODO Auto-generated destructor stub
}

MapperOpPtr TrackerLink::getMapper() const
{
    return mapper;
}

ITrackerOpPtr TrackerLink::getTracker() const
{
    return tracker;
}

void TrackerLink::setMapper(MapperOpPtr mapper)
{
    this->mapper = mapper;
}

void TrackerLink::update()
{
	mapper.get()->setShift(tracker.get()->getShift());
}

TrackerLink::TrackerLink(ITrackerOpPtr tracker, MapperOpPtr mapper)
{
	this->tracker = tracker;
	this->mapper = mapper;
}

void TrackerLink::setTracker(ITrackerOpPtr tracker)
{
    this->tracker = tracker;
}



