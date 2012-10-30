//
//  Shape.h
//  fluidExample
//
//  Created by Jonathan Bobrow on 8/8/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef fluidExample_Shape_h
#define fluidExample_Shape_h
#include "ofMain.h"



class SoundRing {
public:
	SoundRing(int id, ofVec2f p);
	~SoundRing();
	
	void update();
	void display();
	
	ofVec2f	pos;
	float	radius;
	int		stringID;
};



class Shape {
public:
	Shape(int n = 0, int x = 0);
	
	void update();
	void display();
	
	void setAccel(float x, float y);
	void setWiggle(float w);
	void setNoise(float n);
	void setRadius(float r);
	
	void heavyDrop();
	
	void playSound();
	
	int		lifespan;
	int		alive;
	int		hitCount;
	float	wiggle;
	int		noise;
	
private:	
	
	ofVec2f pos;
	ofVec2f cVel;
	ofVec2f vel;
	ofVec2f accel;
	
	float	delta_rotation;
	float	rotation;
	float	radius;
		
	int stringID;
	
	bool bGravity;
	
	vector<SoundRing> hits;
	
	ofImage img;
	ofSoundPlayer sound;
};


class SoftShape {
public:
	
	SoftShape(int n = 0, int x = 0);
	~SoftShape();
	
	void move();
	void display();
	
	// center point
	float	centerX;
	float	centerY;
	
	float	radius;
	float	rotAngle;
	float	accelX;
	float	accelY;
	float	springing;
	float	damping;
	int		nodes;
	
	//corner nodes
	float	nodeStartX[5];
	float	nodeStartY[5];
	float	nodeX[5];
	float	nodeY[5];
	float	angle[5];
	float	frequency[5];
	
	// soft-body dynamics
	float organicConstant;
	
	int stringID; 
};

#endif
