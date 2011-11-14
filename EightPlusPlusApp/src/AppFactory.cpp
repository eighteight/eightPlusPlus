/*
 * AppFactory.cpp
 *
 *  Created on: Apr 23, 2011
 *      Author: eight
 */

#include "AppFactory.h"

AppFactory::AppFactory(const string &xmlFilePath) {

	try {
		auto_ptr<EightPlusPlusApp_t> revolverApp = parseEightPlusPlusApp(xmlFilePath);
		for (EightPlusPlusApp_t::MediaConstIterator medium(
				revolverApp->getMedia().begin()); medium
				!= revolverApp->getMedia().end(); ++medium) {
			cout << " Media:" << (*medium).getPath() << " type: "<< (*medium).getType() << endl;
			mediaFilePaths.push_back((*medium).getPath().get());
		}

		for (EightPlusPlusApp_t::MapperConstIterator mapper(
				revolverApp->getMapper().begin()); mapper
				!= revolverApp->getMapper().end(); ++mapper) {
			cout << " Mapper: " << (*mapper).getName() << endl;

			Linkable::LinkSequence links = (*mapper).getLink();

			for (EightPlusPlusApp_t::LinkConstIterator linkIt(links.begin()); linkIt != links.end(); ++linkIt) {
				cout<<"Link "<<(*linkIt).getSource()<<endl;
			}

			 int x = (*mapper).getX();
			 int y = (*mapper).getY();
			 int w = (*mapper).getW();
			 int h = (*mapper).getH();

			 float winX0 = (*mapper).getWinX0();
			 float winX1 = (*mapper).getWinX1();

			 MapperOp mOp = MapperOp(x, y, w, h, winX0, winX1);

			for (EightPlusPlusApp_t::LinkConstIterator link(
					(*mapper).getLink().begin()); link
							!= (*mapper).getLink().end(); ++link){
				//mOp.setMovie(link.getSource());
			}
			 mappers.push_back(mOp);
		}

		if (revolverApp->getTracker().present()) {
			cout << " Tracker: " << revolverApp->getTracker().get().getType() << endl;
			trackers.push_back(TrackerFactory::makeTracker(revolverApp->getTracker().get().getType().get()));
		}
	} catch (const xml_schema::Exception& e) {
		cerr << e << endl;
	}
}

AppFactory::~AppFactory() {
	if (!mediaFilePaths.empty()){
		mediaFilePaths.clear();
	}

	if (!mappers.empty()){
		mappers.clear();
	}
}
