//
//  Track.h
//  MotionBank3DPosition
//
//  Created by Andreas Müller on 24/11/2013.
//
//

#pragma once

#include "ofMain.h"

// -------------------------------------------------------------------------------------------------
//
template <class T>
class Track
{
	public:
	
		// --------------------------------------
		Track()
		{
			trackLength = 0.0f;
		}

		// --------------------------------------
		T getValueAtTime( float _t, bool _loop = true, bool _interpolate = true )
		{
			
			if(values.size()==0)
			{
				// hmm, how return a generic 0
				return T();
			}
			
			int index = getIndex( _t, _loop );
						
			T returnVal = values.at(index);
			
			if( _interpolate && index < values.size()-2)
			{
				float fps = trackLength / values.size();
				float localTime = fmod( _t, fps );
				float tmpFrac = localTime / fps;
				
				int nextIndex =  getIndex( _t + fps, _loop );
				T nextVal = values.at(nextIndex);
								
				return returnVal + (nextVal-returnVal) * tmpFrac;
			}
			
			return returnVal;
		}

		// --------------------------------------
		bool trackIsValid()
		{
			return values.size() > 0;
		}

		// --------------------------------------
		void addValue( T _val, float _valLengthSecs = 0.03333333333333f )
		{
			values.push_back( _val );
			trackLength += _valLengthSecs;
		}

		// --------------------------------------
		int getNumValues()
		{
			return values.size();
		}

		// --------------------------------------
		float getTrackLength()
		{
			return trackLength;
		}
	
		// --------------------------------------
		void setTrackLength( float _trackLength )
		{
			trackLength = _trackLength;
		}
	
	protected:
	
		// --------------------------------------
		int getIndex( float _t, bool _loop = true )
		{
			if( _loop )
			{
				_t = fmod( _t, trackLength );
			}
			
			_t = ofClamp( _t, 0.0f, trackLength );
			
			return (_t / trackLength) * (values.size()-1);
		}
	
		vector<T> values;
		float trackLength;
};


// -------------------------------------------------------------------------------------------------
//
class TrackVec3Reader
{
	public:
	
		static bool readVec3DFile( Track<ofVec3f>& _track, string _path, float _trackLength = 0.0f, float _fps = 30.0f )
		{
			// read text file
			ifstream fin;
			fin.open( ofToDataPath(_path).c_str() );
			
			if( fin == NULL )
			{
				ofLogError() << "Track<ofVec3f>::readVec3DFile could not open: " << _path;
				return false;
			}
			else
			{
				vector<string> lines;
				
				while( fin != NULL )
				{
					string str;
					getline(fin, str);
					lines.push_back(str);
				}
				
				for( unsigned int i = 0; i < lines.size(); i++ )
				{
					ofVec3f tmp;
					
					// split at space
					vector<string> tokens = ofSplitString( lines.at(i), " ", true, true );
					if( tokens.size() == 3 )
					{
						tmp.x = ofToFloat( tokens.at(0) );
						tmp.y = ofToFloat( tokens.at(1) );
						tmp.z = ofToFloat( tokens.at(2) );
					}
					else
					{
						ofLogError() << "SeeneObjectData::vec3FromString, unexpected input " << lines.at(i);
					}
					
					_track.addValue(tmp);
				}
			}
			
			// we don't know the data length, so we assume a framerate
			if( _trackLength == 0.0f )
			{
				float frameLength = 1.0f / _fps;
				_track.setTrackLength( _track.getNumValues() * frameLength );
			}
			
			return true;
		}

};

