#pragma once

#include "ofMain.h"
#include "Utils/ofEasyCamExt.h"

#include "Track.h"

class testApp : public ofBaseApp
{
	public:
	
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
		Track<ofVec3f> positionTrack;

		int maxPositionHistoryLength;
		deque<ofVec3f> positionHistory;
	
		ofEasyCamExt camera;
	
		ofCamera recordingCameraLeft;
		ofCamera recordingCameraRight;
		ofCamera recordingCameraCenter;
};
