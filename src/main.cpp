#include "ofMain.h"
#include "ofApp.h"

int main() {
    ofAppGLFWWindow window;
    window.setMultiDisplayFullscreen(true);
    ofSetupOpenGL(&window, 1280, 1024, OF_FULLSCREEN);
    ofRunApp(new ofApp());

    //	ofSetupOpenGL(1280, 180, OF_WINDOW);
    //	ofRunApp(new ofApp());
}
