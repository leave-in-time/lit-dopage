#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofHideCursor();
	// arduino stuff
	#ifdef TARGET_OPENGLES
	string port = "/dev/ttyACM0";
	#else
	string port = "/dev/tty.usbmodem1421";
	#endif
	serial.setup(port, 115200);
	initOK = false;
	// images loading
	#ifdef TARGET_OPENGLES
	mediaPath = "/media/data/";
	#else
	mediaPath = "/Users/bigx/Desktop/lit/";
	#endif
	p1.load(mediaPath + "p1.png");
	p2.load(mediaPath + "p2.png");
	p3.load(mediaPath + "p3.png");
	p4.load(mediaPath + "p4.png");
	p5.load(mediaPath + "p5.png");
	p6.load(mediaPath + "p6.png");
	p7.load(mediaPath + "p7.png");
	p8.load(mediaPath + "p8.png");
	p9.load(mediaPath + "p9.png");
	p0.load(mediaPath + "p0.png");
	idle.load(mediaPath + "idle.png");
	#ifdef TARGET_OPENGLES
	player.omxPlayer.disableLooping();
	player.load(mediaPath + "scan.mp4");
	#else
	player.load(mediaPath + "scan.mp4");
	#endif
}

//--------------------------------------------------------------
void ofApp::update() {
	// connection with arduino is OK, the app can work
	if (initOK) {
		// check for incoming data from arduino
		char first = serial.readByte();
		char second = serial.readByte();
		string prevState = state;
		if (first != OF_SERIAL_NO_DATA && first != OF_SERIAL_ERROR
			&& second != OF_SERIAL_NO_DATA && second != OF_SERIAL_ERROR) {
			string current = string(1, first) + string(1, second);
			if (current == "p0" || current == "p1" || current == "p2" ||
				current == "p3" || current == "p4" || current == "p5" ||
				current == "p6" || current == "p7" || current == "p8" ||
				current == "p9" || current == "id" || current == "sc"
			) state = current;
		}
		if (state == "sc") {
			if (prevState != "sc") {
				player.stop();
				player.play();
				player.setPaused(false);
			}
			player.update();
		} else {
			player.stop();
		}
	}
	// wait for the connection with arduino to be up
	else if (serial.isInitialized() && !initOK) {
		initOK = true;
		char init = '#';
		serial.writeByte(init);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	if (state == "p1") p1.draw(0, 0);
	else if (state == "p2") p2.draw(0, 0);
	else if (state == "p3") p3.draw(0, 0);
	else if (state == "p4") p4.draw(0, 0);
	else if (state == "p5") p5.draw(0, 0);
	else if (state == "p6") p6.draw(0, 0);
	else if (state == "p7") p7.draw(0, 0);
	else if (state == "p8") p8.draw(0, 0);
	else if (state == "p9") p9.draw(0, 0);
	else if (state == "p0") p0.draw(0, 0);
	else if (state == "sc") player.draw(0, 0, ofGetWidth(), ofGetHeight());
	else if (state == "id") idle.draw(0, 0);
}
