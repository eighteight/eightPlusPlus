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
#include "MediaLink.h"

typedef boost::shared_ptr<MediaOp> MediaOpPtr;
typedef boost::shared_ptr<MediaLink> MediaLinkPtr;
typedef boost::shared_ptr<ITrackerOp> ITrackerOpPtr;

class Executable {
public:
	Executable();
	virtual ~Executable();

    void setMediaOp(MediaOpPtr mediaOp);
    void setMapperOps(std::vector<MapperOpPtr>);
    void setTrackerOps(std::vector<ITrackerOpPtr>);
    void setup();
    void update();
    void draw(int);
    void mouseUp(cinder::app::MouseEvent);
    void mouseDown(cinder::app::MouseEvent);
    void mouseDrag(cinder::app::MouseEvent);
    void keyDown(cinder::app::KeyEvent);
    std::vector<MapperOpPtr> getMapperOps() const;
    std::vector<ITrackerOpPtr> getTrackerOps() const;
    MediaOpPtr getMediaOp() const;
    std::vector<MediaLinkPtr> getMediaLinks() const;
    void setMediaLinks(std::vector<MediaLinkPtr> mediaLinks);
private:
    MediaOpPtr mediaOp;
	std::vector<MapperOpPtr> mapperOps;
	std::vector<ITrackerOpPtr> trackerOps;
	std::vector<MediaLinkPtr> mediaLinks;
};

#endif /* EXECUTABLE_H_ */
