/*
 * Executable.cpp
 *
 *  Created on: Nov 26, 2011
 *      Author: eight
 */

#include "Executable.h"

using namespace cinder::app;

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

void Executable::setTrackerOps(std::vector<ITrackerOpPtr> trackerOps)
{
	this->trackerOps = trackerOps;
}

void Executable::setup()
{
	mediaOp->load();

	int currentShift = 0;

	vector<ITrackerOpPtr>::iterator itr;
	for (itr = trackerOps.begin(); itr != trackerOps.end(); ++itr) {
		(*itr).get()->setup(&currentShift);
		//(*itr)->signalPositionUpdate.connect(bind(&PositionListener::updatePosition,&positionListener, boost::lambda::_1));
	}

}

void Executable::update()
{
	vector<ITrackerOpPtr>::iterator itr;
	for (itr = trackerOps.begin(); itr != trackerOps.end(); ++itr)
		(*itr).get()->update(getElapsedSeconds());

	vector<MediaLinkPtr>::iterator ml;
	for (ml = mediaLinks.begin(); ml != mediaLinks.end(); ++ml){
		(*ml)->update();
	}

	vector<TrackerLinkPtr>::iterator tl;
	for (tl = trackerLinks.begin(); tl != trackerLinks.end(); ++tl){
		(*tl)->update();
	}
}

std::vector<ITrackerOpPtr> Executable::getTrackerOps() const
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
		(*m).get()->draw(currentShift);
		(*m).get()->draw();
	}

	vector<ITrackerOpPtr>::iterator t;
	for (t = trackerOps.begin(); t != trackerOps.end(); ++t)
		(*t).get()->draw();
}

void Executable::mouseUp(cinder::app::MouseEvent event)
{
	vector<MapperOpPtr>::iterator itr;
	for (itr = mapperOps.begin(); itr != mapperOps.end(); ++itr)
		(*itr).get()->mouseUp(event);
}

void Executable::mouseDown(cinder::app::MouseEvent event)
{
	vector<MapperOpPtr>::iterator itr;
	for (itr = mapperOps.begin(); itr != mapperOps.end(); ++itr)
		(*itr).get()->mouseDown(event);
}

void Executable::mouseDrag(cinder::app::MouseEvent event)
{
	vector<MapperOpPtr>::iterator itr;
	for (itr = mapperOps.begin(); itr != mapperOps.end(); ++itr)
		(*itr).get()->mouseDrag(event);
}

void Executable::keyDown(KeyEvent event)
{
	vector<ITrackerOpPtr>::iterator itr;
	for (itr = trackerOps.begin(); itr != trackerOps.end(); ++itr)
		(*itr).get()->keyDown(event);
}

void Executable::setMediaLinks(std::vector<MediaLinkPtr> mediaLinks)
{
    this->mediaLinks = mediaLinks;
}

std::vector<TrackerLinkPtr> Executable::getTrackerLinks() const
{
    return trackerLinks;
}

void Executable::setTrackerLinks(std::vector<TrackerLinkPtr> trackerLinks)
{
    this->trackerLinks = trackerLinks;
}















