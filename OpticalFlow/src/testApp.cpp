#include "testApp.h"

using namespace ofxCv;
using namespace cv;

// ---------------------------------------------------------------------------------------------------
//
void testApp::setup()
{
	//camera.initGrabber(320, 240);

	//videoPlayer.loadMovie( "RosCenterShort.mp4" /*"IMG_3965.mov"*/ );
	//videoPlayer.setLoopState( OF_LOOP_NORMAL );
	//videoPlayer.play();
	
	fontSmall.loadFont("Fonts/DIN.otf", 8 );
	
	//ofDirectory tmpDir("/Volumes/Nanika USB 3.0/D01T01_Ros_center_subset_converted/");
	//ofDirectory tmpDir("/Volumes/Nanika USB 3.0/D01T01_Ros_center_subset_converted_900wide/");
	//ofDirectory tmpDir("/Volumes/Nanika USB 3.0/D01T01_Ros_center_subset_converted_1280wide/");
	ofDirectory tmpDir("SourceData/D01T01_Ros_center_subset_converted_1280wide/");
	
	tmpDir.allowExt("jpg");
	tmpDir.allowExt("png");
	int numFiles = tmpDir.listDir();
	for( int i = 0; i < numFiles; i++ )
	{
		filenames.push_back( tmpDir.getPath(i) );
	}
	currentIndex = 0;

	
	gui.setup("Flow Test");

	gui.add( doOpticalFlow.set("doOpticalFlow", true ) );
	gui.add( pyrScale.set("pyrScale", .5, 0, 1) );
	gui.add( levels.set("levels", 4, 1, 8) );
	gui.add( winsize.set("winsize", 8, 4, 64) );
	gui.add( iterations.set("iterations", 2, 1, 8) );
	gui.add( polyN.set("polyN", 7, 5, 10) );
	gui.add( polySigma.set("polySigma", 1.5, 1.1, 2) );
	gui.add( OPTFLOW_FARNEBACK_GAUSSIAN.set("OPTFLOW_FARNEBACK_GAUSSIAN", true ) );
	gui.add( drawFlow.set("drawFlow", true ) );

	gui.add( flowDrawingScale.set("Flow Drawing Scale", 2.0f, 0.1f, 20.0f ) );
	drawGui = true;
		
	//gui.add( useFarneback.set("useFarneback", true ) );
	
	/*
	gui.add( winSize.set("winSize", 32, 4, 64 ) );
	gui.add( maxLevel.set("maxLevel", 3, 0, 8 ) );
	gui.add( maxFeatures.set("maxFeatures", 200, 1, 1000 ) );
	gui.add( qualityLevel.set("qualityLevel", 0.01, 0.001, .02 ) );
	gui.add( minDistance.set("minDistance", 4, 1, 16 ) );
	*/
	 
	curFlow = &farneback;
	
	float alpha = 0.3f;
	ofFloatColor startColor(0.0f,0.0f,1.0f,alpha);
	ofFloatColor endColor(1.0f,0.0f,0.0f,alpha);
	
	farneback.setLineDrawingColors( startColor, endColor );
	
/*
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
	*/
	
	isPlaying = false;
}


// ---------------------------------------------------------------------------------------------------
//
void testApp::update()
{
	if( filenames.size() > 0 && isPlaying )
	{
		currentImage.loadImage( filenames.at(currentIndex) );
		currentIndex++;
		currentIndex %= filenames.size();
		
		//cv::Mat imageCv = toCv(currentImage);
	
			if( doOpticalFlow )
			{
			//if( useFarneback )
			//{
				curFlow = &farneback;
				
				farneback.setPyramidScale( pyrScale );
				farneback.setNumLevels( levels );
				farneback.setWindowSize( winsize );
				farneback.setNumIterations( iterations );
				farneback.setPolyN( polyN );
				farneback.setPolySigma( polySigma );
				farneback.setUseGaussian( OPTFLOW_FARNEBACK_GAUSSIAN );
			
				farneback.setDrawExtraScaling( flowDrawingScale );
			
			//}
			/*
			else
			{
				curFlow = &pyrLk;
				pyrLk.setMaxFeatures( maxFeatures );
				pyrLk.setQualityLevel( qualityLevel );
				pyrLk.setMinDistance( minDistance );
				pyrLk.setWindowSize( winSize );
				pyrLk.setMaxLevel( maxLevel );
			}*/
			
			curFlow->calcOpticalFlow(currentImage);
				
			for( unsigned int i = 0; i < trackedPoints.size(); i++ )
			{
				int windowSize = 1;
				
				ofVec2f tmpPos = trackedPoints.at(i)->pos;
				ofRectangle flowRect( tmpPos.x-windowSize, tmpPos.y-windowSize,windowSize,windowSize );
				ofVec2f tmpOffset = farneback.getAverageFlowInRegion( flowRect );
				trackedPoints.at(i)->pos += tmpOffset;
			}
				
			pointsBoundingBox = getBoundingBox( trackedPoints );
		}
		
	}
		
}

