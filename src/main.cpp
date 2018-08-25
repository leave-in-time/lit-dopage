#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main() {
#ifdef TARGET_OPENGLES
	ofGLESWindowSettings settings;
	settings.setGLESVersion(2);
	settings.windowMode = OF_FULLSCREEN;
#else
	ofGLWindowSettings settings;
	settings.setGLVersion(3,2);
	settings.setSize(800, 480);
	settings.windowMode = OF_WINDOW;
#endif
	ofCreateWindow(settings);
	ofRunApp(new ofApp());
}
