/*
 *  OpenGLESHelpers.cpp
 *  GLSprite
 *
 *  Created by Andreas Muller on 30/04/2008.
 *  Copyright 2008 Nanika. All rights reserved.
 *
 */


#import "OpenGLESHelpers.h"

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
void gluES::gluPerspective(GLfloat fovy, GLfloat aspect, GLfloat zNear, GLfloat zFar)
{
	GLfloat xmin, xmax, ymin, ymax;
	
	ymax = zNear * tan(fovy * M_PI / 360.0);
	ymin = -ymax;
	xmin = ymin * aspect;
	xmax = ymax * aspect;
	
	
	glFrustum(xmin, xmax, ymin, ymax, zNear, zFar);
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
void gluES::gluOrtho2D(GLfloat left, GLfloat right, GLfloat bottom, GLfloat top)
{
    glOrtho(left, right, bottom, top, -1.0f, 1.0f);
}



// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Make m an identity matrix
//

void gluES::__gluMakeIdentityf(GLfloat m[16])
{
    m[0+4*0] = 1; m[0+4*1] = 0; m[0+4*2] = 0; m[0+4*3] = 0;
    m[1+4*0] = 0; m[1+4*1] = 1; m[1+4*2] = 0; m[1+4*3] = 0;
    m[2+4*0] = 0; m[2+4*1] = 0; m[2+4*2] = 1; m[2+4*3] = 0;
    m[3+4*0] = 0; m[3+4*1] = 0; m[3+4*2] = 0; m[3+4*3] = 1;
}

#define __glPi 3.14159265358979323846

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
void gluES::normalize(float v[3])
{
    float r;
	
    r = sqrt( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] );
    if (r == 0.0) return;
	
    v[0] /= r;
    v[1] /= r;
    v[2] /= r;
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
void gluES::cross(float v1[3], float v2[3], float result[3])
{
    result[0] = v1[1]*v2[2] - v1[2]*v2[1];
    result[1] = v1[2]*v2[0] - v1[0]*v2[2];
    result[2] = v1[0]*v2[1] - v1[1]*v2[0];
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
void gluES::gluLookAt(GLfloat eyex, GLfloat eyey, GLfloat eyez, 
			   GLfloat centerx, GLfloat centery, GLfloat centerz, 
			   GLfloat upx, GLfloat upy, GLfloat upz)
{
    float forward[3], side[3], up[3];
    GLfloat m[4][4];
	
    forward[0] = centerx - eyex;
    forward[1] = centery - eyey;
    forward[2] = centerz - eyez;
	
    up[0] = upx;
    up[1] = upy;
    up[2] = upz;
	
    normalize(forward);
	
    /* Side = forward x up */
    cross(forward, up, side);
    normalize(side);
	
    /* Recompute up as: up = side x forward */
    cross(side, forward, up);
	
    __gluMakeIdentityf(&m[0][0]);
    m[0][0] = side[0];
    m[1][0] = side[1];
    m[2][0] = side[2];
	
    m[0][1] = up[0];
    m[1][1] = up[1];
    m[2][1] = up[2];
	
    m[0][2] = -forward[0];
    m[1][2] = -forward[1];
    m[2][2] = -forward[2];
	
    glMultMatrixf(&m[0][0]);
    glTranslatef(-eyex, -eyey, -eyez);
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
void gluES::__gluMultMatrixVecf(const GLfloat matrix[16], const GLfloat in[4],
								GLfloat out[4])
{
    int i;
	
    for (i=0; i<4; i++) {
		out[i] = 
	    in[0] * matrix[0*4+i] +
	    in[1] * matrix[1*4+i] +
	    in[2] * matrix[2*4+i] +
	    in[3] * matrix[3*4+i];
    }
}


// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
// Invert 4x4 matrix.
// Contributed by David Moore (See Mesa bug #6748)
//
int gluES::__gluInvertMatrixf(const GLfloat m[16], GLfloat invOut[16])
{
    float inv[16], det;
    int i;
	
    inv[0] =   m[5]*m[10]*m[15] - m[5]*m[11]*m[14] - m[9]*m[6]*m[15]
	+ m[9]*m[7]*m[14] + m[13]*m[6]*m[11] - m[13]*m[7]*m[10];
    inv[4] =  -m[4]*m[10]*m[15] + m[4]*m[11]*m[14] + m[8]*m[6]*m[15]
	- m[8]*m[7]*m[14] - m[12]*m[6]*m[11] + m[12]*m[7]*m[10];
    inv[8] =   m[4]*m[9]*m[15] - m[4]*m[11]*m[13] - m[8]*m[5]*m[15]
	+ m[8]*m[7]*m[13] + m[12]*m[5]*m[11] - m[12]*m[7]*m[9];
    inv[12] = -m[4]*m[9]*m[14] + m[4]*m[10]*m[13] + m[8]*m[5]*m[14]
	- m[8]*m[6]*m[13] - m[12]*m[5]*m[10] + m[12]*m[6]*m[9];
    inv[1] =  -m[1]*m[10]*m[15] + m[1]*m[11]*m[14] + m[9]*m[2]*m[15]
	- m[9]*m[3]*m[14] - m[13]*m[2]*m[11] + m[13]*m[3]*m[10];
    inv[5] =   m[0]*m[10]*m[15] - m[0]*m[11]*m[14] - m[8]*m[2]*m[15]
	+ m[8]*m[3]*m[14] + m[12]*m[2]*m[11] - m[12]*m[3]*m[10];
    inv[9] =  -m[0]*m[9]*m[15] + m[0]*m[11]*m[13] + m[8]*m[1]*m[15]
	- m[8]*m[3]*m[13] - m[12]*m[1]*m[11] + m[12]*m[3]*m[9];
    inv[13] =  m[0]*m[9]*m[14] - m[0]*m[10]*m[13] - m[8]*m[1]*m[14]
	+ m[8]*m[2]*m[13] + m[12]*m[1]*m[10] - m[12]*m[2]*m[9];
    inv[2] =   m[1]*m[6]*m[15] - m[1]*m[7]*m[14] - m[5]*m[2]*m[15]
	+ m[5]*m[3]*m[14] + m[13]*m[2]*m[7] - m[13]*m[3]*m[6];
    inv[6] =  -m[0]*m[6]*m[15] + m[0]*m[7]*m[14] + m[4]*m[2]*m[15]
	- m[4]*m[3]*m[14] - m[12]*m[2]*m[7] + m[12]*m[3]*m[6];
    inv[10] =  m[0]*m[5]*m[15] - m[0]*m[7]*m[13] - m[4]*m[1]*m[15]
	+ m[4]*m[3]*m[13] + m[12]*m[1]*m[7] - m[12]*m[3]*m[5];
    inv[14] = -m[0]*m[5]*m[14] + m[0]*m[6]*m[13] + m[4]*m[1]*m[14]
	- m[4]*m[2]*m[13] - m[12]*m[1]*m[6] + m[12]*m[2]*m[5];
    inv[3] =  -m[1]*m[6]*m[11] + m[1]*m[7]*m[10] + m[5]*m[2]*m[11]
	- m[5]*m[3]*m[10] - m[9]*m[2]*m[7] + m[9]*m[3]*m[6];
    inv[7] =   m[0]*m[6]*m[11] - m[0]*m[7]*m[10] - m[4]*m[2]*m[11]
	+ m[4]*m[3]*m[10] + m[8]*m[2]*m[7] - m[8]*m[3]*m[6];
    inv[11] = -m[0]*m[5]*m[11] + m[0]*m[7]*m[9] + m[4]*m[1]*m[11]
	- m[4]*m[3]*m[9] - m[8]*m[1]*m[7] + m[8]*m[3]*m[5];
    inv[15] =  m[0]*m[5]*m[10] - m[0]*m[6]*m[9] - m[4]*m[1]*m[10]
	+ m[4]*m[2]*m[9] + m[8]*m[1]*m[6] - m[8]*m[2]*m[5];
	
    det = m[0]*inv[0] + m[1]*inv[4] + m[2]*inv[8] + m[3]*inv[12];
    if (det == 0)
        return GL_FALSE;
	
    det = 1.0f / det;
	
    for (i = 0; i < 16; i++)
        invOut[i] = inv[i] * det;
	
    return GL_TRUE;
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
void gluES::__gluMultMatricesf(const GLfloat a[16], const GLfloat b[16],
							   GLfloat r[16])
{
    int i, j;
	
    for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			r[i*4+j] = 
			a[i*4+0]*b[0*4+j] +
			a[i*4+1]*b[1*4+j] +
			a[i*4+2]*b[2*4+j] +
			a[i*4+3]*b[3*4+j];
		}
    }
}


// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
GLint gluES::gluProject(GLfloat objx, GLfloat objy, GLfloat objz, 
						 const GLfloat modelMatrix[16], 
						 const GLfloat projMatrix[16],
						 const GLint viewport[4],
						 GLfloat *winx, GLfloat *winy, GLfloat *winz)
{
    float in[4];
    float out[4];
	
    in[0]=objx;
    in[1]=objy;
    in[2]=objz;
    in[3]=1.0;
    __gluMultMatrixVecf(modelMatrix, in, out);
    __gluMultMatrixVecf(projMatrix, out, in);
    if (in[3] == 0.0) return(GL_FALSE);
    in[0] /= in[3];
    in[1] /= in[3];
    in[2] /= in[3];
    /* Map x, y and z to range 0-1 */
    in[0] = in[0] * 0.5f + 0.5f;
    in[1] = in[1] * 0.5f + 0.5f;
    in[2] = in[2] * 0.5f + 0.5f;
	
    /* Map x,y to viewport */
    in[0] = in[0] * viewport[2] + viewport[0];
    in[1] = in[1] * viewport[3] + viewport[1];
	
    *winx=in[0];
    *winy=in[1];
    *winz=in[2];
    return(GL_TRUE);
}

// ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//
GLint gluES::gluUnProject(GLfloat winx, GLfloat winy, GLfloat winz,
						   const GLfloat modelMatrix[16], 
						   const GLfloat projMatrix[16],
						   const GLint viewport[4],
						   GLfloat *objx, GLfloat *objy, GLfloat *objz)
{
    float finalMatrix[16];
    float in[4];
    float out[4];
	
    __gluMultMatricesf(modelMatrix, projMatrix, finalMatrix);
    if (!__gluInvertMatrixf(finalMatrix, finalMatrix)) return(GL_FALSE);
	
    in[0]=winx;
    in[1]=winy;
    in[2]=winz;
    in[3]=1.0;
	
    /* Map x and y from window coordinates */
    in[0] = (in[0] - viewport[0]) / viewport[2];
    in[1] = (in[1] - viewport[1]) / viewport[3];
	
    /* Map to range -1 to 1 */
    in[0] = in[0] * 2 - 1;
    in[1] = in[1] * 2 - 1;
    in[2] = in[2] * 2 - 1;
	
    __gluMultMatrixVecf(finalMatrix, in, out);
    if (out[3] == 0.0) return(GL_FALSE);
    out[0] /= out[3];
    out[1] /= out[3];
    out[2] /= out[3];
    *objx = out[0];
    *objy = out[1];
    *objz = out[2];
    return(GL_TRUE);
}

