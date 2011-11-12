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
#include <string>

#include "eightPlusPlus.hxx"

#include "MapperOp.h"

using namespace cinder;

class AppFactory {
public:
	AppFactory(){};
	AppFactory(const string &xmlFilePath);

	virtual ~AppFactory();

	std::vector<string> mediaFilePaths;

	std::vector<MapperOp> mappers;
	std::vector<ITrackerOp*> trackers;
};

#endif /* XMLCONFIG_H_ */
