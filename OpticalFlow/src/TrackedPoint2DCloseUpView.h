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
		}
	
		// -------------------------------------
		void subscribeToEvents()
		{
			ofAddListener( ofEvents().mousePressed,  this, &TrackedPoint2DCloseUpView::mousePressed );
			ofAddListener( ofEvents().mouseReleased, this, &TrackedPoint2DCloseUpView::mouseReleased );
			ofAddListener( ofEvents().mouseDragged,  this, &TrackedPoint2DCloseUpView::mouseDragged );
		}
		
		// -------------------------------------
		void unsubscribeFromEvents()
		{
			ofRemoveListener( ofEvents().mousePressed,  this, &TrackedPoint2DCloseUpView::mousePressed );
			ofRemoveListener( ofEvents().mouseReleased, this, &TrackedPoint2DCloseUpView::mouseReleased );
			ofRemoveListener( ofEvents().mouseDragged,  this, &TrackedPoint2DCloseUpView::mouseDragged );
		}
	
		// -------------------------------------
		void mousePressed(ofMouseEventArgs &e)
		{
			if( e.button == 0 )
			{
				ofVec2f mousePos(e.x,e.y);
								
				if( drawRect.inside( mousePos ) )
				{
					startDragPos = mousePos;
					isDragged = true;
				}
			}
		}
		
		// -------------------------------------
		void mouseReleased(ofMouseEventArgs &e)
		{
			isDragged = false;
		}
		
		// -------------------------------------
		void mouseDragged(ofMouseEventArgs &e)
		{
			if( isDragged )
			{
				ofVec2f mousePos(e.x,e.y);
				trackedPoint->pos -= ( mousePos - startDragPos ) * (srcRect.width / drawRect.width);
				startDragPos = mousePos;
			}
		}
	
		ofRectangle drawRect;
		ofRectangle srcRect;
	
		float sourceWindowWidth;
		float sourceWindowHeight;
	
		ofImage* srcImage;
		TrackedPoint2D* trackedPoint;
	
		bool isDragged;
		ofVec2f startDragPos;
};