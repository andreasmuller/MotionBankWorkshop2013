
/*
 *  OpenGLESHelpers.h
 *  GLSprite
 *
 *  Created by Andreas Muller on 30/04/2008.
 *  Copyright 2008 Nanika. All rights reserved.
 *
 */


#ifndef __A_OPENGL_ES_HELPERS_H
#define __A_OPENGL_ES_HELPERS_H


#include "ofMain.h"

#import <math.h>


class gluES
{
	public:

		static void gluPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar);
			
		static void gluOrtho2D(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top);
			
		static void __gluMakeIdentityf(GLfloat m[16]);
			
		static void normalize(float v[3]);
			
		static void cross(float v1[3], float v2[3], float result[3]);
			
			static void gluLookAt(GLfloat eyex, GLfloat eyey, GLfloat eyez, 
								  GLfloat centerx, GLfloat centery, GLfloat centerz, 
								  GLfloat upx, GLfloat upy, GLfloat upz);
			
		static void __gluMultMatrixVecf(const GLfloat matrix[16], const GLfloat in[4],GLfloat out[4]);
			
		static int __gluInvertMatrixf(const GLfloat m[16], GLfloat invOut[16]);
			
		static void __gluMultMatricesf(const GLfloat a[16], const GLfloat b[16], GLfloat r[16]);
		
		static GLint gluProject(GLfloat objx, GLfloat objy, GLfloat objz, 
								const GLfloat modelMatrix[16], 
								const GLfloat projMatrix[16],
								const GLint viewport[4],
								GLfloat *winx, GLfloat *winy, GLfloat *winz);
		
		
		static GLint gluUnProject(GLfloat winx, GLfloat winy, GLfloat winz,
								  const GLfloat modelMatrix[16], 
								  const GLfloat projMatrix[16],
								  const GLint viewport[4],
								  GLfloat *objx, GLfloat *objy, GLfloat *objz);
	
	
	
};


#endif //__A_OPENGL_ES_HELPERS_H