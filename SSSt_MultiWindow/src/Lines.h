//
//  Lines.h
//  fluidExample
//
//  Created by Jonathan Bobrow on 8/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef fluidExample_Lines_h
#define fluidExample_Lines_h

#include "ofMain.h"
#include "SSSobject.h"

//--------------------------------------------
//	Horizontal
//--------------------------------------------
class HorizontalLines{
public:
	HorizontalLines();
	~HorizontalLines();
	
	void update(vector<SSSobject> strings);
	void display();

	float	yHeights[6][51];
	
	int		spacing;
	float	stretch;
	float	lineWidth;
};

//--------------------------------------------
//	Vertical
//--------------------------------------------
struct VerticalLine{
	vector<float> values;
};


class VerticalLines{
public:
	VerticalLines();
	~VerticalLines();
	
	void update(vector<SSSobject> strings);
	void display();
	void reset();
	
	vector<VerticalLine>	lines;
	
	int		direction;
	int		spacing;
	float	stretch;
	float	lineWidth;
	
	int		mode;
};


#endif
