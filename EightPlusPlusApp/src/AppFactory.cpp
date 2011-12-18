/*
 * AppFactory.cpp
 *
 *  Created on: Apr 23, 2011
 *      Author: eight
 */

#include "AppFactory.h"

using namespace cinder;

AppFactory::AppFactory(const string & resourcePath, const string &xmlFilePath) {
	bool error = false;
	try {
		xml_schema::Properties props;
		props.no_namespace_schema_location ("file://"+resourcePath+"/eightPlusPlus.xsd");
		//props.schema_location ("http://www.w3.org/XML/1998/namespace", "xml.xsd");
		eightPlusPlusApp = parseEightPlusPlusApp(xmlFilePath, 0, props);
	} catch (const xml_schema::Exception& e) {
		cerr << e << endl;
		error = true;
	}
	if (error){
		console()<<"Please provide valid application file. Exiting."<<endl;
		exit(1);
	}
}

AppFactory::~AppFactory() {

}

Executable *AppFactory::createExecutable() {
	Executable* executable = new Executable();
	MediaOpPtr mediaOp = createMediaOp();
	executable->setMediaOp(mediaOp);

	std::vector<MapperOpPtr> mapperOps = createMapperOps();
	executable->setMapperOps(mapperOps);
	executable->setMediaLinks(createMediaLinks(mediaOp, mapperOps));

	std::vector<ITrackerOpPtr> trackerOps = createTrackerOps();
	executable->setTrackerOps(trackerOps);

	//TODO pass a vector there
	executable->setTrackerLinks(createTrackerLinks(trackerOps[0],mapperOps));

	return executable;
}

MediaOpPtr AppFactory::createMediaOp() {
	std::vector<string> mediaFilePaths;
	std::vector<MediaLink*> mediaLinks;
	for (EightPlusPlusApp_t::MediaConstIterator mediumItr(
			eightPlusPlusApp->getMedia().begin()); mediumItr
			!= eightPlusPlusApp->getMedia().end(); ++mediumItr) {
		cout << " Media:" << (*mediumItr).getPath() << " type: "<< (*mediumItr).getType() <<endl;

		mediaFilePaths.push_back((*mediumItr).getPath().get());
	}

	MediaOpPtr mediaOpPtr(new MediaOp());
	mediaOpPtr.get()->setMediaFilePaths(mediaFilePaths);
	return mediaOpPtr;
}

std::vector<MediaLinkPtr> AppFactory::createMediaLinks(MediaOpPtr& mediaOp, std::vector<MapperOpPtr> mapperOps) {
	std::vector<MediaLinkPtr> mediaLinks;
	for (EightPlusPlusApp_t::MediaConstIterator mdmItr(
			eightPlusPlusApp->getMedia().begin()); mdmItr
			!= eightPlusPlusApp->getMedia().end(); ++mdmItr) {
		cout << " Media:" << (*mdmItr).getPath() << " type: "<< (*mdmItr).getType() <<endl;

		Linkable::LinkSequence links = (*mdmItr).getLink();

		for (EightPlusPlusApp_t::LinkConstIterator linkIt(links.begin()); linkIt != links.end(); ++linkIt) {
			cout<<"Media Link "<<(*linkIt).getSource()<< ": "<<(*linkIt).getTarget()<<endl;
			string str=(*linkIt).getTarget();
			size_t pos = str.find("@mapper.")+8;
			string indStr = str.substr (pos);

			int numb;
			istringstream ( indStr ) >> numb;

			mediaLinks.push_back(MediaLinkPtr(new MediaLink(mediaOp, mapperOps.at(numb))));
		}
	}

	return mediaLinks;
}

std::vector<MapperOpPtr> AppFactory::createMapperOps()
{
	std::vector<MapperOpPtr> mappers;
	for (EightPlusPlusApp_t::MapperConstIterator mapperItr(
			eightPlusPlusApp->getMapper().begin()); mapperItr
			!= eightPlusPlusApp->getMapper().end(); ++mapperItr) {
		cout << " Mapper: " << (*mapperItr).getName() << endl;

		 int x = (*mapperItr).getX();
		 int y = (*mapperItr).getY();
		 int w = (*mapperItr).getW();
		 int h = (*mapperItr).getH();

		 float winX0 = (*mapperItr).getWinX0();
		 float winX1 = (*mapperItr).getWinX1();

		 mappers.push_back(MapperOpPtr(new MapperOp(x, y, w, h, winX0, winX1)));
	}

	return mappers;
}

std::vector<ITrackerOpPtr> AppFactory::createTrackerOps()
{
	std::vector<ITrackerOpPtr> trackers;
	if (eightPlusPlusApp->getTracker().present()) {
		cout << " Tracker: " << eightPlusPlusApp->getTracker().get().getType() << endl;
		trackers.push_back(ITrackerOpPtr(TrackerFactory::makeTracker(eightPlusPlusApp->getTracker().get().getType().get())));
	}
	return trackers;
}

std::vector<TrackerLinkPtr> AppFactory::createTrackerLinks(ITrackerOpPtr & trackerOp, std::vector<MapperOpPtr> mapperOps)
{
	std::vector<TrackerLinkPtr> trackerLinks;
	if (eightPlusPlusApp->getTracker().present()) {
		cout << " Tracker: " << eightPlusPlusApp->getTracker().get().getType() << endl;

		Linkable::LinkSequence links = eightPlusPlusApp->getTracker().get().getLink();

		for (EightPlusPlusApp_t::LinkConstIterator linkIt(links.begin()); linkIt != links.end(); ++linkIt) {
			cout<<"Media Link "<<(*linkIt).getSource()<< ": "<<(*linkIt).getTarget()<<endl;
			string str=(*linkIt).getTarget();
			size_t pos = str.find("@mapper.")+8;
			string indStr = str.substr (pos);

			int numb;
			istringstream ( indStr ) >> numb;

			trackerLinks.push_back(TrackerLinkPtr(new TrackerLink(trackerOp, mapperOps.at(numb))));
		}
	}

	return trackerLinks;
}










