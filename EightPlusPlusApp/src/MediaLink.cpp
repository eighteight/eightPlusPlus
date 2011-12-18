/*
 * MediaLink.cpp
 *
 *  Created on: Dec 13, 2011
 *      Author: eight
 */

#include "MediaLink.h"

MediaLink::MediaLink(MediaOpPtr& mediaOp, MapperOpPtr& mapperOp) {
	this->mediaOp = mediaOp;
	this->mapperOp = mapperOp;
}

MediaLink::~MediaLink() {
}

MapperOpPtr MediaLink::getMapperOp() const
{
    return mapperOp;
}

MediaOpPtr MediaLink::getMediaOp() const
{
    return mediaOp;
}

void MediaLink::setMapperOp(MapperOpPtr &mapperOp)
{
    this->mapperOp = mapperOp;
}

void MediaLink::setMediaOp(MediaOpPtr &mediaOp)
{
    this->mediaOp = mediaOp;
}

void MediaLink::update()
{
	mediaOp->update();
	mapperOp.get()->setTexture((gl::Texture)mediaOp.get()->getTexture());
}





