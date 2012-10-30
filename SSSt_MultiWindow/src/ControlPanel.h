//
//  ControlPanel.h
//  ofxFensterExample
//
//  Created by Jonathan Bobrow on 8/12/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ofxFensterExample_AlternateWindows_h
#define ofxFensterExample_AlternateWindows_h

#include "ofxFensterManager.h"
#include "PercussionShapes.h"
#include "ofxFX.h"
#include "SSSobject.h"
#include "KorgControl.h"

enum{
	SSS_CALLI_STATE = 0,
	SSS_FLUID_STATE = 1,
	SSS_SHAPE_STATE = 2,
	SSS_HLINE_STATE = 3,
	SSS_VLINE_STATE = 4,
	SSS_VIDEO_STATE = 5,
	SSS_TITLE_STATE	= 6
};

class controlWindow: public ofxFensterListener {
public:
	~controlWindow();
	void setup();
	void update();
	void draw();
	
	void keyReleased(int key, ofxFenster* window);
	void keyPressed(int key, ofxFenster* window);
	
	KorgControl*	korg;			// Korg Control
	
	vector<SSSobject> strings;		// SSS objects
	
	int		state;
	int		xPositions[6];
	int		editString;
	
	int		titleNumber;
	
	int		bar;
	int		beat;
	string	scene;
	
	bool	bDoneCallibrating;
	bool	bOverrideScene;
	bool	bColorFluid;
	
	ofTrueTypeFont labelFont;
	ofTrueTypeFont barFont;
	ofTrueTypeFont beatFont;
	ofTrueTypeFont sceneFont;
};

#endif
