/*
 * MediaLink.h
 *
 *  Created on: Dec 13, 2011
 *      Author: eight
 */

#ifndef MEDIALINK_H_
#define MEDIALINK_H_

#include "EightPlusPlusTypes.h"

class MediaLink {
public:
	MediaLink(MediaOpPtr &, MapperOpPtr&);
	virtual ~MediaLink();
	MapperOpPtr getMapperOp() const;
    MediaOpPtr getMediaOp() const;
    void setMapperOp(MapperOpPtr &mapperOp);
    void setMediaOp(MediaOpPtr &mediaOp);
    void update();
private:
    MapperOpPtr mapperOp;
	MediaOpPtr mediaOp;
};

#endif /* MEDIALINK_H_ */
