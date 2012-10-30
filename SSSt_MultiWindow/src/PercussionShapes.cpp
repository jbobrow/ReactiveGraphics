//
//  PercussionShapes.cpp
//  fluidExample
//
//  Created by Jonathan Bobrow on 8/14/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "PercussionShapes.h"

PercussionShapes::PercussionShapes(){
	bMortality = false;
}

PercussionShapes::~PercussionShapes(){
	
}

void PercussionShapes::addShape(int string, int xPos){
	shapes.push_back( Shape(string, xPos) );	
}

void PercussionShapes::removeAllShapes(){
	shapes.clear();
}

void PercussionShapes::update(){
	// update shapes
	for(int i=0; i<shapes.size(); i++){
		shapes[i].update();
	}
	
	// delete old percussion shapes
	for(int i=shapes.size()-1; i>=0; i--){
		if( shapes[i].alive > shapes[i].lifespan && bMortality )
			shapes.erase(shapes.begin()+i);
	}
}

void PercussionShapes::display(){
	// display shapes
	for(int i=0; i<shapes.size(); i++){
		shapes[i].display();
	}
}

void PercussionShapes::setRadius(float r){
	// 
	for(int i=0; i<shapes.size(); i++){
		shapes[i].setRadius(r);
	}
}

void PercussionShapes::setWiggle(float w){
	// 
	for(int i=0; i<shapes.size(); i++){
		shapes[i].setWiggle(w);
	}
}

void PercussionShapes::setNoise(float n){
	// 
	for(int i=0; i<shapes.size(); i++){
		shapes[i].setNoise(n);
	}
}