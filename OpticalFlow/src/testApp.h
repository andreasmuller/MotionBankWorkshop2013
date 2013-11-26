#pragma once

#include "ofMain.h"
//#include "ofxAutoControlPanel.h"
#include "ofxGui.h"
#include "ofxTimeline.h"
#include "ofxCv.h"

class testApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	
	void exit();
	
	//ofVideoGrabber camera;
	ofVideoPlayer videoPlayer;
	
	ofxCv::FlowFarneback farneback;
	ofxCv::FlowPyrLK pyrLk;
	
	ofxCv::Flow* curFlow;
		
	ofParameter<float> pyrScale;
	ofParameter<int> levels;
	ofParameter<int> winsize;
	ofParameter<int> iterations;
	ofParameter<int> polyN;
	ofParameter<int> polySigma;
	ofParameter<bool> OPTFLOW_FARNEBACK_GAUSSIAN;
	
	ofParameter<bool> useFarneback;
	ofParameter<int> winSize;
	ofParameter<int> maxLevel;
	
	ofParameter<float> maxFeatures;
	ofParameter<float> qualityLevel;
	ofParameter<float> minDistance;
	
	ofxTimeline timeline;
	
	ofxPanel gui;
};

