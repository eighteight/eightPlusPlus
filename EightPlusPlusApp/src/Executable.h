/*
 * Executable.h
 *
 *  Created on: Nov 26, 2011
 *      Author: eight
 */

#ifndef EXECUTABLE_H_
#define EXECUTABLE_H_

#include "MediaOp.h"
#include "MapperOp.h"
#include "TrackerFactory.h"

class Executable {
public:
	Executable();
	virtual ~Executable();

    void setMediaOp(MediaOp *mediaOp);
    void setMapperOps(std::vector<MapperOp>*);
    void setTrackerOps(std::vector<ITrackerOp*>*);
    void setup();
    void update();
    std::vector<MapperOp>* getMapperOps() const;
    std::vector<ITrackerOp*> *getTrackerOps() const;
private:
	MediaOp* mediaOp;
	std::vector<MapperOp>* mapperOps;
	std::vector<ITrackerOp*>* trackerOps;
};

#endif /* EXECUTABLE_H_ */
