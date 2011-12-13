/*
 * Cropper.h
 *
 *  Created on: May 2, 2011
 *      Author: eight
 */

#ifndef CROPPER_H_
#define CROPPER_H_

#define MOUSE_TOLERANCE 5

#include "cinder/Utilities.h"
#include "cinder/app/MouseEvent.h"
#include "cinder/Rect.h"
#include "cinder/gl/Texture.h"

#include "cinder/app/App.h"
#include "CinderOpenCV.h"

using namespace cinder;
using namespace cinder::app;
using namespace cinder::gl;
class MapperOp {
public:
	MapperOp();
	MapperOp(const int x, const int y, const int width, const int height,  const int textureW, const int textureH, const float xCropFro, const float xCropT);
	MapperOp(const int x, const int y, const int width, const int height,  const float xCropFro, const float xCropT);
	virtual ~MapperOp();

	void mouseDown( MouseEvent event );
	void mouseUp( MouseEvent event );

	void mouseDrag( MouseEvent event );

	void setTexture(Texture mTexture);
	void updateTransform();
	void draw();
	void draw(int shift);

private:
	int findNearestPt( const Vec2f &aPt, int minDistance );
	void drawTexturedRect( const Rectf &srcRect,  const Rectf &destRec);

	Rectf getSourceRect();
	Rectf getDestinationRect(int currentShift);

	cv::Point2f	mSource[4];
	cv::Point2f	mDestination[4];
	Matrix44d	mTransform;

	PolyLine<Vec2f>	polyline;
	Vec2f				mPoints[4];
	int					mTrackedPoint;
	int         textureWidth;
	int         textureHeight;
	float       xCropFrom;
	float       xCropTo;
	Texture     texture;

};

#endif /* CROPPER_H_ */
