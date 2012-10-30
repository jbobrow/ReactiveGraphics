#include "testApp.h"

#define WIDTH 1024
#define HEIGHT 768
#define NUM_STRINGS 6

//--------------------------------------------------------------
void testApp::setup()
{		
//	ofSetFrameRate(30);

	ofBackground(0,0,0);
	
	// Create OSC object
    osc = SSSosc();
	osc.setupOSC( PORT );
	
	// Create control window
	controlPanel.setup();
	ofxFenster* win=ofxFensterManager::get()->createFenster(0, 0, 1024, 400, OF_WINDOW);
	win->addListener(&controlPanel);
	win->setWindowTitle("Control Panel :: SSS,t");
	
	bPlayedVideo		= false;
	
	//---------------------------
	// Set the Scene times here
	//---------------------------
	sceneTimes[0]		= 9;		// 1  Tuning
	sceneTimes[1]		= 162;		// 2  Masako 
	sceneTimes[2]		= 210; 		// 3  Intro
	sceneTimes[3]		= 252; 		// 4  WordPlay
	sceneTimes[4]		= 388; 		// 5  Improv
	sceneTimes[5]		= 456; 		// 6  Percussive
	sceneTimes[6]		= 660; 		// 7  Evidence
	sceneTimes[7]		= 756; 		// 8  Multiplies
	sceneTimes[8]		= 945; 		// 9  Oscar Fischinger
	sceneTimes[9]		= 995; 		// 10 Intro Reactive
	sceneTimes[10]		= 1109;		// 11 Slow
	sceneTimes[11]		= 1202; 	// 12 Hard
	sceneTimes[12]		= 1250; 	// 13 Credits
	//---------------------------
	
	// FLUID
    fluid.allocate(1024, 768+200, 0.5);
    fluid.setGravity(ofVec2f(0.0,-0.098));
    fluid.setDissipation(0.95);
    fluid.setVelocityDissipation(0.95);

	
	// INIT SOUND
	pShapes.addShape(1, 512);
	pShapes.shapes[0].playSound();
	pShapes.removeAllShapes();
	
	// VIDEO
	video.loadMovie("movies/Oskar_Fischinger_sansAudio.mov");
	
	// V LINES
	vLines = VerticalLines();
	
	// H LINES
	hLines = HorizontalLines();
	
	// Titles
	titles = TitleSequence();
}

//--------------------------------------------------------------
void testApp::exit()
{}

