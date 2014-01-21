#pragma once

#include "ofMain.h"
//#include "ofxAutoControlPanel.h"
#include "ofxGui.h"
//#include "ofxTimeline.h"
#include "ofxCv.h"
#include "FlowFarnebackExt.h"

#include "TrackedPoint2D.h"
#include "TrackedPoint2DCloseUpView.h"

class testApp : public ofBaseApp
{
public:
	void setup();
	void update();
	void draw();
	
	ofRectangle getBoundingBox( vector< TrackedPoint2D* >& _points );
	
	void keyPressed(int key);
	
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	
	void exit();
	
	//ofVideoGrabber camera;
	//ofVideoPlayer videoPlayer;
	
	bool isPlaying;
	
	vector<string> filenames;
	int currentIndex;
	
	ofImage currentImage;
	
	FlowFarnebackExt farneback;
	//ofxCv::FlowPyrLK pyrLk;
	
	ofxCv::Flow* curFlow;

	ofParameter<bool> doOpticalFlow;
	ofParameter<float> pyrScale;
	ofParameter<int> levels;
	ofParameter<int> winsize;
	ofParameter<int> iterations;
	ofParameter<int> polyN;
	ofParameter<int> polySigma;
	ofParameter<bool> OPTFLOW_FARNEBACK_GAUSSIAN;
	ofParameter<bool> drawFlow;
	
	vector< TrackedPoint2D* > trackedPoints;
	vector< TrackedPoint2DCloseUpView* > trackedPointCloseUpViews;
	ofRectangle pointsBoundingBox;
	
	//ofParameter<bool> useFarneback;

	//ofParameter<int> winSize;
	//ofParameter<int> maxLevel;
	//ofParameter<float> maxFeatures;
	//ofParameter<float> qualityLevel;
	//ofParameter<float> minDistance;
	
	ofParameter<float> flowDrawingScale;
	ofParameter<int> flowDrawingStep;
	
	string outputDir;
	
	ofTrueTypeFont fontSmall;
	
	//ofxTimeline timeline;
		
	bool drawGui;
	ofxPanel gui;
};

