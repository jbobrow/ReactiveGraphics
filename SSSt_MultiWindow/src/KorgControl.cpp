//
//  KorgControl.cpp
//  fluidExample
//
//  Created by Jonathan Bobrow on 8/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "KorgControl.h"
#include <iostream>


//--------------------------------------------------------
KorgControl::KorgControl(){
	// print input ports to console
	midiIn.listPorts(); // via instance
	//ofxMidiIn::listPorts(); // via static as well
	
	// open port by number (you may need to change this)
	midiIn.openPort(0);
	//midiIn.openPort("IAC Pure Data In");	// by name
	//midiIn.openVirtualPort("ofxMidiIn Input");	// open a virtual port
	
	// don't ignore sysex, timing, & active sense messages,
	// these are ignored by default
	midiIn.ignoreTypes(false, false, false);
	
	// add KorgControl as a listener
	midiIn.addListener(this);
	
	// print received messages to the console
	midiIn.setVerbose(false);
}


//--------------------------------------------------------
void KorgControl::cleanUp(){
	// clean up
	midiIn.closePort();
	midiIn.removeListener(this);
}

//--------------------------------------------------------
void KorgControl::update(){

//		// Knobs 0-7
//		
//		// Sliders 10-17
//			
//		// Toggle Buttons 20-27
//		
//		// Instant Buttons 30-37
//			
//		// Instant Buttons 40-47
//	
//		// Instant Buttons (bottom left) 50-54
//		
//		// Instant Buttons (Scene Advance) 60-62
//			
}

//--------------------------------------------------------
void KorgControl::newMidiMessage(ofxMidiMessage &msg){
	// make a copy of the latest message
	midiMessage = msg;
	controlValue[midiMessage.control] = midiMessage.value;
	
//	printf("control: %i, value: %i\n", midiMessage.control, midiMessage.value);

}