//
//  TitleSequence.cpp
//  ofxFensterExample
//
//  Created by Jonathan Bobrow on 8/15/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "TitleSequence.h"

#define NUM_IMAGES 20

TitleSequence::TitleSequence(){
	loadImages();
	index = 0;
}

TitleSequence::~TitleSequence(){
	
}

void TitleSequence::loadImages(){
	
	for(int i = 0; i < NUM_IMAGES; i++ ){
		ofImage img;
		string path;
		
		if(i < 10)
			path = "titles/SSSt_title_0" + ofToString(i) + ".png";
		else
			path = "titles/SSSt_title_" + ofToString(i) + ".png";

		img.loadImage(path);
		images.push_back(img);
	}
}

void TitleSequence::setImageTo(int n){
	index = n;
}

void TitleSequence::setOpacity(int a){
	opacity = a;
}

void TitleSequence::update(){
	
}

void TitleSequence::display(){
	ofEnableAlphaBlending();
	ofSetColor(255, 255, 255, opacity);
	images[index].draw(0, 0);
	ofDisableAlphaBlending();
}

void TitleSequence::next(){
	
	if( index < images.size()-1 ) index++;
}

void TitleSequence::prev(){

	if( index > 0 ) index--;
}


