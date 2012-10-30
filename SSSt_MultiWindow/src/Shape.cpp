//
//  Shape.cpp
//  fluidExample
//
//  Created by Jonathan Bobrow on 8/8/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "Shape.h"
#include "SSScommon.h"

//-------------------------------------------------
//-------------------------------------------------
SoundRing::SoundRing(int id, ofVec2f p){
	pos = p;
	radius = 0;
	stringID = id;
}


SoundRing::~SoundRing(){
	
}

void SoundRing::update(){
	radius += 3;
}

void SoundRing::display(){
	ofPushStyle();
	ofNoFill();
	// add smoothing to these shapes
	ofSetLineWidth((5*(200-radius)/200.f));
	ofEnableAlphaBlending();
	switch (stringID) {
		case 0:		ofSetColor(SSScommon::red, 204-radius);			break;
		case 1:		ofSetColor(SSScommon::green, 204-radius);		break;
		case 2:		ofSetColor(SSScommon::orange, 204-radius);		break;
		case 3:		ofSetColor(SSScommon::blue, 204-radius);		break;
		case 4:		ofSetColor(SSScommon::yellow, 204-radius);		break;
		case 5:		ofSetColor(SSScommon::purple, 204-radius);		break;
		default:	break;
	}
	ofEnableSmoothing();
	ofCircle(pos.x, pos.y, radius);
	ofDisableSmoothing();
	ofDisableAlphaBlending();
	ofPopStyle();
}


//-------------------------------------------------
//-------------------------------------------------
Shape::Shape( int n , int x){
	
	stringID = n;
	
	pos.set(x, 450);
	float chance = ofRandom(1);
	cVel.set(chance>.5?1:-1, -1);
	vel = cVel;
	accel.set(0, 0);
	
	rotation	= ofRandom(0,360);
	delta_rotation	= ofRandom(-1,1);
	radius		= ofRandom(10,15);
	hitCount	= 0.f;
	lifespan	= (int)ofRandom(100,500);
	alive		= 0;
	wiggle		= 10.f;
	noise		= 5000.f;
	
	bGravity = false;
	
//	img.loadImage("soft_ball.png");
}

void Shape::update(){
	
	alive++;
	
	//gravity
	if( bGravity ){
		vel+=accel;
		pos+=vel;
	}
	else
		pos+=cVel;
	
	rotation += delta_rotation;
	
	if( pos.x + radius >= 1024 || pos.x - radius <= 0 ){
		cVel.x = -cVel.x;
		vel.x = -vel.x;
		playSound();
		delta_rotation = -delta_rotation;
		hits.push_back(SoundRing(stringID, pos));
		hitCount++;
	}
	if( pos.y + radius >= 768 || pos.y - radius <= 0 ){
		cVel.y = -cVel.y;
		vel.y = -vel.y;
		playSound();
		delta_rotation = -delta_rotation;
		hits.push_back(SoundRing(stringID, pos));
		hitCount++;
	}
	
	for(int i=0; i<hits.size(); i++){
		hits[i].update();
	}
	
	// delete faded out Sound Rings
	for(int i=hits.size()-1; i>=0; i--){
		if( hits[i].radius > 200 )
			hits.erase(hits.begin()+i);
	}
}

void Shape::setAccel(float x, float y){
	accel.set(x, y);
}

void Shape::setWiggle(float w){
	wiggle = w;
}

void Shape::setNoise(float n){
	noise = (int)n;
}

void Shape::setRadius(float r){
	radius = ofRandom(r-2,r+2);
}

void Shape::heavyDrop(){
	accel.set(0, 1.f);
}

