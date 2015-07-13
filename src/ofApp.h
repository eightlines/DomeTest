#pragma once

#include "ofMain.h"
#include "ofxMemoryUsage.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyReleased(int key);
private:
    vector<ofVideoPlayer> videos;
    vector<ofImage> templates;
    ofFbo fbo;
    ofxMemoryUsage mem;
    bool bPlay, bTemplate;
    void stop();
    void reset();
    void play();
};