//--------------------------------------------------------------
void testApp::update()
{
	// update scene
	updateScene();
	
	// update osc
	osc.listenOSC();
	
	// update SSS objects
	for (int i = 0; i<8; i++) {
		
		switch (i) {
			case 0:		controlPanel.strings[i].addValue(osc.string1);		break;
			case 1:		controlPanel.strings[i].addValue(osc.string2);		break;
			case 2:		controlPanel.strings[i].addValue(osc.string3);		break;
			case 3:		controlPanel.strings[i].addValue(osc.string4);		break;
			case 4:		controlPanel.strings[i].addValue(osc.string5);		break;
			case 5:		controlPanel.strings[i].addValue(osc.string6);		break;
			case 6:		controlPanel.strings[i].addValue(osc.bass);			break;
			case 7:		controlPanel.strings[i].addValue(osc.drums);		break;
				
			default:	break;
		}
		
		controlPanel.strings[i].update();
	}
	// bar + beat
	controlPanel.bar = osc.bar;
	controlPanel.beat = osc.beat;
	
	//------------------------------
	//		SCENES
	//------------------------------
	
	// FLUID
	//--------------------------------------------------------------
	if( controlPanel.state == SSS_FLUID_STATE ){
		
		// FLUID ceiling	************
		fluid.begin();
		ofSetColor(0);
		ofRect(0, 0, 1024, 50);
		fluid.end();
		
		// add temporal forces for strings
		for(int i=0; i<NUM_STRINGS; i++){
			ofColor smokeColor;
			if(controlPanel.bColorFluid){
				switch(i){
					case 0:		smokeColor = ofColor(255, 0, 60);		break;
					case 1:		smokeColor = ofColor(36, 211, 119);		break;
					case 2:		smokeColor = ofColor(255, 123, 5);		break;
					case 3:		smokeColor = ofColor(57, 123, 255);		break;
					case 4:		smokeColor = ofColor(255, 220, 0);		break;
					case 5:		smokeColor = ofColor(57, 0, 255);		break;
					default:	break;
				}
			}
			else{
				smokeColor = ofFloatColor(1,1,1);
			}
			fluid.addTemporalForce(ofPoint(controlPanel.xPositions[i], HEIGHT*1.1), ofPoint(0,-20.f*controlPanel.strings[i].getNormalWeightedAverageValue()), smokeColor, 50.f*controlPanel.strings[i].getNormalWeightedAverageValue());
		}
		fluid.update();
		
		// parameters
		fluid.setGravity(ofVec2f(0.0,-ofMap(controlPanel.korg->controlValue[6], 0.f, 127.f, 0.05f, .2f)));
		fluid.setDissipation(ofMap(controlPanel.korg->controlValue[7], 0.f, 127.f, .8f, 1.1f));
		fluid.setVelocityDissipation(ofMap(controlPanel.korg->controlValue[17], 0.f, 127.f, .8f, 1.1f));
    }
	
	// SHAPE
	//--------------------------------------------------------------
	else if( controlPanel.state == SSS_SHAPE_STATE ){
		
		// add shapes
		for(int i=0; i<NUM_STRINGS; i++){
			if( controlPanel.strings[i].isLoud() ){
				if( controlPanel.strings[i].bLoudReset ){
					pShapes.addShape(i, controlPanel.xPositions[i]);
					controlPanel.strings[i].bLoudReset = false;
				}
			}
			else {
				controlPanel.strings[i].bLoudReset = true;
			}
		}
		
		// update shapes
		pShapes.update();
		
		// parameters
		pShapes.setWiggle(ofMap(controlPanel.korg->controlValue[6], 0.f, 127.f, 0.f, 20.f));
		pShapes.setRadius(ofMap(controlPanel.korg->controlValue[7], 0.f, 127.f, 5.f, 55.f));
//		pShapes.setNoise(ofMap(controlPanel.korg->controlValue[17], 0.f, 127.f, 1000.f, 10000.f));
	}
	
	// VIDEO
	//--------------------------------------------------------------
	else if( controlPanel.state == SSS_VIDEO_STATE ){
		
		if( !bPlayedVideo ){
			video.play();
			bPlayedVideo = true;	
		}
		video.idleMovie();
	}
	
	// HORIZONTAL LINE
	//--------------------------------------------------------------
	else if( controlPanel.state == SSS_HLINE_STATE ){
		hLines.update(controlPanel.strings);

		// parameters
		hLines.lineWidth	=  20.f*controlPanel.korg->controlValue[6]/127.f;
		hLines.stretch		=  1 + 20.f*controlPanel.korg->controlValue[7]/127.f;
		hLines.spacing		=  (int)(1 + 20.f*controlPanel.korg->controlValue[17]/127.f);
	}

	// VERTICAL LINE
	//--------------------------------------------------------------
	else if( controlPanel.state == SSS_VLINE_STATE ){
		vLines.update(controlPanel.strings);
		
		// parameters
		vLines.lineWidth	=  20.f*controlPanel.korg->controlValue[6]/127.f;
		vLines.stretch		=  1 + 20.f*controlPanel.korg->controlValue[7]/127.f;
		vLines.spacing		=  (int)(1 + 20.f*controlPanel.korg->controlValue[17]/127.f);
	}
	
	// TITLES
	//
	else if( controlPanel.state == SSS_TITLE_STATE ){
		titles.setImageTo(controlPanel.titleNumber);	// set title
		
		// parameters
		titles.setOpacity((int)ofMap(controlPanel.korg->controlValue[16], 0.f, 127.f, 0.f, 255.f));
	}

	
//	// Allow to play again
//	if( state != SSS_VIDEO_STATE ){
//		bPlayedVideo = false;
//	}
}

