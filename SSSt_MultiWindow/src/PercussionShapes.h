//
//  PercussionShapes.h
//  fluidExample
//
//  Created by Jonathan Bobrow on 8/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef fluidExample_PercussionShapes_h
#define fluidExample_PercussionShapes_h

#include "ofMain.h"
#include "Shape.h"

class PercussionShapes {
public:
	PercussionShapes();
	~PercussionShapes();
	
	void addShape(int string, int xPos);
	void removeAllShapes();
	void update();
	void display();
	
	void setRadius(float r);
	void setWiggle(float w);
	void setNoise(float n);
	
	vector<Shape> shapes;			// Shapes
	
	bool	bMortality;
};

#endif
