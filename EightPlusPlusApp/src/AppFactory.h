/*
 * XmlConfig.h
 *
 *  Created on: Apr 23, 2011
 *      Author: eight
 */

#ifndef XMLCONFIG_H_
#define XMLCONFIG_H_

#include "cinder/Utilities.h"
#include <boost/algorithm/string.hpp>
#include "TrackerFactory.h"
#include "Executable.h"
#include <string>

#include "eightPlusPlus.hxx"

#include "MapperOp.h"
#include "MediaOp.h"
#include "TrackerFactory.h"

using namespace cinder;

class AppFactory {
public:
	AppFactory(){};
	AppFactory(const string & appPath, const string &xmlFilePath);

	Executable* createExecutable();

	virtual ~AppFactory();

    auto_ptr<EightPlusPlusApp_t> eightPlusPlusApp;

private:
	MediaOp* createMediaOp();
	std::vector<MapperOp>* createMapperOps();
	std::vector<ITrackerOp*>* createTrackerOps();
};

#endif /* XMLCONFIG_H_ */
