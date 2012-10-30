//
//  SSSobject.h
//  fluidExample
//
//  Created by Jonathan Bobrow on 7/27/12.
//  Copyright (c) 2012 SSS,t. All rights reserved.
//

#ifndef fluidExample_SSSobject_h
#define fluidExample_SSSobject_h
#include "ofMain.h"

class SSSobject{
public:	
	SSSobject(int _id, string _name);
	
	void update();
	void setThresholdLoud(float f);
	void setThresholdActive(float f);
	void setNumberToAverage(int n);
	void setAmpValue(float a);
	
	void	addValue(float v);
	float	getAverageValue();
	float	getNormalValue();
	float	getWeightedAverageValue();
	float	getNormalWeightedAverageValue();
	
	bool	isLoud();
	bool	isActive();
	
	bool	isLoudFirst();
	bool	isActiveFirst();
	
	void	display();
	
	//variables
	int id;
	string name;
	float amp;
	
	float value;
	float avgValue;
	float thresholdLoud;
	float thresholdActive;
	
	bool bActive;
	bool bLoud;
	
	bool bActiveReset;
	bool bLoudReset;
	
	vector<float> values;
	vector<float> avgValues;
	int numValues;
	
	ofTrueTypeFont valueFont;
};

#endif
