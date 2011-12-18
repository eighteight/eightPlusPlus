/*
 * Executable.h
 *
 *  Created on: Nov 26, 2011
 *      Author: eight
 */

#ifndef EXECUTABLE_H_
#define EXECUTABLE_H_

#include "TrackerFactory.h"
#include "MediaLink.h"
#include "TrackerLink.h"
#include "EightPlusPlusTypes.h"
typedef boost::shared_ptr<MediaLink> MediaLinkPtr;
typedef boost::shared_ptr<TrackerLink> TrackerLinkPtr;
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
    std::vector<TrackerLinkPtr> getTrackerLinks() const;
    void setTrackerLinks(std::vector<TrackerLinkPtr> trackerLinks);
private:
    MediaOpPtr mediaOp;
	std::vector<MapperOpPtr> mapperOps;
	std::vector<ITrackerOpPtr> trackerOps;
	std::vector<MediaLinkPtr> mediaLinks;
	std::vector<TrackerLinkPtr> trackerLinks;
};

#endif /* EXECUTABLE_H_ */
