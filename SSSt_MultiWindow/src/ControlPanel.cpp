//
//  ControlPanel.cpp
//  ofxFensterExample
//
//  Created by Jonathan Bobrow on 8/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "ControlPanel.h"

#define AMPLITUDE 20
#define KORG_CONNECTED 1

//--------------------------------------------------------------
controlWindow::~controlWindow() {
	cout << "Projection Window" << endl;
}

//--------------------------------------------------------------
void controlWindow::setup() {
	
	// Korg
	korg = new KorgControl();
	
	// STRINGS
	for (int i = 0; i<8; i++) {
		strings.push_back(SSSobject(i, ""));
	}
	
	// STRING POSITIONS
	for(int i=0; i<6; i++){
		xPositions[i] = 64+(i+1)*1024/8;
	}
	
	// INIT
	editString			= 0;
	titleNumber			= 0;
	bDoneCallibrating	= false;
	bOverrideScene		= false;
	bColorFluid			= false;
	state				= SSS_CALLI_STATE;
	scene				= "Callibrating: PRESS SPACEBAR";
	
	// load text
	barFont.loadFont("fonts/ApexNew-Book.otf", 36, true, true, true);
	beatFont.loadFont("fonts/ApexNew-Book.otf", 18, true, true, true);
	sceneFont.loadFont("fonts/ApexNew-Book.otf", 24, true, true, true);
	labelFont.loadFont("fonts/ApexNew-Book.otf", 12, true, true, true);	
}

//--------------------------------------------------------------
void controlWindow::update() {

	// Update Korg
	if( KORG_CONNECTED ){
	
		for (int i = 0; i<6; i++) {
			strings[i].setThresholdLoud(korg->controlValue[i+10]);
//			strings[i].setAmpValue(AMPLITUDE*korg->controlValue[i]/127.f);		// Amplitude * normalized value
			strings[i].setAmpValue(40*(korg->controlValue[i]/127.f)*(korg->controlValue[i]/127.f));		// Curve sensitivity for amplitude
		}
	}

}


//--------------------------------------------------------------
void controlWindow::draw() {
	ofBackground(0);
	
	// display charts
	for (int i = 0; i<8; i++) {
		ofPushMatrix();
		ofTranslate(1024*i/8.f+20, 20);
		strings[i].display();
		
		// bass
		if( i == 6 ) labelFont.drawString("bass", 10, 10);
		// drums
		if( i == 7 ) labelFont.drawString("drums", 10, 10);
		
		ofPopMatrix();
	}	
	
	// display bars + current scene
	ofSetColor(153, 153, 153);
	labelFont.drawString("bar:", 50, 320);
	barFont.drawString(ofToString(bar), 80, 320);
	labelFont.drawString("beat:", 70, 360);
	beatFont.drawString(ofToString(beat), 110, 360);
	sceneFont.drawString(scene, 200, 320);
	
	// display override state, color fluid state
	if( bOverrideScene )
		labelFont.drawString("Override Scene: TRUE", 800, 320);
	else 
		labelFont.drawString("Override Scene: FALSE", 800, 320);

	
	// if in line mode, display lineWidth, spacing, and speckle...
	if( state == SSS_HLINE_STATE || state == SSS_VLINE_STATE ){
		
		ofPushStyle();
		ofSetColor(255, 153, 0);	// orange text
		
		string s = "stroke: " + ofToString(10*korg->controlValue[6]/127.f, 1);
		labelFont.drawString(s, 800, 260);
		
		s = "stretch: " + ofToString(1+20*korg->controlValue[7]/127.f, 1);
		labelFont.drawString(s, 928, 260);
		
		s = "speckle: " + ofToString(1+20*korg->controlValue[17]/127.f, 0);
		labelFont.drawString(s, 928, 280);
		
		ofPopStyle();
	}
	
	// smoke params...
	else if( state == SSS_FLUID_STATE ){
		
		if( bColorFluid )
			labelFont.drawString("Color Smoke: TRUE", 800, 360);
		else
			labelFont.drawString("Color Smoke: FALSE", 800, 360);

			
		ofPushStyle();
		ofSetColor(255, 153, 0);	// orange text
		
		string s = "gravity: " + ofToString(ofMap(korg->controlValue[6], 0.f, 127.f, 0.05f, .2f), 3);
		labelFont.drawString(s, 800, 260);
		
		s = "dissapation: " + ofToString(ofMap(korg->controlValue[7], 0.f, 127.f, .8f, 1.1f), 2);
		labelFont.drawString(s, 928, 260);
		
		s = "velocity: " + ofToString(ofMap(korg->controlValue[17], 0.f, 127.f, .8f, 1.1f), 2);
		labelFont.drawString(s, 928, 280);
		
		ofPopStyle();
	}
	
	// percussion params...
	else if( state == SSS_SHAPE_STATE ){
		
		ofPushStyle();
		ofSetColor(255, 153, 0);	// orange text
		
		string s = "wiggle: " + ofToString(ofMap(korg->controlValue[6], 0.f, 127.f, 0.f, 20.f), 2);
		labelFont.drawString(s, 800, 260);
		
		s = "radius: " + ofToString(ofMap(korg->controlValue[7], 0.f, 127.f, 5.f, 55.f), 0);
		labelFont.drawString(s, 928, 260);

		ofPopStyle();
	}
	
	// title frame
	else if( state == SSS_TITLE_STATE ){
		ofPushStyle();
		ofSetColor(255, 153, 0);	// orange text

		string s = "Title: " + ofToString(titleNumber,0);
		sceneFont.drawString(s, 200, 360);
		
		s = "opacity: " + ofToString(ofMap(korg->controlValue[16], 0.f, 127.f, 0.f, 255.f), 0);
		labelFont.drawString(s, 800, 260);
	}

}

//--------------------------------------------------------------
void controlWindow::keyReleased(int key, ofxFenster* window) {
	if(key=='f')
		ofxFensterManager::get()->getPrimaryWindow()->toggleFullscreen();

}

//--------------------------------------------------------------
void controlWindow::keyPressed(int key, ofxFenster* window)
{
	// STATES
	if( key == '1')
		state = SSS_FLUID_STATE;
	
	if( key == '2')
		state = SSS_SHAPE_STATE;
	
	if( key == '3')
		state = SSS_VLINE_STATE;
	
	if( key == '4')
		state = SSS_HLINE_STATE;
	
	if( key == '5')
		state = SSS_TITLE_STATE;
	
	if( key == '6')
		state = SSS_VIDEO_STATE;
	
	// OVERRIDE STATE
	if ( key == 'O' )
		bOverrideScene = !bOverrideScene;
	
	// CALLIBRATE
	if( key == ' ' )
		bDoneCallibrating = true;
	
	if( key == 'c' )
		bColorFluid = !bColorFluid;
		
	// ALIGN
	if( key == 'l')
		xPositions[editString]++;
	
	if( key == 'j')
		xPositions[editString]--;
	
	if( key == 'k' && editString > 0)
		editString--;
	
	if( key == 'i' && editString < 6)
		editString++;		
	
	// TITLES
	if( key == 267 && titleNumber > 0)
		titleNumber--;
	
	if( key == 268 && titleNumber < 19)
		titleNumber++;
}