
#pragma once

#include "ofMain.h"

class TrackedPoint2D
{
	public:
	
		// -----------------------------
		TrackedPoint2D()
		{
			baseInit();
		}

		// -----------------------------
		TrackedPoint2D( ofVec2f _pos )
		{
			baseInit();
			pos = _pos;
		}
	
		// -----------------------------
		~TrackedPoint2D()
		{
			unsubscribeFromEvents();
		}
	
		// -----------------------------
		void baseInit()
		{
			name = "";
			color.setHsb( ofRandom(255), 200, 200 );
			maxDragRadius = 15.0f;
			
			subscribeToEvents();
		}
	
		// -----------------------------
		void subscribeToEvents()
		{
			ofAddListener( ofEvents().mousePressed,  this, &TrackedPoint2D::mousePressed );
			ofAddListener( ofEvents().mouseReleased, this, &TrackedPoint2D::mouseReleased );
			ofAddListener( ofEvents().mouseDragged,  this, &TrackedPoint2D::mouseDragged );
		}
	
		// -----------------------------
		void unsubscribeFromEvents()
		{
			ofRemoveListener( ofEvents().mousePressed,  this, &TrackedPoint2D::mousePressed );
			ofRemoveListener( ofEvents().mouseReleased, this, &TrackedPoint2D::mouseReleased );
			ofRemoveListener( ofEvents().mouseDragged,  this, &TrackedPoint2D::mouseDragged );
		}
	
		// -----------------------------
		void draw()
		{
			ofSetColor( color, 100 );
			ofNoFill();
				ofCircle( pos, maxDragRadius );
			ofFill();
			
			ofSetColor( color );
			ofCircle( pos, 1.0f );
		}

		// -----------------------------
		void mousePressed(ofMouseEventArgs &e)
		{
			if( e.button == 0 )
			{
				ofVec2f mousePos(e.x,e.y);
				if( mousePos.distance(pos) < maxDragRadius )
				{
					isDragged = true;
					draggedOffset = pos - mousePos;
				}
			}
		}
	
		// -----------------------------
		void mouseReleased(ofMouseEventArgs &e)
		{
			isDragged = false;
		}
		
		// -----------------------------
		void mouseDragged(ofMouseEventArgs &e)
		{
			ofVec2f mousePos(e.x,e.y);
			if( isDragged )
			{
				pos = mousePos + draggedOffset;
			}
		}
	
		ofVec2f pos;
		float maxDragRadius;
	
		ofColor color;
	
		bool isDragged;
		ofVec2f draggedOffset;

		string name;
};