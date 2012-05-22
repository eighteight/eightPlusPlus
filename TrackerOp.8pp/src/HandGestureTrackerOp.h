/*
 * HandGestureTracker.h
 *
 *  Created on: Apr 17, 2011
 *      Author: eight
 */

#pragma once
#include "ITrackerOp.h"

#include "cinder/Easing.h"
#include "cinder/Utilities.h"
#include "cinder/app/AppBasic.h"

#include "XnOpenNI.h"
#include "XnCppWrapper.h"
#include <XnHash.h>
#include <XnLog.h>

// Header for NITE
#include "XnVNite.h"

#ifndef HANDGESTURETRACKER_H_
#define HANDGESTURETRACKER_H_

#define GESTURE_CLICK "Click"
#define GESTURE_WAVE "Wave"
#define GESTURE_CIRCLE "Circle"

#define SAMPLE_XML_PATH "/Users/eight/repos/nite-bin-macosx-v1.5.2.7/Data/Sample-Tracking.xml"

using namespace ci;
using namespace ci::app;
using namespace std;
using namespace xn;

typedef enum
{
	IN_SESSION,
	NOT_IN_SESSION,
	QUICK_REFOCUS
} SessionState;


#define CHECK_RC(rc, what)                                   \
if (rc != XN_STATUS_OK)                                      \
{                                                            \
        printf("%s failed: %s\n", what, xnGetStatusString(rc));               \
}

#define CHECK_ERRORS(rc, errors, what)		\
	if (rc == XN_STATUS_NO_NODE_PRESENT)	\
	{										\
		XnChar strError[1024];				\
		errors.ToString(strError, 1024);	\
		printf("%s\n", strError);			\
		return (rc);						\
	}


class HandGestureTracker : public ITrackerOp{
public:
	HandGestureTracker();
    ~HandGestureTracker();
	void setup();
	void draw();
	bool isTracking();
	void update();
	Vec3f getShift();
	Vec3f getTargetPosition() const;
	static void XN_CALLBACK_TYPE Gesture_Recognized(GestureGenerator& generator, const XnChar* strGesture, const XnPoint3D* pIDPosition, const XnPoint3D* pEndPosition, void* pCookie);
	static void XN_CALLBACK_TYPE Gesture_Process(GestureGenerator& generator, const XnChar* strGesture, const XnPoint3D* pPosition, XnFloat fProgress, void* pCookie);
	static void XN_CALLBACK_TYPE Hand_Update(HandsGenerator& generator, XnUserID nId, const XnPoint3D* pPosition, XnFloat fTime, void* pCookie);
	static void XN_CALLBACK_TYPE Hand_Create(xn::HandsGenerator& generator, XnUserID nId, const XnPoint3D* pPosition, XnFloat fTime, void* pCookie);
	static void XN_CALLBACK_TYPE Hand_Destroy(xn::HandsGenerator& generator, XnUserID nId, XnFloat fTime, void* pCookie);
	static void XN_CALLBACK_TYPE NoHands(void* UserCxt);
	static void XN_CALLBACK_TYPE FocusProgress(const XnChar* strFocus, const XnPoint3D& ptPosition, XnFloat fProgress, void* UserCxt);
	static void XN_CALLBACK_TYPE SessionStarting(const XnPoint3D& ptPosition, void* UserCxt);
	static void XN_CALLBACK_TYPE SessionEnding(void* UserCxt);

	static void updatePosition(const XnPoint3D position);

	float               easing;
};

#endif /* HANDGESTURETRACKER_H_ */
