
#pragma once

#include "ofMain.h"
#include "ofXml.h"

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
			
			isDragged = false;
			mouseIsOver = false;
			
			fontSmall = NULL;
			
			stageScale = 1.0f;
			
			pointsXml.addChild("Points");
			
			posHistoryMesh.setMode( OF_PRIMITIVE_LINE_STRIP );
			
			subscribeToEvents();
		}
	
		// -----------------------------
		void subscribeToEvents()
		{
			ofAddListener( ofEvents().mousePressed,  this, &TrackedPoint2D::mousePressed,  OF_EVENT_ORDER_BEFORE_APP + 1 );
			ofAddListener( ofEvents().mouseReleased, this, &TrackedPoint2D::mouseReleased, OF_EVENT_ORDER_BEFORE_APP + 1 );
			ofAddListener( ofEvents().mouseDragged,  this, &TrackedPoint2D::mouseDragged,  OF_EVENT_ORDER_BEFORE_APP + 1 );
			ofAddListener( ofEvents().mouseMoved,	 this, &TrackedPoint2D::mouseMoved,	   OF_EVENT_ORDER_BEFORE_APP + 1 );
			
			
		}
	
		// -----------------------------
		void unsubscribeFromEvents()
		{
			ofRemoveListener( ofEvents().mousePressed,  this, &TrackedPoint2D::mousePressed );
			ofRemoveListener( ofEvents().mouseReleased, this, &TrackedPoint2D::mouseReleased );
			ofRemoveListener( ofEvents().mouseDragged,  this, &TrackedPoint2D::mouseDragged );
			ofRemoveListener( ofEvents().mouseMoved,    this, &TrackedPoint2D::mouseMoved );
		}
	
		// -----------------------------
		void draw()
		{
			ofSetColor( color, 150 );
			
			ofPushMatrix();
			
				//float invScale = 1.0f / stageScale;
				//ofScale( invScale, invScale, invScale );
			
				ofNoFill();
					ofCircle( pos, maxDragRadius );
				ofFill();
				
				ofSetColor( color );
				ofCircle( pos, 1.0f );
				
				// we also draw N amount of old points to the right of our position
				int pointsToDraw = 150;
				pointsToDraw = ofClamp( pointsToDraw, 0, positionHistory.size() );
				
				posHistoryMesh.clear();
				for( int i = 0; i < pointsToDraw; i++ )
				{
					posHistoryMesh.addVertex( positionHistory.at(positionHistory.size()-i-1) );
					posHistoryMesh.addColor( ofColor(color, ofMap(i, 0, pointsToDraw, 255,0)) );
				}
				
				ofVec2f tmpOffset(100,0);
				ofPushMatrix();
					ofTranslate( tmpOffset );
				
					ofSetColor( color );
					ofCircle( pos, 1.0f );
				
					posHistoryMesh.draw();
				
				ofPopMatrix();
				
				if( mouseIsOver )
				{
					if( fontSmall != NULL )
					{
						ofVec2f drawPos( pos.x - (fontSmall->stringWidth(name)*0.5f), pos.y - maxDragRadius * 1.15f );
					
						//ofSetColor( ofColor::white );
						//fontSmall->drawString( name, drawPos.x+1, drawPos.y+1 );
						
						ofSetColor( color );
						fontSmall->drawString( name, drawPos.x, drawPos.y );
					}
				}
			
			ofPopMatrix();
		}

		// -----------------------------
		void update()
		{
			// Todo: we should have the concept of frames, a point could be added at a later stage in the processing
			
			ofXml tmpPoint;
			tmpPoint.addChild("Point2D");
			tmpPoint.setTo("Point2D");
			tmpPoint.setAttribute("x", ofToString(pos.x) );
			tmpPoint.setAttribute("y", ofToString(pos.y) );

			pointsXml.addXml( tmpPoint );
			
			pointsTextBuffer += ofToString((int)pos.x) + " " + ofToString((int)pos.y) + '\n';
						
			positionHistory.push_back( pos );
		}

		// -----------------------------
		void save( string _path )
		{
			if( name.length() > 0 ) // if we don't have a name, we're not worth saving
			{
				string filePathXML = _path + name + ".xml";
				string filePathTXT = _path + name + ".txt";
				
				pointsXml.save( filePathXML );
				
				ofFile file(filePathTXT,ofFile::WriteOnly);
				file << pointsTextBuffer;
				file.close();
			}
		}
	
		// -----------------------------
		bool mousePressed(ofMouseEventArgs &e)
		{
			
			float invScale = 1.0f / stageScale;
			ofVec2f mousePos( e.x * invScale, e.y * invScale );
			if( mousePos.distance(pos) < maxDragRadius )
			{
				if( e.button == 0 )
				{
					isDragged = true;
					draggedOffset = pos - mousePos;
				}
				
				return true; // we consume the event
			}
			
			return false;
		}
	
		// -----------------------------
		bool mouseReleased(ofMouseEventArgs &e)
		{
			isDragged = false;
			
			return false;
		}
		
		// -----------------------------
		bool mouseDragged(ofMouseEventArgs &e)
		{
			if( isDragged )
			{
				float invScale = 1.0f / stageScale;
				ofVec2f mousePos( e.x * invScale, e.y * invScale );
				pos = mousePos + draggedOffset;
				return true; // we consume the event
			}
			return false;
		}
	
		// -----------------------------
		bool mouseMoved(ofMouseEventArgs &e)
		{
			float invScale = 1.0f / stageScale;
			ofVec2f mousePos( e.x * invScale, e.y * invScale );
			if( mousePos.distance(pos) < maxDragRadius )
			{
				mouseIsOver = true;
			}
			else
			{
				mouseIsOver = false;
			}
			return false;
		}
	
		ofVec2f pos;
		float maxDragRadius;
	
		float stageScale;

		vector<ofVec2f> positionHistory;
	
		ofColor color;
	
		bool isDragged;
		ofVec2f draggedOffset;

		bool mouseIsOver;
	
		ofTrueTypeFont* fontSmall;
	
		string name;
	
		ofXml pointsXml;
		string pointsTextBuffer; // data in the format Instant Vision likes, "int int breakline"
	
		ofMesh posHistoryMesh;
};