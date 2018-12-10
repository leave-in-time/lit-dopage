#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetEscapeQuitsApp(false);
	ofHideCursor();
	// arduino stuff
	#ifdef TARGET_OPENGLES
	string port = "/dev/ttyACM0";
	#else
	string port = "/dev/tty.usbmodem14201";
	#endif
	serial.setup(port, 115200);
	initOK = false;
	// images loading
	#ifdef TARGET_OPENGLES
	mediaPath = "/media/data/";
	#else
	mediaPath = "/Users/bigx/Desktop/lit/";
	#endif
	p0.load(mediaPath + "00.png");
	p1.load(mediaPath + "01.png");
	p2.load(mediaPath + "02.png");
	p3.load(mediaPath + "03.png");
	p4.load(mediaPath + "04.png");
	p5.load(mediaPath + "05.png");
	p6.load(mediaPath + "06.png");
	p7.load(mediaPath + "07.png");
	p8.load(mediaPath + "08.png");
	p9.load(mediaPath + "09.png");
	p10.load(mediaPath + "10.png");
	p11.load(mediaPath + "11.png");
	p12.load(mediaPath + "12.png");
	p13.load(mediaPath + "13.png");
	p14.load(mediaPath + "14.png");
	p15.load(mediaPath + "15.png");
	p16.load(mediaPath + "16.png");
	p17.load(mediaPath + "17.png");
	p18.load(mediaPath + "18.png");
	p19.load(mediaPath + "19.png");
	p20.load(mediaPath + "20.png");
	p21.load(mediaPath + "21.png");
	p22.load(mediaPath + "22.png");
	p23.load(mediaPath + "23.png");
	p24.load(mediaPath + "24.png");
	p25.load(mediaPath + "25.png");
	p26.load(mediaPath + "26.png");
	p27.load(mediaPath + "27.png");
	p28.load(mediaPath + "28.png");
	p29.load(mediaPath + "29.png");
	p30.load(mediaPath + "30.png");
	p31.load(mediaPath + "31.png");
	p32.load(mediaPath + "32.png");
	p33.load(mediaPath + "33.png");
	p34.load(mediaPath + "34.png");
	p35.load(mediaPath + "35.png");
	p36.load(mediaPath + "36.png");
	p37.load(mediaPath + "37.png");
	p38.load(mediaPath + "38.png");
	p39.load(mediaPath + "39.png");
	idle.load(mediaPath + "idle.png");
	password.load(mediaPath + "password.png");
	passwordFail.load(mediaPath + "password-fail.png");
	report.load(mediaPath + "report.png");
	fail.load(mediaPath + "fail.png");
	win.load(mediaPath + "win.png");
	// video loading
	#ifdef TARGET_OPENGLES
	player.omxPlayer.disableLooping();
	#endif
	player.load(mediaPath + "scan.mp4");
	// passwords
	ofBuffer buff = ofBufferFromFile(mediaPath + "password1.txt");
	password1 = trim(buff.getText());
	buff = ofBufferFromFile(mediaPath + "password2.txt");
	password2 = trim(buff.getText());
	buff = ofBufferFromFile(mediaPath + "password3.txt");
	password3 = trim(buff.getText());
	// steps
	step = "password";
	// font
	font.load("Lato-Bold.ttf", 32);

	// prevent SIGINT, SIGTERM and SIGKILL
	#ifdef TARGET_OPENGLES
	signal(SIGINT, &ofApp::sighandler);
	signal(SIGTERM, &ofApp::sighandler);
	signal(SIGKILL, &ofApp::sighandler);
	#endif
}

//--------------------------------------------------------------
void ofApp::sighandler(int signal) {
	// noop
	ofLog(OF_LOG_NOTICE, "SIGNAL!!");
}