//--------------------------------------------------------------
void testApp::updateScene(){
	
	if(!controlPanel.bDoneCallibrating) return;	// don't allow Live to set scene until done callibrating
	if(controlPanel.bOverrideScene) return;
	
	if(osc.bar < sceneTimes[0]){
		controlPanel.state = SSS_TITLE_STATE;
		controlPanel.scene = "1: INTRO TITLES";
		if(curScene != 1)
			controlPanel.titleNumber = 0;	// set title
		curScene = 1;
	}
	else if(osc.bar >= sceneTimes[0] && osc.bar < sceneTimes[1]){
		controlPanel.state = SSS_VLINE_STATE;
		vLines.mode = 0;
		controlPanel.scene = "2: MASAKO -> V-LINES";
		curScene = 2;
	}
	else if(osc.bar >= sceneTimes[1] && osc.bar < sceneTimes[2]){
		controlPanel.state = SSS_TITLE_STATE;
		controlPanel.scene = "3: INTRO STRING TITLES";
		if(curScene != 3)
			controlPanel.titleNumber = 1;	// set title
		curScene = 3;
	}
	else if(osc.bar >= sceneTimes[2] && osc.bar < sceneTimes[3]){
		controlPanel.state = SSS_TITLE_STATE;
		controlPanel.scene = "4: WORDPLAY -> WORDS";
		if(curScene != 4)
			controlPanel.titleNumber = 1;	// set title
		curScene = 4;
	}
	else if(osc.bar >= sceneTimes[3] && osc.bar < sceneTimes[4]){
		controlPanel.state = SSS_HLINE_STATE;
		controlPanel.scene = "5: IMPROV -> H-LINES";
		curScene = 5;
	}
	else if(osc.bar >= sceneTimes[4] && osc.bar < sceneTimes[5]){
		controlPanel.state = SSS_SHAPE_STATE;
		controlPanel.scene = "6: PERCUSSIVE SHAPES";
		curScene = 6;
	}
	else if(osc.bar >= sceneTimes[5] && osc.bar < sceneTimes[6]){
		controlPanel.state = SSS_VLINE_STATE;
		vLines.mode = 1;
		controlPanel.scene = "7: EVIDENCE OF POP -> V-LINES";
		curScene = 7;
	}
	else if(osc.bar >= sceneTimes[6] && osc.bar < sceneTimes[7]){
		controlPanel.state = SSS_HLINE_STATE;
		controlPanel.scene = "8: MULTIPLIES -> H-LINES";
		curScene = 8;
	}
	else if(osc.bar >= sceneTimes[7] && osc.bar < sceneTimes[8]){
		controlPanel.state = SSS_VIDEO_STATE;
		controlPanel.scene = "9: OSCAR FISCHINGER -> VIDEO";
		curScene = 9;
	}
	else if(osc.bar >= sceneTimes[8] && osc.bar < sceneTimes[9]){
		controlPanel.state = SSS_TITLE_STATE;
		controlPanel.scene = "10: REACTIVE BODIES -> TITLES";
		if(curScene != 10)
			controlPanel.titleNumber = 9;	// set title
		curScene = 10;
	}
	else if(osc.bar >= sceneTimes[9] && osc.bar < sceneTimes[10]){
		controlPanel.state = SSS_FLUID_STATE;
		controlPanel.scene = "11: SLOW -> SMOKE";
		curScene = 11;
	}
	else if(osc.bar >= sceneTimes[10] && osc.bar < sceneTimes[11]){
		controlPanel.state = SSS_FLUID_STATE;
		controlPanel.bColorFluid = true;
		controlPanel.scene = "12: HARD -> SMOKE COLOR";
		curScene = 12;
	}
	else if(osc.bar >= sceneTimes[11] && osc.bar < sceneTimes[12]){
		controlPanel.state = SSS_TITLE_STATE;
		controlPanel.scene = "13: END CREDITS";
		if(curScene != 13)
			controlPanel.titleNumber = 18;	// set title
		curScene = 13;
	}
	else if(osc.bar >= sceneTimes[12]){
		controlPanel.state = SSS_TITLE_STATE;
		controlPanel.titleNumber = 18;	// set title
		controlPanel.scene = "Go Home Already!!!";
		curScene = 14;
	}
}


//--------------------------------------------------------------
void testApp::draw()
{	
	// CALLIBRATE
	if( controlPanel.state == SSS_CALLI_STATE ){
		ofPushStyle();
		for( int i = 0; i < 6; i++ ){
			ofNoFill();
			ofSetColor(255, 255, 255);
			ofSetLineWidth(5);
			ofLine(controlPanel.xPositions[i], 0, controlPanel.xPositions[i], 768);
		}
		ofPopStyle();
	}
	
	// SHAPE
	if( controlPanel.state == SSS_SHAPE_STATE ){
		pShapes.display();
	}
	
	// FLUID
	else if( controlPanel.state == SSS_FLUID_STATE ){
		fluid.draw();
	}
	
	// VIDEO
	else if( controlPanel.state == SSS_VIDEO_STATE ){
		video.draw(50, 30, 924, 693);
	}
	
	// HORIZONTAL LINE
	else if( controlPanel.state == SSS_HLINE_STATE ){
		hLines.display();
	}

	// VERTICAL LINE
	else if( controlPanel.state == SSS_VLINE_STATE ){
		vLines.display();
	}
	
	// TITLE STATE
	else if( controlPanel.state == SSS_TITLE_STATE ){
		titles.display();
	}
}

//--------------------------------------------------------------
void testApp::setState(int s){
	controlPanel.state = s;
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{	
	// MODIFIERS
	if( key == 'c' )
		pShapes.removeAllShapes();
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{
}