// ---------------------------------------------------------------------------------------------------
//
void testApp::draw()
{
	ofBackground(0);
		
	ofSetColor( ofColor::white );
	
	float tmpRel = ofGetWidth() / currentImage.getWidth();
	
//	videoPlayer.draw(0,0);
	
	ofPushMatrix();
		
		//ofScale( tmpRel, tmpRel, 1.0f );
		if( currentImage.isAllocated() ) currentImage.draw(0,0);
		
		ofEnableAlphaBlending();
	
			if( drawFlow) curFlow->draw(0,0);
		
			for( unsigned int i = 0; i < trackedPoints.size(); i++ )
			{
				trackedPoints.at(i)->draw();
			}
	
			ofSetColor( ofColor::blue, 40 );
			ofNoFill();
			ofRect( pointsBoundingBox );
			ofFill();
	
		ofDisableAlphaBlending();
	
	ofPopMatrix();
	
	//timeline.draw();
	
	ofSetColor( ofColor::white );
	
	for( unsigned int i = 0; i < trackedPointCloseUpViews.size(); i++ )
	{
		trackedPointCloseUpViews.at(i)->draw();
	}
	
	if( drawGui ) gui.draw();

	ofSetColor( ofColor::black );
	string frameStr = "Frame: " + ofToString( currentIndex ) + " / " + ofToString(filenames.size());
	if( isPlaying ) { frameStr += "  (Playing)"; } else { frameStr += "  (Paused)"; }
	fontSmall.drawString(frameStr, 10, ofGetHeight() - 20 );
	
}

// ---------------------------------------------------------------------------------------------------
//
ofRectangle testApp::getBoundingBox( vector< TrackedPoint2D* >& _points )
{
	ofRectangle bbox;
	for( unsigned int i = 0; i < _points.size(); i++ )
	{
		if(i == 0) {
			bbox.set( _points.at(i)->pos,0,0);
		} else {
			bbox.growToInclude( _points.at(i)->pos );
		}
	}
	return bbox;
}

// ---------------------------------------------------------------------------------------------------
//
void testApp::keyPressed(int key)
{
	if( key == ' ' )
	{
		isPlaying = !isPlaying;
	}
	else if ( key == OF_KEY_TAB )
	{
		drawGui = !drawGui;
	}
}

// ---------------------------------------------------------------------------------------------------
//
void testApp::mouseMoved(int x, int y )
{
}

// ---------------------------------------------------------------------------------------------------
//
void testApp::mouseDragged(int x, int y, int button)
{
}

// ---------------------------------------------------------------------------------------------------
//
void testApp::mousePressed(int x, int y, int button)
{
	if( button == 2 )
	{
		trackedPoints.push_back( new TrackedPoint2D( ofVec2f(x,y) ) );
		trackedPointCloseUpViews.push_back( new TrackedPoint2DCloseUpView( trackedPoints.back(), &currentImage ) );
		
		int drawSize = 100;
		trackedPointCloseUpViews.back()->drawRect.set( ofGetWidth()-drawSize, trackedPointCloseUpViews.size() * drawSize, drawSize, drawSize );
	}
}

// ---------------------------------------------------------------------------------------------------
//
void testApp::mouseReleased(int x, int y, int button)
{
}


// ---------------------------------------------------------------------------------------------------
//
void testApp::exit()
{
	//timeline.removeTrack("Video");
}