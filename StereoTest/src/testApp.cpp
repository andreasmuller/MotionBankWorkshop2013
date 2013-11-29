#include "testApp.h"

using namespace ofxCv;
using namespace cv;

// ---------------------------------------------------------------------------------------------------
//
void testApp::setup()
{
	fontSmall.loadFont("Fonts/DIN.otf", 8 );
	
	gui.setup("Stereo");
	drawGui = true;
	
	imageLeft.loadImage("SourceData/D01T01_Ros_sync_Left_Frame0.png");
	imageRight.loadImage("SourceData/D01T01_Ros_sync_Right_Frame0.png");
}

/*
 
 <IntrinsicDataPerspective calibrated="1" camerainfo='MotionBank_2011_04_CamLeft' key="IntrinsicCamLeft_Recordings2011_04">
	<Image_Resolution h='1080' w='1920'/>
	<Normalized_Principal_Point cx='0.4914' cy='0.4848'/>
	<Normalized_Focal_Length_and_Skew fx='0.9691' fy='1.7302' s='0.0'/>
	<Lens_Distortion k1='-0.218994' k2='0.175059' k3='0.00244' k4='-0.001355' k5='0.0'/>
 </IntrinsicDataPerspective>
 
 <IntrinsicDataPerspective calibrated="1" camerainfo='MotionBank_2011_04_CamRight' key="IntrinsicCamRight_Recordings2011_04">
	<Image_Resolution h='1080' w='1920'/>
	<Normalized_Principal_Point cx='0.50663' cy='0.483735'/>
	<Normalized_Focal_Length_and_Skew fx='0.99119' fy='1.76755' s='0.0'/>
	<Lens_Distortion k1='-0.197812' k2='0.135983' k3='0.005245' k4='-0.001163' k5='0.0'/>
 </IntrinsicDataPerspective>
 
 
 <ExtrinsicData bUseQuaternion='1' calibrated='1' key='ExtrinsicCamLeft_Recordings2011_04' t='0'>
	<R rotation='0.584948409 0.7681944587 -0.1948659841 0.1724525464'/>
	<t translation='[-2.469386766 1.69543843 7.157942597 ]'/>
	<Cov covariance="0  0  0  0  0  0  &#xA;0  0  0  0  0  0  &#xA;0  0  0  0  0  0  &#xA;0  0  0  0  0  0  &#xA;0  0  0  0  0  0  &#xA;0  0  0  0  0  0  &#xA;"/>
 </ExtrinsicData>
 
 <ExtrinsicData bUseQuaternion='1' calibrated='1' key='ExtrinsicCamRight_Recordings2011_04' t='0'>
	<R rotation='0.5816191647 0.7701059394 0.2111286909 -0.1551794612'/>
	<t translation='[-8.069439892 -0.1336678099 13.46992451 ]'/>
	<Cov covariance="0  0  0  0  0  0  &#xA;0  0  0  0  0  0  &#xA;0  0  0  0  0  0  &#xA;0  0  0  0  0  0  &#xA;0  0  0  0  0  0  &#xA;0  0  0  0  0  0  &#xA;"/>
 </ExtrinsicData>
 
 
 ofQuaternion recordingCameraLeftQuat( -0.768194, 0.194866, -0.172453, 0.584948 );
 ofVec3f recordingCameraLeftPos( -1.22784, -6.78289, 3.56278 );
 recordingCameraLeft.setPosition( recordingCameraLeftPos );
 recordingCameraLeft.setOrientation( recordingCameraLeftQuat );
 
 ofQuaternion recordingCameraRightQuat( -0.78026, 0.00625737, -0.00959723, 0.62535 );
 ofVec3f recordingCameraRightPos( 5.79188,-11.2932, 4.96226 );
 recordingCameraRight.setPosition( recordingCameraRightPos );
 recordingCameraRight.setOrientation( recordingCameraRightQuat );
 */

// ---------------------------------------------------------------------------------------------------
//
void testApp::update()
{
			
}

// ---------------------------------------------------------------------------------------------------
//
void testApp::draw()
{
	ofBackground(0);
		
	ofSetColor( ofColor::white );
	
	float sizeDiv = 4.0f;
	imageLeft.draw(0,0,imageLeft.getWidth()/sizeDiv,imageLeft.getHeight()/sizeDiv);
	imageRight.draw(imageLeft.getWidth()/sizeDiv,0,imageRight.getWidth()/sizeDiv,imageRight.getHeight()/sizeDiv);
	
	if( drawGui ) gui.draw();

	ofSetColor( ofColor::black );
	fontSmall.drawString( ofToString(ofGetElapsedTimef(), 1), 10, ofGetHeight() - 20 );
	
}

// ---------------------------------------------------------------------------------------------------
//
void testApp::keyPressed(int key)
{
	if( key == ' ' )
	{
		
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
}