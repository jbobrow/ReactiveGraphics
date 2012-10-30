//
//  TitleSequence.h
//  ofxFensterExample
//
//  Created by Jonathan Bobrow on 8/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef ofxFensterExample_TitleSequence_h
#define ofxFensterExample_TitleSequence_h

#include "ofMain.h"

class TitleSequence{
public:
	TitleSequence();
	~TitleSequence();

	void loadImages();
	void setImageTo(int n);
	void setOpacity(int a);
	void update();
	void display();
	
	void next();
	void prev();

private:
	vector<ofImage> images;
	
	int index;
	
	int opacity;
};

#endif
