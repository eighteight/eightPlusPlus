/*
 * Cropper.cpp
 *
 *  Created on: May 2, 2011
 *      Author: eight
 */

#include "MapperOp.h"
#include <iostream>
using namespace cinder;
using namespace cinder::app;
using namespace gl;
using namespace std;

MapperOp::MapperOp(){
	MapperOp(0,0,100,200,0.2, 0.4);
}

MapperOp::MapperOp(const int x, const int y, const int width, const int height,  const float xCropFro, const float xCropT)
              :xCropFrom(xCropFro), xCropTo(xCropT) {
	mTrackedPoint = -1;
	mPoints[0] = Vec2f( x, y );
	mPoints[1] = Vec2f( x+ width, y );
	mPoints[2] = Vec2f( x+ width, y + height);
	mPoints[3] = Vec2f( x, y + height);

	for( int i = 0; i < 4; ++i )
		mDestination[i] = toOcv( mPoints[i] );

	for( int i = 0; i < 4; ++i ){
		polyline.push_back( mPoints[i] );
	}
	polyline.push_back( mPoints[0] );
}


void MapperOp::setTexture(Texture texture){
	if (!texture) return;
	this->texture = texture;
	this->textureWidth = this->texture.getWidth();
	this->textureHeight = this->texture.getHeight();

	mSource[0] = cv::Point2f( 0, 0 );
	mSource[1] = cv::Point2f( textureWidth, 0 );
	mSource[2] = cv::Point2f( textureWidth, textureHeight);
	mSource[3] = cv::Point2f( 0, textureHeight);
	updateTransform();
}
Rectf MapperOp::getSourceRect(){
	return Rectf(0, 0, textureWidth, textureHeight);
}

Rectf MapperOp::getDestinationRect(int currentShift){
	if (texture.getTarget() == GL_TEXTURE_2D){
		return Rectf(xCropFrom + currentShift, 0.0f, xCropTo + currentShift, 1.0f );
	} else {
		return Rectf(xCropFrom * textureWidth + currentShift, 0.0f * textureHeight, xCropTo * textureWidth + currentShift, 1.0f * textureHeight);
	}
}

MapperOp::~MapperOp() {
}

void MapperOp::mouseDown( MouseEvent event )
{
	mTrackedPoint = findNearestPt( event.getPos(), MOUSE_TOLERANCE);
}

void MapperOp::mouseUp( MouseEvent event )
{
	mTrackedPoint = -1;
}

void MapperOp::mouseDrag( MouseEvent event )
{
	if( mTrackedPoint == -1 ) return;

	int before = mTrackedPoint == 0 ? 3:mTrackedPoint - 1;
	int after = mTrackedPoint == 3? 0: mTrackedPoint + 1;

	Vec2f v1 = mPoints[before] - event.getPos();
	Vec2f v2 = mPoints[after] - event.getPos();
	float angl = MapperOp::angle(v1, v2);
	if (angl>3.0){
		return;
	}
	mPoints[mTrackedPoint] = event.getPos();

	polyline.getPoints()[mTrackedPoint] = mPoints[mTrackedPoint];
	polyline.getPoints()[4]=mPoints[0];

	updateTransform();
}

int MapperOp::findNearestPt( const Vec2f &aPt, int minDistance )
{
	int result = -1;
	float nearestDist;

	for( size_t i = 0; i < 4; ++i ) {
		float dist = mPoints[i].distance( aPt );
		if( dist < minDistance ) {
			if( ( result == -1 ) || ( dist < nearestDist ) ) {
				result = i;
				nearestDist = dist;
			}
		}
	}

	return result;
}

void MapperOp::draw(){
	if (!texture) return;
	gl::color(Color(1, 1, 1));
	glDisable(GL_TEXTURE_2D);
	gl::pushModelView();
	gl::multModelView(mTransform);

	texture.enableAndBind();
	drawTexturedRect(getSourceRect(), getDestinationRect(shift.x));
	texture.unbind();

	gl::popModelView();
	gl::color(Color(1, 1, 1));
}

void MapperOp::drawTexturedRect( const Rectf &srcRect,  const Rectf &destRec){

	glEnableClientState( GL_VERTEX_ARRAY );
	GLfloat verts[8];
	glVertexPointer( 2, GL_FLOAT, 0, verts );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	GLfloat texCoords[8];
	glTexCoordPointer( 2, GL_FLOAT, 0, texCoords );

	verts[0*2+0] = srcRect.getX2(); texCoords[0*2+0] = destRec.getX2();
	verts[0*2+1] = srcRect.getY1(); texCoords[0*2+1] = destRec.getY1();
	verts[1*2+0] = srcRect.getX1(); texCoords[1*2+0] = destRec.getX1();
	verts[1*2+1] = srcRect.getY1(); texCoords[1*2+1] = destRec.getY1();
	verts[2*2+0] = srcRect.getX2(); texCoords[2*2+0] = destRec.getX2();
	verts[2*2+1] = srcRect.getY2(); texCoords[2*2+1] = destRec.getY2();
	verts[3*2+0] = srcRect.getX1(); texCoords[3*2+0] = destRec.getX1();
	verts[3*2+1] = srcRect.getY2(); texCoords[3*2+1] = destRec.getY2();

	glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );

	glDisableClientState( GL_VERTEX_ARRAY );
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
}

void MapperOp::drawControls(){
	glColor3f( 1.0f, 0.5f, 0.25f );
	for( int i = 0; i < 4; ++i )
	gl::drawSolidCircle( mPoints[i], 4.0f );
	gl::draw(polyline);
}

void MapperOp::updateTransform()
{

	for( int i = 0; i < 4; ++i ) {
		mDestination[i] = toOcv( mPoints[i] );
	}

	cv::Mat warpMatrix = cv::getPerspectiveTransform( mSource, mDestination );

	mTransform.setToIdentity();

	mTransform[0]	= warpMatrix.ptr<double>(0)[0];
	mTransform[4]	= warpMatrix.ptr<double>(0)[1];
	mTransform[12]	= warpMatrix.ptr<double>(0)[2];

	mTransform[1]	= warpMatrix.ptr<double>(1)[0];
	mTransform[5]	= warpMatrix.ptr<double>(1)[1];
	mTransform[13]	= warpMatrix.ptr<double>(1)[2];

	mTransform[3]	= warpMatrix.ptr<double>(2)[0];
	mTransform[7]	= warpMatrix.ptr<double>(2)[1];
	mTransform[15]	= warpMatrix.ptr<double>(2)[2];
}

void MapperOp::setShift(Vec3f shift)
{
	this->shift = shift;
}

float MapperOp::angle(const Vec2f& v1, const Vec2f& v2)
{
	return acos( v1.dot(v2) / (v1.length() * v2.length()) );
}


