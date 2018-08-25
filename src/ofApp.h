#pragma once

#include "ofMain.h"
#ifdef TARGET_OPENGLES
#include "ofRPIVideoPlayer.h"
#endif

class ofApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	// arduino stuff
	ofSerial serial;
	bool initOK;
	// flag OK/KO/idle to display the right picture
	string state;
	// images to be showed
	ofImage p1;
	ofImage p2;
	ofImage p3;
	ofImage p4;
	ofImage p5;
	ofImage p6;
	ofImage p7;
	ofImage p8;
	ofImage p9;
	ofImage p0;
	ofImage sc;
	ofImage idle;
	// media path
	string mediaPath;
	#ifdef TARGET_OPENGLES
	ofRPIVideoPlayer player;
	#else
	ofVideoPlayer player;
	#endif
};
