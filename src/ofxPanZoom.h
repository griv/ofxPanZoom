/*
 *  ofxPanZoom.h
 *  iPhoneEmptyExample
 *
 *  Created by Oriol Ferrer Mesià on 5/17/10.
 *  Copyright 2010 uri.cat. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxiPhone.h"
#include "ofxiPhoneExtras.h"
#include "ofxEasyRetina.h"

#define	MAX_TOUCHES		12
#define MIN_FINGER_DISTANCE 70.0f /* in pixels - zooming when fingers were too close was unaccurate & jumpy*/

class testApp;

class ofxPanZoom{

public:
	
	ofxPanZoom();
	~ofxPanZoom(){};
		
	void touchDown(ofTouchEventArgs &touch);
	void touchMoved(ofTouchEventArgs &touch);
	void touchUp(ofTouchEventArgs &touch);
	void touchDoubleTap(ofTouchEventArgs &touch);

	void setViewportConstrain(ofVec2f topLeftConstrain_, ofVec2f bottomRightConstrain_ );
	void removeViewportConstrain();

	void setDeviceScaleFactor(float f); //retina

	void setMinZoom(float min){ minZoom = min;} //how far out user can zoom
	void setMaxZoom(float max){ maxZoom = max;}	//how far in user can zoom
	void setZoom(float z){ zoom = desiredZoom = z;}  //set a zoom level
	void setSmoothFactor(float smooth){ smoothFactor = smooth;}; // [0..1], 1 means no fitlering at all, 0.1 very smoothed zoom
	//void setVerticalFlip( bool flip){ vFlip = flip; } 

	bool fingerDown(); //return true if user has 1+ fingers on screen
	float getZoom(){ return zoom; } //current zoom level
	ofVec2f getOffset(){return -offset;}
	
	void setScreenSize(int x, int y); //you need to provide the device screen size here
	bool isOnScreen(const ofVec2f & p, float gap = 0.0f); //query if a point (in world units) is now visible on screen
	bool isOnScreen(const ofRectangle & r, float gap = 0.0f); //query if an ofRectangle (in world units) is now visible on screen
	void lookAt(ofVec2f p);	//set the offset to place the given point (in world units) in the middle of the screen
	ofRectangle getCurentViewPort();

	void update(float deltaTime);

	void apply(int customW = 0, int customH = 0);	//customWH >> if you need to provide a viewport size (not full screen)
	void reset(); //go back to default OF screen projection
	void drawDebug(); //overlay camera and touches status on screen
	bool viewportDidChange();
	
	ofVec2f screenToWorld(const ofVec2f & p); //convert a point from current screen units to world units
	ofVec2f worldToScreen(const ofVec2f & p); //convert a point from world units to current screen units
	
private:
	
	void applyConstrains();
	
	ofVec2f screenSize;
	
	//those keep the bbox of the world (in gl units) that are visible on screen
	ofVec2f topLeft;
	ofVec2f bottomRight;
	
	ofVec2f offset;
	ofVec2f desiredOffset;

	float zoom;
	float desiredZoom;

	float smoothFactor;
	
	float minZoom;
	float maxZoom;
	
	float zoomDiff;
	
	bool touching[MAX_TOUCHES];
	ofVec2f lastTouch[MAX_TOUCHES];
	
	bool vFlip;	//of give you standard OF flipped y
	bool viewportConstrained;
	ofVec2f topLeftConstrain, bottomRightConstrain;

	ofxEasyRetina retinaUtils;
	vector<int> touchIDOrder;

	ofRectangle pViewport;
	
};