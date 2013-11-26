
#include "MousePosOnPlane.h"


// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
ofVec3f MousePosOnPlane::getMousePosOnPlane( float _mouseX, float _mouseY, ofVec3f _planeNormal, ofVec3f _pointOnPlane, ofCamera* _camera )
{
	ofMatrix4x4 modelViewMat;
	ofMatrix4x4 projectionMat;
	ofRectangle viewport;
	
	if( _camera != NULL )
	{
		modelViewMat  = _camera->getModelViewMatrix();
		projectionMat = _camera->getProjectionMatrix();
		viewport = ofGetCurrentViewport();
		
		return getMousePosOnPlane(  _mouseX, _mouseY, _planeNormal, _pointOnPlane, &modelViewMat, &projectionMat, &viewport );
	}
	else
	{
		return getMousePosOnPlane(  _mouseX, _mouseY, _planeNormal, _pointOnPlane, NULL, NULL, NULL );
	}
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
ofVec3f MousePosOnPlane::getMousePosOnPlane( float _mouseX, float _mouseY, ofVec3f _planeNormal, ofVec3f _pointOnPlane,
						   ofMatrix4x4* _modelViewMatrix, ofMatrix4x4* _projectionMatrix, ofRectangle* _viewPort )
{
	ofMatrix4x4 modelViewMat;
	ofMatrix4x4 projectionMat;
	GLint viewport[4];
	
	if( _modelViewMatrix == NULL ) { glGetFloatv(GL_MODELVIEW_MATRIX, modelViewMat.getPtr() ); }
	else { modelViewMat.set( *_modelViewMatrix ); }
	
	if( _projectionMatrix == NULL ) { glGetFloatv(GL_PROJECTION_MATRIX, projectionMat.getPtr() );	 }
	else { projectionMat.set( *_projectionMatrix ); }
	
	
	if( _viewPort == NULL )
	{
		glGetIntegerv(GL_VIEWPORT, viewport);
	}
	else
	{
		viewport[0] = _viewPort->x;
		viewport[1] = _viewPort->y;
		viewport[2] = _viewPort->width;
		viewport[3] = _viewPort->height;
	}
	
	float dx, dy, dz = 0.0;
	ofVec3f mouseRayPosition;
	ofVec3f mouseRayVector;
	
	int ry = viewport[3] - _mouseY - 1;
	
	gluES::gluUnProject( _mouseX, ry, 0.0,
						modelViewMat.getPtr(), projectionMat.getPtr(), viewport,
						&mouseRayPosition.x, &mouseRayPosition.y, &mouseRayPosition.z);
	
	gluES::gluUnProject( _mouseX, ry, 1.0,
						modelViewMat.getPtr(), projectionMat.getPtr(), viewport,
						&mouseRayVector.x, &mouseRayVector.y, &mouseRayVector.z);
	
	mouseRayVector -= mouseRayPosition;
	mouseRayVector.normalize();
	
	float planeDistance = getPlaneDistance( &_planeNormal, &_pointOnPlane );
	float tmpDist = rayIntersectPlane( &_planeNormal, planeDistance, &mouseRayPosition, &mouseRayVector );
	
	return mouseRayPosition + (mouseRayVector * tmpDist);

	
}
/*
// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
ofVec3f MousePosOnPlane::getMousePosOnPlane( float _mouseX, float _mouseY, ofVec3f _planeNormal, ofVec3f _pointOnPlane, bool _grabMatrices )
{
	GLfloat tmpModelView[16];
	GLfloat tmpProjection[16];
	GLint tmpViewport[4];	
	
	if( _grabMatrices)
	{
		glGetFloatv(GL_MODELVIEW_MATRIX, tmpModelView);
		glGetFloatv(GL_PROJECTION_MATRIX, tmpProjection);
		glGetIntegerv(GL_VIEWPORT, tmpViewport);
	}
	
	ofMatrix4x4 modelViewMat;
	ofMatrix4x4 projectionMat;
	//ofMatrix4x4 viewport;
	
	//cout << "viewport: " << tmpViewport[0] << ", " << tmpViewport[1] << ", " << tmpViewport[2] << ", " << tmpViewport[3] << endl;
	
}
*/



// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
ofVec2f MousePosOnPlane::getScreenPosFrom3DPoint( ofVec3f _worldPos, bool _grabMatrices )
{
	GLfloat tmpModelView[16];
	GLfloat tmpProjection[16];
	GLint tmpViewport[4];
	
	if( _grabMatrices )
	{
		glGetFloatv(GL_MODELVIEW_MATRIX, tmpModelView);
		glGetFloatv(GL_PROJECTION_MATRIX, tmpProjection);
		glGetIntegerv(GL_VIEWPORT, tmpViewport);
	}

	float resultX = 0.0f;
	float resultY = 0.0f;
	float resultZ = 0.0f;
	
	gluES::gluProject( _worldPos.x, _worldPos.y, _worldPos.z,
						tmpModelView, tmpProjection, tmpViewport,
						&resultX, &resultY, &resultZ );

	return ofVec2f(resultX,resultY);		
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
float MousePosOnPlane::getPlaneDistance( ofPoint* Normal, ofPoint* Point )
{
	// Basically, the negated dot product of the normal of the plane and the point. (More about the dot product in another tutorial)	
	
	float distance = 0;		// This variable holds the distance from the plane to the origin												
	distance = - ((Normal->x * Point->x) + (Normal->y * Point->y) + (Normal->z * Point->z));
	return distance;
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
float MousePosOnPlane::rayIntersectPlane( ofPoint* planeNormal, float planeD, ofPoint* rayOrigin, ofPoint* rayDir )
{
    float denom = (float)(planeNormal->x * rayDir->x + 
						  planeNormal->y * rayDir->y + 
						  planeNormal->z * rayDir->z);
	
    // if denom == 0 ray does not intersect the plane else
	return  (float)-(planeNormal->x * rayOrigin->x + 
					 planeNormal->y * rayOrigin->y +
					 planeNormal->z * rayOrigin->z + planeD) / denom;
}
