//
//  KorgControl.h
//  fluidExample
//
//  Created by Jonathan Bobrow on 8/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef fluidExample_KorgControl_h
#define fluidExample_KorgControl_h
#include "ofMain.h"
#include "ofxMidi.h"

class KorgControl : public ofxMidiListener{
public:
	KorgControl();
	void cleanUp();
	void update();
	void newMidiMessage(ofxMidiMessage& msg);
	
	ofxMidiIn midiIn;
	ofxMidiMessage midiMessage;	
	
	int controlValue[63];
};


#endif
