#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxTimeline.h"
#include "ofxCv.h"

#define EPSILON FLT_EPSILON

class testApp : public ofBaseApp
{
	public:

		void setup();
		void update();
		void draw();
			
		void keyPressed(int key);
		
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		
		void exit();
		
		ofTrueTypeFont fontSmall;
	
		ofImage imageLeft;
		ofImage imageRight;
	
		bool haveComputed;
	
		bool drawGui;
		ofxPanel gui;
};
