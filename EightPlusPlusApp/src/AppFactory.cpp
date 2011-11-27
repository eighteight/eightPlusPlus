/*
 * AppFactory.cpp
 *
 *  Created on: Apr 23, 2011
 *      Author: eight
 */

#include "AppFactory.h"

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

	executable->setMediaOp(createMediaOp());
	executable->setMapperOps(createMapperOps());
	executable->setTrackerOps(createTrackerOps());

	return executable;
}

MediaOp *AppFactory::createMediaOp() {
	std::vector<string> mediaFilePaths;
	for (EightPlusPlusApp_t::MediaConstIterator mediumItr(
			eightPlusPlusApp->getMedia().begin()); mediumItr
			!= eightPlusPlusApp->getMedia().end(); ++mediumItr) {
		cout << " Media:" << (*mediumItr).getPath() << " type: "<< (*mediumItr).getType() << endl;
		mediaFilePaths.push_back((*mediumItr).getPath().get());

		Linkable::LinkSequence links = (*mediumItr).getLink();

		for (EightPlusPlusApp_t::LinkConstIterator linkIt(links.begin()); linkIt != links.end(); ++linkIt) {
			cout<<"Link "<<(*linkIt).getSource()<<endl;
		}
	}

	MediaOp* mediaOp = new MediaOp();
	mediaOp->setMediaFilePaths(mediaFilePaths);
	return mediaOp;
}

std::vector<MapperOp> *AppFactory::createMapperOps()
{
	std::vector<MapperOp>* mappers = new std::vector<MapperOp>();
	for (EightPlusPlusApp_t::MapperConstIterator mapperItr(
			eightPlusPlusApp->getMapper().begin()); mapperItr
			!= eightPlusPlusApp->getMapper().end(); ++mapperItr) {
		cout << " Mapper: " << (*mapperItr).getName() << endl;

		Linkable::LinkSequence links = (*mapperItr).getLink();

		for (EightPlusPlusApp_t::LinkConstIterator linkIt(links.begin()); linkIt != links.end(); ++linkIt) {
			cout<<"Link "<<(*linkIt).getSource()<<endl;
		}

		 int x = (*mapperItr).getX();
		 int y = (*mapperItr).getY();
		 int w = (*mapperItr).getW();
		 int h = (*mapperItr).getH();

		 float winX0 = (*mapperItr).getWinX0();
		 float winX1 = (*mapperItr).getWinX1();

		 mappers->push_back(MapperOp(x, y, w, h, winX0, winX1));
	}

	return mappers;

}

std::vector<ITrackerOp*> *AppFactory::createTrackerOps()
{
	std::vector<ITrackerOp*>* mappers = new std::vector<ITrackerOp*>();
	std::vector<ITrackerOp*> trackers;
	if (eightPlusPlusApp->getTracker().present()) {
		cout << " Tracker: " << eightPlusPlusApp->getTracker().get().getType() << endl;
		mappers->push_back(TrackerFactory::makeTracker(eightPlusPlusApp->getTracker().get().getType().get()));

		Linkable::LinkSequence links = eightPlusPlusApp->getTracker().get().getLink();

		for (EightPlusPlusApp_t::LinkConstIterator linkItr(links.begin()); linkItr != links.end(); ++linkItr) {
			cout<<"TrackerLink "<<(*linkItr).getTarget()<<endl;
		}
	}
	return mappers;
}








