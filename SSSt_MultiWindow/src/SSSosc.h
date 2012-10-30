//
//  SSSosc.h
//  fluidExample
//
//  Created by Jonathan Bobrow on 7/27/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef fluidExample_osc_h
#define fluidExample_osc_h

#include "ofxOsc.h"
#include "ofxOscReceiver.h"

// listen on port 12000
#define PORT 12000

class SSSosc: ofxOscReceiver{
public:
	SSSosc();
	void setupOSC(int n);
	void listenOSC();

	float	bass, drums;
	float	string1, string2, string3, string4, string5, string6;
	int		bar, beat;
	float	unit; 
};
#endif
