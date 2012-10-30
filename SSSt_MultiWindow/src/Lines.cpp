//
//  Lines.cpp
//  fluidExample
//
//  Created by Jonathan Bobrow on 8/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Lines.h"

//--------------------------------------------
//	Horizontal
//--------------------------------------------
HorizontalLines::HorizontalLines(){
	for( int i=0; i < 6; i++ ){
		for( int j=0; j < 51; j++ ){
			yHeights[i][j] = 0.f;
		}
	}
	
	lineWidth = .1;
	spacing = 10;
	stretch = 10;
}

HorizontalLines::~HorizontalLines(){
	
}

void HorizontalLines::update(vector<SSSobject> strings){
	//update the 6 string values
	for(int i=0; i<6; i++){
		for( int j=50; j > 0; j-- ){
			yHeights[i][j] = yHeights[i][j-1];
		}
		yHeights[i][0] = 10 * stretch * strings[i].getNormalValue();
	}
}

void HorizontalLines::display(){
	//display prev values
	
	//display cur values
	ofPushStyle();
	ofSetLineWidth(lineWidth);
	ofPolyline line;
	ofNoFill();
	for(int j=0; j < 51; j++){
		
		ofSetColor(255-5*j, 255-5*j, 255-5*j);
		ofBeginShape();
		ofVertex(-100, 768 - spacing*j);
		for(int i=0; i<6; i++){
			ofVertex((1+i)*1024/7, 768 - yHeights[i][j] - spacing*j);
		}
		ofVertex(1124, 768 - spacing*j);
		ofEndShape();
	}
	ofPopStyle();	
	//save cur values (shift by factor)
}


//--------------------------------------------
//	Vertical
//--------------------------------------------
VerticalLines::VerticalLines(){
	
	// create 6 vertical lines
	for( int i=0; i < 6; i++ ){
	
		VerticalLine l;

		// each line will hold 768 values
		for( int j=0; j < 768; j++ ){
			
			l.values.push_back(0.f);
		}
		lines.push_back(l);
	}
	
	lineWidth = .1;
	direction = -1;
	spacing = 1;
	stretch = 1;
	
	mode = 0;
}

VerticalLines::~VerticalLines(){
	
}

void VerticalLines::update(vector<SSSobject> strings){
	// bump values back and add latest to front
	// also, change direction of line everytime we add a value
	direction *= -1;
	
	for( int i=0; i < 6; i++ ){
		
		if( mode == 0 ){
			
			for( int j=0; j < lines[i].values.size()-1; j++ ){
			
				lines[i].values[j+1] = lines[i].values[j];
			}
			lines[i].values[0] = direction * strings[i].getNormalValue() * 50;
		}
		
		else if( mode == 1 ){
			
			for( int j=lines[i].values.size()-1; j > 0; j-- ){
				
				lines[i].values[j] = lines[i].values[j-1];
			}
			lines[i].values[0] = direction * strings[i].getNormalValue() * 50;
		
		}

	}
}

void VerticalLines::display(){
	//draw lines left to right across center point, magnitude of string value
	
	ofPushStyle();
	ofEnableAlphaBlending();
	ofSetLineWidth(lineWidth);
	
	if( mode == 1 ) stretch = (stretch < 3) ? 3: stretch;
	
	for( int i=0; i<6; i++ ){
		
		for( int j=0; j < lines[i].values.size()-1; j+= spacing ){
			float opacity = (j*stretch) < 768 ? (255*(768-j*stretch)/768.f) : 0;
			ofSetColor(255, 255, 255, (int)opacity);
			ofLine((1+i)*1024/7.f + lines[i].values[j], 768-j*stretch, (1+i)*1024/7.f - lines[i].values[j+1], 768-j*stretch);
		}
	}
	
	ofDisableAlphaBlending();
	ofPopStyle();
}

void VerticalLines::reset(){
	
	for( int i=0; i<6; i++ ){
		
		for( int j=0; j < lines[i].values.size(); j++ ){
			
			lines[i].values[j] = 0.f;
		}
	}
}
