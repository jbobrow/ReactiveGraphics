//
//  SSSobject.cpp
//  fluidExample
//
//  Created by Jonathan Bobrow on 7/27/12.
//  Copyright (c) 2012 SSS,t. All rights reserved.
//

#include "SSSobject.h"
#include <iostream>

#define AMOUNT_WEIGHTED .8f

// Class to make data clean and organized for visuals
SSSobject::SSSobject(int _id, string _name){
	id = _id;
	name = _name;
	numValues = 50;
	bActive = false;
	bLoud = false;
	thresholdActive = 5;
	thresholdLoud = 60;
	amp = 1.f;
	
	for(int i=0; i<numValues; i++){
		values.push_back(0.f);
		avgValues.push_back(0.f);
	}
	
	// load text
	valueFont.loadFont("fonts/ApexNew-Book.otf", 12, true, true, true);
} 

//--------------------------------------------------------
void SSSobject::update(){
	avgValue = getAverageValue();
	
	if(value > thresholdActive)
		bActive = true;
	else
		bActive = false;
	
	if(value > thresholdLoud)
		bLoud = true;
	else
		bLoud = false;
}

//--------------------------------------------------------
void SSSobject::setThresholdLoud(float f){
	thresholdLoud = f;
}

//--------------------------------------------------------
void SSSobject::setThresholdActive(float f){
	thresholdActive = f;
} 

//--------------------------------------------------------
void SSSobject::setNumberToAverage(int n){
	numValues = n;
}

//--------------------------------------------------------
void SSSobject::setAmpValue(float a){
	amp = a;
}

//--------------------------------------------------------
void SSSobject::addValue(float v){
	v *= amp;
	v = v < 127 ? v : 127.f;
	
	for(int i=numValues-1; i>0; i--){
		values[i]=values[i-1];
	}
	values[0] = v;
	value = v;
	
	for(int i=numValues-1; i>0; i--){
		avgValues[i]=avgValues[i-1];
	}
	avgValues[0] = getAverageValue();
	avgValue = avgValues[0];
}

//--------------------------------------------------------
float SSSobject::getAverageValue(){
	float total=0;
	for(int i=0; i<numValues; i++){
		total+=values[i];
	}
	return total/(float)numValues;
}

//--------------------------------------------------------
float SSSobject::getNormalValue(){
	return value/127.f;
}

//--------------------------------------------------------
float SSSobject::getWeightedAverageValue(){
	return (value*AMOUNT_WEIGHTED + avgValue*(1-AMOUNT_WEIGHTED));
}

//--------------------------------------------------------
float SSSobject::getNormalWeightedAverageValue(){
	return getWeightedAverageValue()/127.f;
}

//--------------------------------------------------------
bool SSSobject::isLoud(){  return bLoud;  }

//--------------------------------------------------------
bool SSSobject::isActive(){  return bActive;  }

//--------------------------------------------------------
bool SSSobject::isLoudFirst(){}

//--------------------------------------------------------
bool SSSobject::isActiveFirst(){}

//--------------------------------------------------------
void SSSobject::display(){
	
	ofFill();
	ofSetColor(25, 25, 25);
	ofRect(-10,-10,110,120);
	
	ofSetColor(102, 102, 102);
	for(int i=1; i<numValues; i++){
		ofLine(numValues-i-1, 100.f*(1 - values[i]/127.f), numValues-i, 100.f*(1 - values[i-1]/127.f));
	}
	
	ofSetColor(255, 153, 0);
	for(int i=1; i<numValues; i++){
		ofLine(numValues-i-1, 100.f*(1 - avgValues[i]/127.f), numValues-i, 100.f*(1 - avgValues[i-1]/127.f));
	}
	
	//threshold lines
	ofSetColor(255, 0, 0, 25);
	ofLine(-10, 100.f*(1-thresholdLoud/127.f), 50, 100.f*(1-thresholdLoud/127.f));
	ofSetColor(0, 255, 255, 25);
	ofLine(-10, 100.f*(1-thresholdActive/127.f), 50, 100.f*(1-thresholdActive/127.f));
	
	//display avg value in orange
	//	ofSetColor(255, 153, 0);
	//	ofRect(numValues, 100.f*(1 - avgValue/127.f), 20, 100.f*avgValue/127.f);
	
	//display weighted avg value in blue
	//	ofSetColor(0, 153, 255, 153);
	//	ofRect(numValues, 100.f*(1 - getNormalWeightedAverageValue()), 20, 100.f*getNormalWeightedAverageValue());

	
	//toggle
	if(bActive)
		ofSetColor(0, 204, 204);
	else
		ofSetColor(0, 25, 25);  
	ofEllipse(numValues+40,95,10,10);
	
	//toggle
	if(bLoud){
		ofSetColor(204, 0, 0);
		ofRect(numValues, 100.f*(1 - value/127.f), 20, 100.f*value/127.f);
	}
	else{
		ofSetColor(0, 204, 204);
		ofRect(numValues, 100.f*(1 - value/127.f), 20, 100.f*value/127.f);
		ofSetColor(25, 0, 0);  
	}
	ofEllipse(numValues+40,5,10,10); 
		
	
	string vText = "val: " + ofToString(value, 1);
	string aText = "amp: " + ofToString(amp, 2);
	string tText = "cap: " + ofToString((int)thresholdLoud);
	ofSetColor(153, 153, 153);  
	valueFont.drawString(vText, 10, 145);
	valueFont.drawString(aText, 10, 175);
	valueFont.drawString(tText, 10, 205);
	ofNoFill();
	ofRect(-10,120,110,100);
}