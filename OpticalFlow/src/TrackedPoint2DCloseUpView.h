//
//  TrackedPoint2DCloseUpView.h
//  OpticalFlow
//
//  Created by Andreas Müller on 27/11/2013.
//
//

#pragma once

#include "TrackedPoint2D.h"

class TrackedPoint2DCloseUpView
{
	public:

		// -------------------------------------
		TrackedPoint2DCloseUpView( TrackedPoint2D* _trackedPoint, ofImage* _srcImage )
		{
			srcImage = _srcImage;
			trackedPoint = _trackedPoint;
			
			sourceWindowWidth = 30;
			sourceWindowHeight = 30;
			
			isDragged = false;
			
			int drawSize = 90;
			drawRect.set( ofGetWidth()-drawSize, 0, drawSize, drawSize );
			srcRect.set(0,0,30,30);
			
			fontSmall = NULL;
			
			subscribeToEvents();
		}
	
		// -------------------------------------
		~TrackedPoint2DCloseUpView()
		{
			unsubscribeFromEvents();
		}

		// -------------------------------------
		void draw()
		{
			srcRect.x = trackedPoint->pos.x - (srcRect.width  * 0.5f);
			srcRect.y = trackedPoint->pos.y - (srcRect.height * 0.5f);
			
			//ofSetColor( trackedPoint->color );
			//ofNoFill();
			//ofRect( drawRect );
			//ofRect( srcRect );
			//ofFill();
			
			ofSetColor( ofColor::white );
			srcImage->drawSubsection(drawRect.x, drawRect.y, drawRect.width, drawRect.height, srcRect.x, srcRect.y, srcRect.width, srcRect.height );
			
			ofSetColor( trackedPoint->color, 50 );
			ofCircle( drawRect.x + drawRect.width * 0.5f, drawRect.y + drawRect.height * 0.5f, 2.0f );
			
			if( fontSmall != NULL && trackedPoint->name.length() > 0 )
			{
				ofVec2f drawPos( drawRect.x, drawRect.y + fontSmall->stringHeight(trackedPoint->name) + 1 );
				drawPos += ofVec2f(2,1);
				
				ofSetColor( ofColor::white );
				fontSmall->drawString( trackedPoint->name, drawPos.x+1, drawPos.y+1 );
				
				ofSetColor( trackedPoint->color );
				fontSmall->drawString( trackedPoint->name, drawPos.x, drawPos.y );
			}
			
			ofSetColor( trackedPoint->color );
			ofNoFill();
				ofRect( drawRect );
			ofFill();
			
		}
	
		// -------------------------------------
		void subscribeToEvents()
		{
			ofAddListener( ofEvents().mousePressed,  this, &TrackedPoint2DCloseUpView::mousePressed,  OF_EVENT_ORDER_BEFORE_APP );
			ofAddListener( ofEvents().mouseReleased, this, &TrackedPoint2DCloseUpView::mouseReleased, OF_EVENT_ORDER_BEFORE_APP );
			ofAddListener( ofEvents().mouseDragged,  this, &TrackedPoint2DCloseUpView::mouseDragged,  OF_EVENT_ORDER_BEFORE_APP );
		}
		
		// -------------------------------------
		void unsubscribeFromEvents()
		{
			ofRemoveListener( ofEvents().mousePressed,  this, &TrackedPoint2DCloseUpView::mousePressed );
			ofRemoveListener( ofEvents().mouseReleased, this, &TrackedPoint2DCloseUpView::mouseReleased );
			ofRemoveListener( ofEvents().mouseDragged,  this, &TrackedPoint2DCloseUpView::mouseDragged );
		}
	
		// -------------------------------------
		bool mousePressed(ofMouseEventArgs &e)
		{
			ofVec2f mousePos(e.x,e.y);
							
			if( drawRect.inside( mousePos ) )
			{
				if( e.button == 0 )
				{
					startDragPos = mousePos;
					isDragged = true;
				}
					
				return true; // we consume the event
			}
			
			return false;
		}
		
		// -------------------------------------
		bool mouseReleased(ofMouseEventArgs &e)
		{
			isDragged = false;
			return false;
		}
		
		// -------------------------------------
		bool mouseDragged(ofMouseEventArgs &e)
		{
			if( isDragged )
			{
				ofVec2f mousePos(e.x,e.y);
				trackedPoint->pos -= ( mousePos - startDragPos ) * (srcRect.width / drawRect.width);
				startDragPos = mousePos;
				
				return true; // we consume the event
			}
			
			return false;
		}
	
		ofRectangle drawRect;
		ofRectangle srcRect;
	
		float sourceWindowWidth;
		float sourceWindowHeight;
	
		ofImage* srcImage;
		TrackedPoint2D* trackedPoint;
	
		bool isDragged;
		ofVec2f startDragPos;
	
		ofTrueTypeFont* fontSmall;
	
		string name;
};