void Shape::display(){
	// Sound Rings
	for(int i=0; i<hits.size(); i++){
		hits[i].display();
	}
	
	// draw current position
	ofFill();
	switch (stringID) {
		case 0:		ofSetColor(SSScommon::red);			break;
		case 1:		ofSetColor(SSScommon::green);		break;
		case 2:		ofSetColor(SSScommon::orange);		break;
		case 3:		ofSetColor(SSScommon::blue);		break;
		case 4:		ofSetColor(SSScommon::yellow);		break;
		case 5:		ofSetColor(SSScommon::purple);		break;
		default:	break;
	}
	ofPushStyle();
	ofSetColor(255,255,255);	//white with color rings
	ofSetLineWidth(1.f);
	ofNoFill();
//	ofEnableAlphaBlending();
	ofEnableSmoothing();
	ofPushMatrix();
	ofTranslate(pos.x, pos.y);
	ofRotate(rotation);
	
	ofBeginShape();
	for(int i=0; i<8; i++){
		ofCurveVertex(wiggle*ofNoise(i*ofGetElapsedTimeMillis()%noise) + radius*cos(i*TWO_PI/6.f), wiggle*ofNoise(i*ofGetElapsedTimeMillis()%noise) + radius*sin(i*TWO_PI/6.f));
	}
	ofCurveVertex(4*ofNoise(0) + radius, 4*ofNoise(0));
	ofEndShape();
	
	ofBeginShape();
	for(int i=0; i<8; i++){
		ofCurveVertex(wiggle*ofNoise(i*ofGetElapsedTimeMillis()%noise) + .5*radius*cos(i*TWO_PI/6.f), wiggle*ofNoise(i*ofGetElapsedTimeMillis()%noise) + .5*radius*sin(i*TWO_PI/6.f));
	}
	ofCurveVertex(wiggle*ofNoise(0) + .5*radius, wiggle*ofNoise(0));
	ofEndShape();

	//img.draw(-15,-15);
	ofPopMatrix();
	//ofCircle(pos.x, pos.y, radius);
	ofDisableSmoothing();
//	ofDisableAlphaBlending();
	ofPopStyle();
}

void Shape::playSound(){
	sound.setMultiPlay(true);
	switch (stringID) {
		case 0:		sound.loadSound("sounds/sound_0.wav");		break;
		case 1:		sound.loadSound("sounds/sound_1.wav");		break;
		case 2:		sound.loadSound("sounds/sound_2.wav");		break;
		case 3:		sound.loadSound("sounds/sound_3.wav");		break;
		case 4:		sound.loadSound("sounds/sound_4.wav");		break;
		case 5:		sound.loadSound("sounds/sound_5.wav");		break;
		case 6:		sound.loadSound("sounds/sound_6.wav");		break;
		default:	break;
	}
	sound.play();
}



//-------------------------------------------------
// This is not yet functional!!! Don't use :-/
//-------------------------------------------------
SoftShape::SoftShape( int n , int x){

	nodes = 5;
	
	// iniitalize frequencies for corner nodes
    for (int i=0; i<nodes; i++){
		frequency[i] = ofRandom(5, 12);
    }
	
	accelX = 3;
    accelY = 3;

}

SoftShape::~SoftShape(){
	
}

void SoftShape::move(){
	
	// account for edges
	if( centerX >= 1024 || centerX <= 0 ){
		accelX = -accelX;
	}
	if( centerY >= 768-50 || centerY <= 50 ){
		accelY = -accelY;
	}
	
    // move predator's center
    centerX += accelX;
    centerY += accelY;
	
    //move nodes
    for (int i=0; i<nodes; i++){
		nodeX[i] = nodeStartX[i]+sin(TWO_PI*angle[i]/360.f)*(accelX*2);
		nodeY[i] = nodeStartY[i]+sin(TWO_PI*angle[i]/360.f)*(accelY*2);
		angle[i]+=frequency[i];
    }
}

void SoftShape::display(){
	//  calculate node  starting locations
    for (int i=0; i<nodes; i++){
		nodeStartX[i] = centerX+cos(TWO_PI*rotAngle/360.f)*radius;
		nodeStartY[i] = centerY+sin(TWO_PI*rotAngle/360.f)*radius;
		rotAngle += 360.0/nodes;
    }
	
    // draw polygon
    ofFill();
	ofSetColor(255, 255, 255);
    ofBeginShape();
    for (int i=0; i<nodes; i++){
		ofCurveVertex(nodeX[i], nodeY[i]);
    }
    for (int i=0; i<nodes-1; i++){
		ofCurveVertex(nodeX[i], nodeY[i]);
    }
    ofEndShape();
}