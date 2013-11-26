#include "testApp.h"

using namespace ofxCv;
using namespace cv;

// ---------------------------------------------------------------------------------------------------
//
void testApp::setup()
{
	//camera.initGrabber(320, 240);

	videoPlayer.loadMovie( "RosCenterShort.mp4" /*"IMG_3965.mov"*/ );
	videoPlayer.setLoopState( OF_LOOP_NORMAL );
	//videoPlayer.play();
	
	/*
	panel.setup(250, 800);
	
	panel.addPanel("Optical Flow");
	
	panel.addSlider("pyrScale", .5, 0, 1);
	panel.addSlider("levels", 4, 1, 8, true);
	panel.addSlider("winsize", 8, 4, 64, true);
	panel.addSlider("iterations", 2, 1, 8, true);
	panel.addSlider("polyN", 7, 5, 10, true);
	panel.addSlider("polySigma", 1.5, 1.1, 2);
	panel.addToggle("OPTFLOW_FARNEBACK_GAUSSIAN", false);
	
	panel.addToggle("useFarneback", true);
	panel.addSlider("winSize", 32, 4, 64, true);
	panel.addSlider("maxLevel", 3, 0, 8, true);
	
	panel.addSlider("maxFeatures", 200, 1, 1000);
	panel.addSlider("qualityLevel", 0.01, 0.001, .02);
	panel.addSlider("minDistance", 4, 1, 16);
	 */
	 
	gui.setup("Flow Test");

	gui.add( pyrScale.set("pyrScale", .5, 0, 1) );
	gui.add( levels.set("levels", 4, 1, 8) );
	gui.add( winsize.set("winsize", 8, 4, 64) );
	gui.add( iterations.set("iterations", 2, 1, 8) );
	gui.add( polyN.set("polyN", 7, 5, 10) );
	gui.add( polySigma.set("polySigma", 1.5, 1.1, 2) );
	gui.add( OPTFLOW_FARNEBACK_GAUSSIAN.set("OPTFLOW_FARNEBACK_GAUSSIAN", true ) );

	gui.add( useFarneback.set("useFarneback", true ) );
	gui.add( winSize.set("winSize", 32, 4, 64 ) );
	gui.add( maxLevel.set("maxLevel", 3, 0, 8 ) );
	gui.add( maxFeatures.set("maxFeatures", 200, 1, 1000 ) );
	gui.add( qualityLevel.set("qualityLevel", 0.01, 0.001, .02 ) );
	gui.add( minDistance.set("minDistance", 4, 1, 16 ) );
	
	curFlow = &farneback;
	
	
	//set the timeline up with some default values
	timeline.setup();
    timeline.setFrameRate(25);
    //set big initial duration, longer than the video needs to be
	timeline.setDurationInFrames(20000);
	timeline.setLoopType(OF_LOOP_NORMAL);
	
	ofxTLVideoTrack* videoTrack = timeline.getVideoTrack("Video");
	
    if(videoTrack == NULL)
	{
	    videoTrack = timeline.addVideoTrack("Video");
    }
	videoTrack->setPlayer( videoPlayer );

	timeline.setSpacebarTogglePlay( false );
	timeline.setHeight( 120 );
	timeline.setWidth( ofGetWidth() );
	timeline.setOffset( ofVec2f(0, ofGetHeight() - timeline.getHeight()) );
	
	
}


// ---------------------------------------------------------------------------------------------------
//
void testApp::update()
{
	videoPlayer.nextFrame();
	videoPlayer.update();
	
	if(videoPlayer.isFrameNew())
	{
		if( useFarneback )
		{
			curFlow = &farneback;

			farneback.setPyramidScale( pyrScale );
			farneback.setNumLevels( levels );
			farneback.setWindowSize( winsize );
			farneback.setNumIterations( iterations );
			farneback.setPolyN( polyN );
			farneback.setPolySigma( polySigma );
			farneback.setUseGaussian( OPTFLOW_FARNEBACK_GAUSSIAN );
		}
		else
		{
			curFlow = &pyrLk;
			pyrLk.setMaxFeatures( maxFeatures );
			pyrLk.setQualityLevel( qualityLevel );
			pyrLk.setMinDistance( minDistance );
			pyrLk.setWindowSize( winSize );
			pyrLk.setMaxLevel( maxLevel );
		}

		curFlow->calcOpticalFlow(videoPlayer);
	}
}

// ---------------------------------------------------------------------------------------------------
//
void testApp::draw()
{
	ofBackground(0);
		
	ofSetColor(255);
	videoPlayer.draw(0,0);
	
	ofEnableAlphaBlending();
		ofSetColor( 0,0,255, 100 );
		curFlow->draw(0,0);
	ofDisableAlphaBlending();
	
	timeline.draw();
	
	gui.draw();
	
}


// ---------------------------------------------------------------------------------------------------
//
void testApp::exit()
{

}