//--------------------------------------------------------------
void ofApp::updateSerial() {
	// connection with arduino is not OK, do nothing
	if (!initOK) return;

	// check for incoming data from arduino
	char first = serial.readByte();
	char second = serial.readByte();
	prevState = state;
	if (first != OF_SERIAL_NO_DATA && first != OF_SERIAL_ERROR
		&& second != OF_SERIAL_NO_DATA && second != OF_SERIAL_ERROR) {
		string current = string(1, first) + string(1, second);
		if (
			current == "00" || current == "01" || current == "02" || current == "03" || current == "04" || current == "05" || current == "06" || current == "07" || current == "08" || current == "09" ||
			current == "10" || current == "11" || current == "12" || current == "13" || current == "14" || current == "15" || current == "16" || current == "17" || current == "18" || current == "19" ||
			current == "20" || current == "21" || current == "22" || current == "23" || current == "24" || current == "25" || current == "26" || current == "27" || current == "28" || current == "29" ||
			current == "30" || current == "31" || current == "32" || current == "33" || current == "34" || current == "35" || current == "36" || current == "37" || current == "38" || current == "39" ||
			current == "id" || current == "sc" || current == "re"
		) {
			state = current;
			if (state == "re") step = "report";
			else step = "scan";
		}
	}
}

//--------------------------------------------------------------
void ofApp::update() {
	updateSerial();
	if (step == "password") uPassword();
	else if (step == "passwordFail") uPasswordFail();
	else if (step == "scan") uScan();
	else if (step == "report") uReport();
	else if (step == "win") uWin();
	else if (step == "fail") uFail();
	// wait for the connection with arduino to be up
	if (serial.isInitialized() && !initOK) {
		initOK = true;
		char init = '#';
		serial.writeByte(init);
	}
}

//--------------------------------------------------------------
void ofApp::uPassword() {
	// ofLogNotice(__func__, "update password");
}

//--------------------------------------------------------------
void ofApp::uPasswordFail() {
	// ofLogNotice(__func__, "update password fail");
	if (ofGetElapsedTimef() - timestamp > 3.0) step = "password";
}

//--------------------------------------------------------------
void ofApp::uScan() {
	if (state == "sc") {
		if (prevState != "sc") {
			#ifdef TARGET_OPENGLES
			player.omxPlayer.restartMovie();
			#else
			player.stop();
			#endif
			player.setPaused(false);
		}
		#ifndef TARGET_OPENGLES
		player.update();
		#endif
	}
	else if (state == "re") {
		step = "report";
	}
	else {
		player.stop();
		player.setPaused(true);
	}
}

//--------------------------------------------------------------
void ofApp::uReport() {
	// ofLogNotice(__func__, "update report");
}

//--------------------------------------------------------------
void ofApp::uWin() {
	// ofLogNotice(__func__, "update win");
	serial.writeByte('$');
	if (ofGetElapsedTimef() - timestamp > 10.0) {
		serial.writeByte('#');
		step = "password";
	}
}

