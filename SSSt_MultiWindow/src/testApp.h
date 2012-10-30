#pragma once

#include "ofMain.h"
#include "ControlPanel.h"
#include "SSSosc.h"
#include "KorgControl.h"
#include "Lines.h"
#include "TitleSequence.h"

class testApp : public ofBaseApp {

public:
    void setup();
    void update();
	void updateScene();
    void draw();
	void exit();

	void keyPressed  (int key);
	void keyReleased(int key);

	void setState(int s);
	
	bool	bPlayedVideo;
	
	int		sceneTimes[13];
	
	int		curScene;
	
	SSSosc osc;						// OSC
		
	controlWindow controlPanel;		// Multiple Windows
	ofxFenster* test;
	
	PercussionShapes pShapes;		// Percussive shapes
	
	ofxFluid fluid;					// FLuid 
	
	ofVideoPlayer video;			// Video
	
	VerticalLines vLines;			// Vert Lines
	
	HorizontalLines hLines;			// Horizontal Lines

	TitleSequence titles;			// Title Sequence
};
