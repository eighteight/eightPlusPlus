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

void Executable::setMediaOp(MediaOpPtr mediaOp)
{
    this->mediaOp = mediaOp;
}

void Executable::setMapperOps(std::vector<MapperOpPtr> mappers)
{
	this->mapperOps = mappers;
}

std::vector<MapperOpPtr> Executable::getMapperOps() const
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

}

void Executable::update()
{
	vector<ITrackerOp*>::iterator itr;
	for (itr = trackerOps->begin(); itr != trackerOps->end(); ++itr)
		(*itr)->update(getElapsedSeconds());

	vector<MediaLinkPtr>::iterator ml;
	for (ml = mediaLinks.begin(); ml != mediaLinks.end(); ++ml){
		(*ml)->update();
	}
}

std::vector<ITrackerOp*> *Executable::getTrackerOps() const
{
    return trackerOps;
}

MediaOpPtr Executable::getMediaOp() const
{
    return mediaOp;
}

std::vector<MediaLinkPtr> Executable::getMediaLinks() const
{
    return mediaLinks;
}

void Executable::draw(int currentShift)
{
	vector<MapperOpPtr>::iterator m;
	for (m = mapperOps.begin(); m != mapperOps.end(); ++m) {
		//cout<<"id "<<mediaOp->getTexture().getId()<<endl;

		//(*m).draw(currentShift);
		(*m).get()->draw();
	}

	vector<MediaLinkPtr>::iterator ml;
	for (ml = mediaLinks.begin(); ml != mediaLinks.end(); ++ml){
		(*ml).get()->getMapperOp().get()->draw(currentShift);
	}

	vector<ITrackerOp*>::iterator t;
	for (t = trackerOps->begin(); t != trackerOps->end(); ++t)
		(*t)->draw();
}

void Executable::setMediaLinks(std::vector<MediaLinkPtr> mediaLinks)
{
    this->mediaLinks = mediaLinks;
}













