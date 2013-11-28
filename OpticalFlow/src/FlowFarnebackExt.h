
#pragma once

#include "ofxCv.h"

using namespace ofxCv;
using namespace cv;

class FlowFarnebackExt : public FlowFarneback
{
public:
	
	// ---------------------------------------------------------------------------------
	//
	FlowFarnebackExt()
	{
		drawExtraScaling = 1.0f;
		
		drawStepSize = 2;
		
		minMagToDraw = 0.001f;
			
		lineDrawingStartColor.set(0.0f,0.0f,1.0f);
		lineDrawingEndColor.set(1.0f,0.0f,0.0f);
	}
		
	// ---------------------------------------------------------------------------------
	//
	void setDrawExtraScaling( float _extraScaling )
	{
		drawExtraScaling = _extraScaling;
	}
	
	// ---------------------------------------------------------------------------------
	//
	void setMinMagToDraw( float _minMagToDraw )
	{
		minMagToDraw = _minMagToDraw;
	}
	
	// ---------------------------------------------------------------------------------
	//
	void setLineDrawingColors( ofFloatColor& _start, ofFloatColor& _end )
	{
		lineDrawingStartColor	= _start;
		lineDrawingEndColor	= _end;
	}
	
	// ---------------------------------------------------------------------------------
	//
	void drawFlow(ofRectangle rect)
	{
		ofVec2f offset(rect.x,rect.y);
		ofVec2f scale(rect.width/flow.cols, rect.height/flow.rows);
		
		float minMagToDrawSquared = minMagToDraw * minMagToDraw;
		
		scratchMesh.clear();
		scratchMesh.setMode( OF_PRIMITIVE_LINES );
		
		for(int y = 0; y < flow.rows; y += drawStepSize)
		{
			for(int x = 0; x < flow.cols; x += drawStepSize)
			{
				ofVec2f tmpFlow = getFlowOffset(x, y);
				
				if( tmpFlow.lengthSquared() > minMagToDrawSquared )
				{
					ofVec2f cur = ofVec2f(x, y) * scale + offset;
					
					tmpFlow *= drawExtraScaling;
					
					//ofLine(cur, getFlowPosition(x, y) * scale + offset);
					//ofLine(cur, cur + ((tmpFlow * scale) ) );
					
					scratchMesh.addColor( lineDrawingStartColor );
					scratchMesh.addVertex( cur );
					
					scratchMesh.addColor( lineDrawingEndColor );
					scratchMesh.addVertex( cur + ((tmpFlow * scale) ) );
					
					//ofCircle( cur, 2.0f );
				}
			}
		}
		
		scratchMesh.draw();
		
		//cout << scratchMesh.getNumVertices() << endl;
	}
	

	float drawExtraScaling;
	
	ofFloatColor lineDrawingStartColor;
	ofFloatColor lineDrawingEndColor;
	
	float minMagToDraw;
	
	ofImage scratchImage;
	
	cv::Mat flowSplitXY[2];
	//cv::Mat flowAbsSplitXYTruncated[2];
	
	cv::Mat magnitude, angle;

	ofMesh scratchMesh;
	
	int drawStepSize;
	
};


// http://stackoverflow.com/questions/7693561/opencv-displaying-a-2-channel-image-optical-flow

