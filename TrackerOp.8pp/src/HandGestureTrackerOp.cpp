/*
 * HandGestureTracker.cpp
 *
 *  Created on: Apr 17, 2011
 *      Author: eight
 */

#include "HandGestureTrackerOp.h"

XnBoundingBox3D* boundingBox;
xn::GestureGenerator g_GestureGenerator;
xn::HandsGenerator g_HandsGenerator;

// OpenNI objects
xn::Context context;
xn::DepthGenerator g_DepthGenerator;

// NITE objects
XnVSessionManager* g_pSessionManager;

SessionState g_SessionState = NOT_IN_SESSION;

int *shift;
bool startEase;

HandGestureTracker::HandGestureTracker() {
}

HandGestureTracker::~HandGestureTracker() {
}

void HandGestureTracker::setup(int *currentPosition){
	startEase = false;
	shift = currentPosition;
	XnStatus rc = XN_STATUS_OK;
	xn::EnumerationErrors errors;

	// Initialize OpenNI
	rc = context.InitFromXmlFile(SAMPLE_XML_PATH, &errors);
	CHECK_RC(rc, "InitFromXmlFile");

	rc = context.FindExistingNode(XN_NODE_TYPE_DEPTH, g_DepthGenerator);
	CHECK_RC(rc, "Find depth generator");
	rc = context.FindExistingNode(XN_NODE_TYPE_HANDS, g_HandsGenerator);
	CHECK_RC(rc, "Find hands generator");
//
	// Create NITE objects
	g_pSessionManager = new XnVSessionManager;
	rc = g_pSessionManager->Initialize(&context, "Click,Wave", "RaiseHand");
	CHECK_RC(rc, "SessionManager::Initialize");
//
	g_pSessionManager->RegisterSession(NULL, SessionStarting, SessionEnding, FocusProgress);

    XnStatus nRetVal = XN_STATUS_OK;

    nRetVal = g_GestureGenerator.Create(context);
    nRetVal = g_HandsGenerator.Create(context);
    CHECK_RC(nRetVal, "Create Gesture & Hands Generators");
    // Register to callbacks
    XnCallbackHandle h1, h2;
    g_GestureGenerator.RegisterGestureCallbacks(Gesture_Recognized, Gesture_Process, NULL, h1);
    g_HandsGenerator.RegisterHandCallbacks(Hand_Create, Hand_Update, Hand_Destroy, NULL, h2);
    //Make it start generating data
    nRetVal = context.StartGeneratingAll();
    CHECK_RC(nRetVal, "Start Generating All Data");
    nRetVal = g_GestureGenerator.AddGesture(GESTURE_CLICK, boundingBox);
    nRetVal = g_GestureGenerator.AddGesture(GESTURE_WAVE, boundingBox);
}

void HandGestureTracker::update(const double elapsedTime){
	XnStatus nRetVal = context.WaitAnyUpdateAll();
	CHECK_RC(nRetVal, "HandGestureTracker::update");
	g_pSessionManager->Update(&context);

	if (startEase){
		float time = math<float>::clamp( fmod( elapsedTime * TWEEN_SPEED, 1 ) * 1.5f, 0, 1 );
		easing = easeInCirc(time);
		console()<<"EEE:"<<easing<<endl;
		updatePosition(-easing*10);
		if (easing == 1.0f){
			startEase = false;
			easing = 0.0f;
		}
	}
	signalPositionUpdate(*shift);
}


void XN_CALLBACK_TYPE HandGestureTracker::Gesture_Recognized(GestureGenerator& generator, const XnChar* strGesture, const XnPoint3D* pIDPosition, const XnPoint3D* pEndPosition, void* pCookie)
{
	printf("Gesture recognized: %s\n", strGesture);
	g_GestureGenerator.RemoveGesture(strGesture);
	g_HandsGenerator.StartTracking(*pEndPosition);
}

void XN_CALLBACK_TYPE HandGestureTracker::Gesture_Process(GestureGenerator& generator, const XnChar* strGesture, const XnPoint3D* pPosition, XnFloat fProgress, void* pCookie) {}

void XN_CALLBACK_TYPE HandGestureTracker::Hand_Create(xn::HandsGenerator& generator, XnUserID nId, const XnPoint3D* pPosition, XnFloat fTime, void* pCookie)
{
	startEase = false;
    printf("New Hand: %d @ (%f %b)\n", nId, pPosition->X, startEase);
}

void XN_CALLBACK_TYPE HandGestureTracker::Hand_Update(HandsGenerator& generator, XnUserID nId, const XnPoint3D* pPosition, XnFloat fTime, void* pCookie) {
	updatePosition(pPosition->X*0.01);
	startEase = false;
	printf("Update Hand: %d @ (%f %d)\n", nId, pPosition->X, shift);

}
void XN_CALLBACK_TYPE HandGestureTracker::Hand_Destroy(xn::HandsGenerator& generator, XnUserID nId, XnFloat fTime, void* pCookie)
{
	printf("Lost Hand: %d\n", nId);
	startEase = true;
	g_GestureGenerator.AddGesture(GESTURE_CLICK, NULL);
}

// Callback for when the focus is in progress
void XN_CALLBACK_TYPE HandGestureTracker::FocusProgress(const XnChar* strFocus, const XnPoint3D& ptPosition, XnFloat fProgress, void* UserCxt)
{
//	printf("Focus progress: %s @(%f,%f,%f): %f\n", strFocus, ptPosition.X, ptPosition.Y, ptPosition.Z, fProgress);
}
// callback for session start
void XN_CALLBACK_TYPE HandGestureTracker::SessionStarting(const XnPoint3D& ptPosition, void* UserCxt)
{
	printf("Session start: (%f,%f,%f)\n", ptPosition.X, ptPosition.Y, ptPosition.Z);
	g_SessionState = IN_SESSION;
}
// Callback for session end
void XN_CALLBACK_TYPE HandGestureTracker::SessionEnding(void* UserCxt)
{
	printf("Session end\n");
	g_SessionState = NOT_IN_SESSION;
}
void XN_CALLBACK_TYPE HandGestureTracker::NoHands(void* UserCxt)
{
	if (g_SessionState != NOT_IN_SESSION)
	{
		printf("Quick refocus\n");
		g_SessionState = QUICK_REFOCUS;
	}
}

void HandGestureTracker::updatePosition(const float position){
	*shift = *shift - (int)position;
}

