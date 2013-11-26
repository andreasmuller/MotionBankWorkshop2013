
#pragma once

#include "ofMain.h"
#include "OpenGLESHelpers.h"

class MousePosOnPlane
{
	public:


		static ofVec3f getMousePosOnPlane( float _mouseX, float _mouseY, ofVec3f _planeNormal = ofVec3f(0,1,0), ofVec3f _pointOnPlane = ofVec3f(-1,0,0), ofCamera* _camera = NULL );
		static ofVec3f getMousePosOnPlane( float _mouseX, float _mouseY, ofVec3f _planeNormal = ofVec3f(0,1,0), ofVec3f _pointOnPlane = ofVec3f(-1,0,0),
									ofMatrix4x4* _modelViewMatrix = NULL, ofMatrix4x4* _projectionMatrix = NULL, ofRectangle* _viewPort  = NULL );

		static ofVec2f getScreenPosFrom3DPoint( ofVec3f _worldPos, bool _grabMatrices = true );
		
		static float getPlaneDistance( ofPoint* Normal, ofPoint* Point );
		static float rayIntersectPlane( ofPoint* planeNormal, float planeD, ofPoint* rayOrigin, ofPoint* rayDir );
				
	private:
		
};

