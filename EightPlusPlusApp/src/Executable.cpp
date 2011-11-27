/*
 * Executable.cpp
 *
 *  Created on: Nov 26, 2011
 *      Author: eight
 */

#include "Executable.h"

Executable::Executable() {
	// TODO Auto-generated constructor stub

}

Executable::~Executable() {
	// TODO Auto-generated destructor stub
}

void Executable::setMediaOp(MediaOp *mediaOp)
{
    this->mediaOp = mediaOp;
}

void Executable::setMapperOps(std::vector<MapperOp>* allocator)
{
	this->mapperOps = allocator;
}

std::vector<MapperOp>* Executable::getMapperOps() const
{
    return mapperOps;
}

void Executable::setTrackerOps(std::vector<ITrackerOp*> *allocator)
{
	this->trackerOps = allocator;
}

void Executable::setup()
{
	mediaOp->load();

	int tW = mediaOp->getCurrentMovie().getWidth();
	int tH = mediaOp->getCurrentMovie().getHeight();

	vector<MapperOp>::iterator mapr;
	for(mapr= mapperOps->begin();mapr != mapperOps->end();++mapr)
		(*mapr).setTextureSize(tW, tH);
}

void Executable::update()
{
	if (mediaOp->hasCurrentMovie()) {
		//mTexture = mediaOp->getCurrentMovie().getTexture();
	}
	vector<ITrackerOp*>::iterator itr;
	for (itr = trackerOps->begin(); itr != trackerOps->end(); ++itr)
		(*itr)->update(getElapsedSeconds());
}

std::vector<ITrackerOp*> *Executable::getTrackerOps() const
{
    return trackerOps;
}









