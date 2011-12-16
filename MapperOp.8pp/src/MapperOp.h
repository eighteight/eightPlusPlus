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

class MapperOp {
public:
	MapperOp();
	MapperOp(const int x, const int y, const int width, const int height,  const int textureW, const int textureH, const float xCropFro, const float xCropT);
	MapperOp(const int x, const int y, const int width, const int height,  const float xCropFro, const float xCropT);
	virtual ~MapperOp();

	void mouseDown(cinder::app::MouseEvent event );
	void mouseUp(cinder::app::MouseEvent event );

	void mouseDrag(cinder::app::MouseEvent event );

	void setTexture(cinder::gl::Texture);
	void updateTransform();
	void draw();
	void draw(int shift);

private:
	int findNearestPt( const cinder::Vec2f &aPt, int minDistance );
	void drawTexturedRect( const cinder::Rectf &srcRect,  const cinder::Rectf &destRec);

	cinder::Rectf getSourceRect();
	cinder::Rectf getDestinationRect(int currentShift);

	cv::Point2f	mSource[4];
	cv::Point2f	mDestination[4];
	cinder::Matrix44d	mTransform;

	cinder::PolyLine<cinder::Vec2f>	polyline;
	cinder::Vec2f				mPoints[4];
	int					mTrackedPoint;
	int         textureWidth;
	int         textureHeight;
	float       xCropFrom;
	float       xCropTo;
	cinder::gl::Texture     texture;

};

#endif /* CROPPER_H_ */
