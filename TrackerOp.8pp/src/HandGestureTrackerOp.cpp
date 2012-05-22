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
Vec3f mTrackPosition;
bool tracked;
HandGestureTracker::HandGestureTracker() {
}

HandGestureTracker::~HandGestureTracker() {
}

void HandGestureTracker::setup(){
	tracked = false;
	shift = 0;
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
	rc = g_pSessionManager->Initialize(&context, "Click,Wave,Circle", "RaiseHand");
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
    nRetVal = g_GestureGenerator.AddGesture(GESTURE_CIRCLE, boundingBox);
}

void HandGestureTracker::update(){
	XnStatus nRetVal = context.WaitAnyUpdateAll();
	CHECK_RC(nRetVal, "HandGestureTracker::update");
	g_pSessionManager->Update(&context);

//	if (tracking){
//		float time = math<float>::clamp( fmod( elapsedTime * TWEEN_SPEED, 1 ) * 1.5f, 0, 1 );
//		easing = easeInCirc(time);
//		//updatePosition(-easing*10);
//		if (easing == 1.0f){
//			tracking = false;
//			easing = 0.0f;
//		}
//	}
}

void HandGestureTracker::draw() {
	gl::setMatricesWindow( getWindowSize() );
	// this pair of lines is the standard way to clear the screen in OpenGL
	gl::clear( Color( 0.1f, 0.1f, 0.1f ) );

	// We'll set the color to an orange color
	glColor3f( 1.0f, 0.5f, 0.25f );

	// now tell OpenGL we've got a series of points it should draw lines between

	gl::drawSolidCircle( Vec2f( mTrackPosition.x, mTrackPosition.y ), 10.0f );
	//glVertex2f( Vec2f(position.X, position.Y) );

	// tell OpenGL to actually draw the lines now
	glEnd();
}


void XN_CALLBACK_TYPE HandGestureTracker::Gesture_Recognized(GestureGenerator& generator, const XnChar* strGesture, const XnPoint3D* pIDPosition, const XnPoint3D* pEndPosition, void* pCookie)
{
	printf("Gesture recognized: %s\n", strGesture);
	g_GestureGenerator.RemoveGesture(strGesture);
	char szKey[] = GESTURE_CLICK;
	if (strcmp (strGesture,szKey) == 0){
		tracked = true;
		g_GestureGenerator.AddGesture(GESTURE_WAVE, NULL);
	} else {
		tracked = false;
		g_GestureGenerator.AddGesture(GESTURE_CLICK, NULL);
	}

	g_HandsGenerator.StartTracking(*pEndPosition);
}

void XN_CALLBACK_TYPE HandGestureTracker::Gesture_Process(GestureGenerator& generator, const XnChar* strGesture, const XnPoint3D* pPosition, XnFloat fProgress, void* pCookie) {}

void XN_CALLBACK_TYPE HandGestureTracker::Hand_Create(xn::HandsGenerator& generator, XnUserID nId, const XnPoint3D* pPosition, XnFloat fTime, void* pCookie)
{
    printf("New Hand: %d @ (%f %b)\n", nId, pPosition->X);
}

void XN_CALLBACK_TYPE HandGestureTracker::Hand_Update(HandsGenerator& generator, XnUserID nId, const XnPoint3D* pPosition, XnFloat fTime, void* pCookie) {
	XnPoint3D       point;
	g_DepthGenerator.ConvertRealWorldToProjective(1, pPosition, &point);
	mTrackPosition = Vec3f(point.X, point.Y, point.Z);
	updatePosition(point);
	tracked = true;
}
void XN_CALLBACK_TYPE HandGestureTracker::Hand_Destroy(xn::HandsGenerator& generator, XnUserID nId, XnFloat fTime, void* pCookie)
{
	printf("Lost Hand: %d\n", nId);
	tracked = false;
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

Vec3f HandGestureTracker::getShift()
{
	return Vec3f((float)*shift,0.0f, 0.0f);
}

void HandGestureTracker::updatePosition(const XnPoint3D position){
	shift = shift - (int)position.X;
}

Vec3f HandGestureTracker::getTargetPosition() const
{
	return Vec3f(mTrackPosition.x,mTrackPosition.y,mTrackPosition.z);
}

bool HandGestureTracker::isTracking()
{
	return tracked;
}

