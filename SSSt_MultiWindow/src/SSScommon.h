//
//  SSScommon.h
//  fluidExample
//
//  Created by Jonathan Bobrow on 8/13/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef fluidExample_SSScommon_h
#define fluidExample_SSScommon_h

#include "ofMain.h"

class SSScommon{
public:
	static const ofColor red;
	static const ofColor orange;
	static const ofColor yellow;
	static const ofColor green;
	static const ofColor blue;
	static const ofColor purple;
};

const ofColor SSScommon::red		= ofColor(255, 0, 60);
const ofColor SSScommon::orange		= ofColor(255, 123, 5);
const ofColor SSScommon::yellow		= ofColor(255, 220, 0);
const ofColor SSScommon::green		= ofColor(36, 211, 119);
const ofColor SSScommon::blue		= ofColor(57, 123, 255);
const ofColor SSScommon::purple		= ofColor(57, 0, 255);

#endif
