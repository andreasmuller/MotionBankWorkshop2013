#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	camera.setFov( 60.0f );
	camera.setNearClip( 0.01f );
	camera.setFarClip( 1024.0f );
	camera.setAutoDistance( false );
	
	//camera.setTranslationKey('a');
	camera.setDollyForwardKey('a');
	camera.setDollyBackwardKey('z');
	
	camera.orbit( 10, -20, 150 );
	
	
	TrackVec3Reader::readVec3DFile( positionTrack,
									"Ros_D01T01_withBackgroundAdjustment_Corrected/Tracked3DPosition_25fps.txt",
								    0.0f,
								    25.0f );
	
	
	ofQuaternion recordingCameraLeftQuat( -0.768194, 0.194866, -0.172453, 0.584948 );
	ofVec3f recordingCameraLeftPos( -1.22784, -6.78289, 3.56278 );
	recordingCameraLeft.setPosition( recordingCameraLeftPos );
	recordingCameraLeft.setOrientation( recordingCameraLeftQuat );
	
	ofQuaternion recordingCameraRightQuat( -0.78026, 0.00625737, -0.00959723, 0.62535 );
	ofVec3f recordingCameraRightPos( 5.79188,-11.2932, 4.96226 );
	recordingCameraRight.setPosition( recordingCameraRightPos );
	recordingCameraRight.setOrientation( recordingCameraRightQuat );
	
	ofQuaternion recordingCameraCenterQuat( -0.770106, -0.211129, 0.155179, 0.581619 );
	ofVec3f recordingCameraCenterPos( 13.5083, -7.13461, 3.63259 );
	recordingCameraCenter.setPosition( recordingCameraCenterPos );
	recordingCameraCenter.setOrientation( recordingCameraCenterQuat );
}


//--------------------------------------------------------------
void testApp::update()
{

}

//--------------------------------------------------------------
void testApp::draw()
{
	
	ofEnableDepthTest();
	
	camera.begin();
	
		ofSetColor( ofColor::whiteSmoke );
		ofPushMatrix();
			ofRotateY( 90 );
			ofDrawGridPlane( 100.0f );
		ofPopMatrix();
	
		ofSetColor( ofColor::red );
	
	
		ofPushMatrix();
	
			//ofRotateX( -90 );
			//ofTranslate(0,0,0);
	
			ofVec3f tmpPos;
			//tmpPos.set( ofRandom(-10, 10), ofRandom(0, 10), ofRandom(-10, 10) );
			if( positionTrack.trackIsValid() )
			{
				tmpPos = positionTrack.getValueAtTime( ofGetElapsedTimef() * 10.0f, true, false );
				//tmpPos *= 10.0f;
			}
			ofDrawSphere(tmpPos, 1.0f);

			maxPositionHistoryLength = 5000;
			positionHistory.push_front( tmpPos );
		
			while( positionHistory.size() > maxPositionHistoryLength )
			{
				positionHistory.pop_back();
			}
			
			ofMesh tmpMesh;
			tmpMesh.setMode( OF_PRIMITIVE_LINES );
			if( positionHistory.size() > 1 )
			{
				for( unsigned int i = 0; i < positionHistory.size()-1; i++ )
				{
					tmpMesh.addVertex( positionHistory.at(i) );
					tmpMesh.addVertex( positionHistory.at(i+1) );
				}
			}
			tmpMesh.draw();
		
		ofPopMatrix();
	
		ofSetColor( ofColor::white );
	
		recordingCameraLeft.draw();
		recordingCameraRight.draw();
		recordingCameraCenter.draw();
	
	camera.end();
	
	ofDisableDepthTest();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{

}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg)
{
}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo)
{
}

/*
 
 # ==================================================================
 # Exported camera pose (rotation and translation of the camera) for
 # Florian and Amin (MotionBank project):
 # In contrast to the extrinsic data, the exported rotation of the camera
 # is the rotation from the WCS (world coordinate system) to the camera
 # (and not vice versa). The exported position is NOT the translation of the
 # camera pose, but the position of the camera in the WCS.
 
 # Description of recording, take and camera:
 # Camera key: Recordings_2011_04_Solos_ExtrinsicCamLeft
 
 # Rotation_WCS_to_Camera (rotation matrix):
 0.864575 -0.0976383 0.492927
 -0.501142 -0.239725 0.831498
 0.0369811 -0.965919 -0.256191
 # Rotation_WCS_to_Camera (quaternion, order: x y z w)
 -0.768194 0.194866 -0.172453 0.584948
 # Position of camera in the WCS:
 -1.22784 -6.78289 3.56278
 
 
 
 # Description of recording, take and camera:
 # Camera key: Recordings_2011_04_Solos_ExtrinsicCamCenter
 
 # Rotation_WCS_to_Camera (rotation matrix):
 0.999737 0.00223852 0.0228028
 -0.021768 -0.217796 0.975752
 0.00715059 -0.975992 -0.21769
 # Rotation_WCS_to_Camera (quaternion, order: x y z w)
 -0.78026 0.00625737 -0.00959723 0.62535
 # Position of camera in the WCS:
 5.79188 -11.2932 4.96226
 
 
=
 
 # Description of recording, take and camera:
 # Camera key: Recordings_2011_04_Solos_ExtrinsicCamRight
 
 # Rotation_WCS_to_Camera (rotation matrix):
 0.862688 0.144672 -0.484602
 0.505694 -0.234288 0.830291
 0.00658374 -0.961342 -0.275277
 # Rotation_WCS_to_Camera (quaternion, order: x y z w)
 -0.770106 -0.211129 0.155179 0.581619
 # Position of camera in the WCS:
 13.5083 -7.13461 3.63259
 

 

 */