//--------------------------------------------------------------
void ofApp::uFail() {
	// ofLogNotice(__func__, "update fail");
	if (ofGetElapsedTimef() - timestamp > 5.0) {
		step = "scan";
		state = "id";
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	if (step == "password") dPassword();
	else if (step == "passwordFail") dPasswordFail();
	else if (step == "scan") dScan();
	else if (step == "report") dReport();
	else if (step == "win") dWin();
	else if (step == "fail") dFail();
}

//--------------------------------------------------------------
void ofApp::drawText(string text, int x, int y, bool cursor){
	ofSetColor(0, 0, 0);
	font.drawString(text, x, y);
	ofRectangle rect = font.getStringBoundingBox(text, x, y);
	if (cursor) {
		if (rect.width > 0) drawCursor(rect.x + rect.width + 5, y - 32);
		else drawCursor(x, y - 32);
	}
	ofSetColor(255, 255, 255);
}

//--------------------------------------------------------------
void ofApp::drawCursor(int x, int y){
	int currentTime = ofGetElapsedTimeMillis();
	if (currentTime - cursorElapsed > INTERVAL) {
		shouldDrawCursor = !shouldDrawCursor;
		cursorElapsed = currentTime;
	}
	if (shouldDrawCursor) ofDrawRectangle(x, y, 10, 32);
}

//--------------------------------------------------------------
void ofApp::dPassword() {
	password.draw(0,0);
	drawText(passwordBuffer, 225, 402, true);
}

//--------------------------------------------------------------
void ofApp::dPasswordFail() {
	passwordFail.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::dScan() {
	if (state == "00") p0.draw(0, 0);
	else if (state == "01") p1.draw(0, 0);
	else if (state == "02") p2.draw(0, 0);
	else if (state == "03") p3.draw(0, 0);
	else if (state == "04") p4.draw(0, 0);
	else if (state == "05") p5.draw(0, 0);
	else if (state == "06") p6.draw(0, 0);
	else if (state == "07") p7.draw(0, 0);
	else if (state == "08") p8.draw(0, 0);
	else if (state == "09") p9.draw(0, 0);
	else if (state == "10") p10.draw(0, 0);
	else if (state == "11") p11.draw(0, 0);
	else if (state == "12") p12.draw(0, 0);
	else if (state == "13") p13.draw(0, 0);
	else if (state == "14") p14.draw(0, 0);
	else if (state == "15") p15.draw(0, 0);
	else if (state == "16") p16.draw(0, 0);
	else if (state == "17") p17.draw(0, 0);
	else if (state == "18") p18.draw(0, 0);
	else if (state == "19") p19.draw(0, 0);
	else if (state == "20") p20.draw(0, 0);
	else if (state == "21") p21.draw(0, 0);
	else if (state == "22") p22.draw(0, 0);
	else if (state == "23") p23.draw(0, 0);
	else if (state == "24") p24.draw(0, 0);
	else if (state == "25") p25.draw(0, 0);
	else if (state == "26") p26.draw(0, 0);
	else if (state == "27") p27.draw(0, 0);
	else if (state == "28") p28.draw(0, 0);
	else if (state == "29") p29.draw(0, 0);
	else if (state == "30") p30.draw(0, 0);
	else if (state == "31") p31.draw(0, 0);
	else if (state == "32") p32.draw(0, 0);
	else if (state == "33") p33.draw(0, 0);
	else if (state == "34") p34.draw(0, 0);
	else if (state == "35") p35.draw(0, 0);
	else if (state == "36") p36.draw(0, 0);
	else if (state == "37") p37.draw(0, 0);
	else if (state == "38") p38.draw(0, 0);
	else if (state == "39") p39.draw(0, 0);
	else if (state == "sc") player.draw(0, 0, ofGetWidth(), ofGetHeight());
	else if (state == "id") idle.draw(0, 0);
}

//--------------------------------------------------------------
void ofApp::dReport() {
	report.draw(0,0);
	if (firstReport == "") {
		drawText(passwordBuffer, 239, 309, true);
	}
	else {
		drawText(firstReport, 239, 309, false);
		drawText(passwordBuffer, 316, 382, true);
	}
}

//--------------------------------------------------------------
void ofApp::dWin() {
	win.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::dFail() {
	fail.draw(0,0);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (step == "password" || step == "report") {
		// if we didn't hit return, add the key to our string
		if (key != OF_KEY_RETURN) {
			if (key == OF_KEY_BACKSPACE && passwordBuffer.size() > 0) passwordBuffer.erase(passwordBuffer.end() - 1);
			#ifdef TARGET_OPENGLES
			else if (!isSpecialChar(key)) passwordBuffer += getLocaleKey(key);
			#else
			else passwordBuffer += key;
			#endif
		}
		// hit Return, check password
		else {
			if (step == "password") {
				if (toLower(passwordBuffer) == password1) {
					step = "scan";
					state = "id";
				}
				else {
					timestamp = ofGetElapsedTimef();
					step = "passwordFail";
				}
			}
			else if (step == "report") {
				if (firstReport == "") firstReport = toLower(passwordBuffer);
				else {
					timestamp = ofGetElapsedTimef();
					if (firstReport == password2 && toLower(passwordBuffer) == password3) step = "win";
					else step = "fail";
					firstReport = "";
				}
			}
			// ofLogNotice(__func__, passwordBuffer);
			passwordBuffer = "";
		}
	}
}

//--------------------------------------------------------------
bool ofApp::isSpecialChar(int key) {
	switch (key) {
		case OF_KEY_ESC:
		case OF_KEY_TAB:
		case OF_KEY_DEL:
		case OF_KEY_BACKSPACE:
		case OF_KEY_F1:
		case OF_KEY_F2:
		case OF_KEY_F3:
		case OF_KEY_F4:
		case OF_KEY_F5:
		case OF_KEY_F6:
		case OF_KEY_F7:
		case OF_KEY_F8:
		case OF_KEY_F9:
		case OF_KEY_F10:
		case OF_KEY_F11:
		case OF_KEY_F12:
		case OF_KEY_LEFT:
		case OF_KEY_UP:
		case OF_KEY_RIGHT:
		case OF_KEY_DOWN:
		case OF_KEY_PAGE_UP:
		case OF_KEY_PAGE_DOWN:
		case OF_KEY_HOME:
		case OF_KEY_END:
		case OF_KEY_INSERT:
		case OF_KEY_CONTROL:
		case OF_KEY_ALT:
		case OF_KEY_SHIFT:
		case OF_KEY_SUPER:
		case OF_KEY_LEFT_SHIFT:
		case OF_KEY_RIGHT_SHIFT:
		case OF_KEY_LEFT_CONTROL:
		case OF_KEY_RIGHT_CONTROL:
		case OF_KEY_LEFT_ALT:
		case OF_KEY_RIGHT_ALT:
		case OF_KEY_LEFT_SUPER:
		case OF_KEY_RIGHT_SUPER:
			return true;
			break;
		// disable some bad keys
		case 0:
		// case 1: // same as OF_KEY_SHIFT
		case 42:
		case 255:
			return true;
			break;
		default:
			return false;
			break;
	}
}

//--------------------------------------------------------------
int ofApp::getLocaleKey(int key) {
	switch (key) {
		// 1 to 0 with shift
		case 33: return '1'; break;
		case 64: return '2'; break;
		case 35: return '3'; break;
		case 36: return '4'; break;
		case 37: return '5'; break;
		case 94: return '6'; break;
		case 38: return '7'; break;
		case 42: return '8'; break;
		case 40: return '9'; break;
		case 41: return '0'; break;
		// 1 to 0 without shift
		case 49: return '&'; break;
		case 50: return 'e'; break;
		case 51: return '"'; break;
		case 52: return '\''; break;
		case 53: return '('; break;
		case 54: return '-'; break;
		case 55: return 'e'; break;
		case 56: return '_'; break;
		case 57: return 'c'; break;
		case 48: return 'a'; break;
		// )/° key
		case 45: return ')'; break;
		#ifdef TARGET_OPENGLES
		case 95: return '°'; break;
		#endif
		// next to "return" key
		case 91: return '^'; break;
		case 123: return '^'; break;
		case 93: return '$'; break;
		case 125: return '$'; break;
		case 39: return 'u'; break;
		case 34: return '%'; break;
		case 92: return '*'; break;
		case 59: return 'm'; break;
		case 58: return 'M'; break;
		case 109: return ','; break;
		case 77: return '?'; break;
		case 44: return ';'; break;
		case 60: return '.'; break;
		case 46: return ':'; break;
		case 62: return '/'; break;
		case 47: return '!'; break;
		case 63: return '!'; break;
		// qwerty --> azerty
		case 113: return 'a'; break;
		case 81: return 'A'; break;
		case 119: return 'z'; break;
		case 87: return 'Z'; break;
		case 122: return 'w'; break;
		case 90: return 'W'; break;
		case 97: return 'q'; break;
		case 65: return 'Q'; break;
		// ² key
		#ifdef TARGET_OPENGLES
		case 10: return '²'; break;
		#endif
		// defaults
		default: return key; break;
	}
}
