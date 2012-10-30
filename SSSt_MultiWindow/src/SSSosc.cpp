//
//  SSSosc.cpp
//  fluidExample
//
//  Created by Jonathan Bobrow on 7/27/12.
//  Copyright (c) 2012 SSS,t. All rights reserved.
//

#include "SSSosc.h"
#include <iostream>

//--------------------------------------------------------------
SSSosc::SSSosc(){
}

//--------------------------------------------------------------
void SSSosc::setupOSC(int n){
	setup(n);
}

//--------------------------------------------------------------
void SSSosc::listenOSC(){
	// check for waiting messages
	while( hasWaitingMessages() )
	{
		// get the next message
		ofxOscMessage m;
		getNextMessage( &m );
		
		// check for mouse moved message
		if ( m.getAddress() == "/var0y" )
		{
			bass = m.getArgAsFloat( 0 );
		}
		else if( m.getAddress() == "/var1Y" ){
			string1 = m.getArgAsFloat( 0 );			
		}
		else if( m.getAddress() == "/var2Y" ){
			string2 = m.getArgAsFloat( 0 );			
		}
		else if( m.getAddress() == "/var3Y" ){
			string3 = m.getArgAsFloat( 0 );			
		}
		else if( m.getAddress() == "/var4Y" ){
			string4 = m.getArgAsFloat( 0 );			
		}
		else if( m.getAddress() == "/var5Y" ){
			string5 = m.getArgAsFloat( 0 );			
		}
		else if( m.getAddress() == "/var6Y" ){
			string6 = m.getArgAsFloat( 0 );			
		}
		else if( m.getAddress() == "/var7Y" ){
			drums = m.getArgAsFloat( 0 );			
		}
		else if( m.getAddress() == "/bar" ) {
			bar = m.getArgAsInt32(0);
		}
		else if( m.getAddress() == "/beat" ) {
			beat = m.getArgAsInt32(0);
		}
		else if( m.getAddress() == "/unit" ) {
			unit = m.getArgAsFloat(0);
		}
//		printf("-----------------------\n");
//		printf("bass: %i\n", (int)bass);
//		printf("string 1: %i\n", (int)string1);
//		printf("string 2: %i\n", (int)string2);
//		printf("string 3: %i\n", (int)string3);
//		printf("string 4: %i\n", (int)string4);
//		printf("string 5: %i\n", (int)string5);
//		printf("string 6: %i\n", (int)string6);
//		printf("drums: %i\n", (int)drums);
//		printf("-----------------------\n\n");
		
	}
}