#pragma once

#include "ofMain.h"
#ifdef TARGET_OPENGLES
#include "ofRPIVideoPlayer.h"
#endif
#include <signal.h>
#include <Poco/String.h>
using Poco::trim;
using Poco::toLower;
using namespace std;
#define INTERVAL 750


class ofApp : public ofBaseApp {
public:
	void setup();
	void updateSerial();
	void update();
	void uPassword();
	void uPasswordFail();
	void uScan();
	void uReport();
	void uWin();
	void uFail();
	void draw();
	void drawText(string text, int x, int y, bool cursor);
	void drawCursor(int x, int y);
	void dPassword();
	void dPasswordFail();
	void dScan();
	void dReport();
	void dWin();
	void dFail();
	void keyPressed(int key);
	bool isSpecialChar(int key);
	int getLocaleKey(int key);
	static void sighandler(int signal);
	// arduino stuff
	ofSerial serial;
	bool initOK;
	// flag OK/KO/idle to display the right picture
	string state;
	string prevState;
	// current app step
	string step;
	// images to be showed
	ofImage p0;
	ofImage p1;
	ofImage p2;
	ofImage p3;
	ofImage p4;
	ofImage p5;
	ofImage p6;
	ofImage p7;
	ofImage p8;
	ofImage p9;
	ofImage p10;
	ofImage p11;
	ofImage p12;
	ofImage p13;
	ofImage p14;
	ofImage p15;
	ofImage p16;
	ofImage p17;
	ofImage p18;
	ofImage p19;
	ofImage p20;
	ofImage p21;
	ofImage p22;
	ofImage p23;
	ofImage p24;
	ofImage p25;
	ofImage p26;
	ofImage p27;
	ofImage p28;
	ofImage p29;
	ofImage p30;
	ofImage p31;
	ofImage p32;
	ofImage p33;
	ofImage p34;
	ofImage p35;
	ofImage p36;
	ofImage p37;
	ofImage p38;
	ofImage p39;
	ofImage sc;
	ofImage idle;
	ofImage password;
	ofImage passwordFail;
	ofImage report;
	ofImage fail;
	ofImage win;
	// media path
	string mediaPath;
	#ifdef TARGET_OPENGLES
	ofRPIVideoPlayer player;
	#else
	ofVideoPlayer player;
	#endif
	// password
	string password1;
	string password2;
	string password3;
	string passwordBuffer;
	string firstReport; // first "report answer"
	// timestamps
	float timestamp; // to reset on win/fail
	int cursorElapsed;
	bool shouldDrawCursor;
	// font stuff
	ofTrueTypeFont font;
	// sound
	ofSoundPlayer winSound;
	bool shouldPlay;
};
