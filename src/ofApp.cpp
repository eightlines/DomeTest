#include "ofApp.h"

// TEST FILE AVAILABLE AT http://eightlines.com/media/BRITA_A_FINAL_1.mp4

const int NUM_VIDEOS = 4;
//const string PATH_ROOT = "/Volumes/WXM/Brita/";
const string PATH_ROOT = "/Users/administrator/Desktop/BRITA/";
const string VIDEO_PATH_START = "BRITA_";
const string VIDEO_PATH_END = "_FINAL_1.mp4";
const string TEMPLATE_PATH_START = "SURFACE TRACE_";
const string TEMPLATE_PATH_END = ".jpg";
const ofRectangle VIDEO_SIZE = ofRectangle(0, 0, 1920, 1080);
const int ADMIN = 1;

void ofApp::setup() {
    ofSetVerticalSync(true);
    ofSetWindowTitle("DOME");
    mem.setup();
    
    for (int i = 0; i < NUM_VIDEOS; i++) {
        string dest = "A"; //(i == 0) ? "A" : (i == 1) ? "B" : (i == 2) ? "C" : "D";

        ofVideoPlayer vid;
        vid.load(PATH_ROOT + VIDEO_PATH_START + dest + VIDEO_PATH_END);
        vid.setLoopState(OF_LOOP_NONE);
        videos.push_back(vid);

//        ofImage img;
//        img.load(PATH_ROOT + TEMPLATE_PATH_START + dest + TEMPLATE_PATH_END);
//        templates.push_back(img);
    }

//    cout << "TEMPLATES: " << templates.size() << ", VIDEOS: " << videos.size() << endl;

    fbo.allocate(VIDEO_SIZE.width * (NUM_VIDEOS + ADMIN), VIDEO_SIZE.height);
    
    bPlay = false;
//    bTemplate = false;
}

void ofApp::update() {
    mem.update();
    
    if (bPlay) {
        videos[0].update();
        videos[1].update();
        videos[2].update();
        videos[3].update();
        
        if (!videos[0].isPlaying())
            reset();
//        for (int i = 0; i < NUM_VIDEOS; i++)
//            videos[i].update();
//        
//        if (videos[0].getIsMovieDone()) {
//            reset();
//        }
    }

    fbo.begin();
    ofClear(255, 255, 255, 0);
    for (int i = 0; i < NUM_VIDEOS + ADMIN; i++) {
        if (i > 0) {
            ofPushMatrix();
            ofTranslate(VIDEO_SIZE.width * i, 0);
            if (bPlay)
                videos[(i - ADMIN)].draw(0, 0);
//            else if (bTemplate)
//                templates[(i - ADMIN)].draw(0, 0);
            ofPopMatrix();
        }
    }
    fbo.end();
}

void ofApp::draw() {
    ofBackground(0);
    fbo.draw(0, 0, 3200, 360); // SCALE TO WINDOW SIZE
    
    stringstream ss;
    ss << "FPS:             " << ofToString(ofGetFrameRate()) << "\n";
    ss << "A POSITION:      " << ofToString(videos[0].getPosition()) << " (" << videos[0].isPlaying() << ")\n";
    ss << "B POSITION:      " << ofToString(videos[1].getPosition()) << " (" << videos[1].isPlaying() << ")\n";
    ss << "C POSITION:      " << ofToString(videos[2].getPosition()) << " (" << videos[2].isPlaying() << ")\n";
    ss << "D POSITION:      " << ofToString(videos[3].getPosition()) << " (" << videos[3].isPlaying() << ")\n";
    ss << "PLAYING     ( ): " << ((bPlay) ? "TRUE" : "FALSE") << "\n";
//    ss << "TEMPLATE    (t): " << ((bTemplate) ? "TRUE" : "FALSE") << "\n";
    ss << "FULLSCREEN  (f)  " << "\n";
    ss << "RESET VIDEO (r)  " << "\n";
    ss << "PROCESS MEMORY:  " << ofToString(mem.getProcessMemory()) << "\n";
    ss << "USED MEMORY:     " << ofToString(mem.getUsedMemory()) << "\n";
    ss << "TOTAL MEMORY:    " << ofToString(mem.getTotalMemory()) << "\n";
    ofDrawBitmapString(ss.str(), 10, 10);
}

void ofApp::keyReleased(int key) {
    if (key == ' ') {
        bPlay = !bPlay;
        (bPlay) ? play() : stop();
//    } else if (key == 't') {
//        bTemplate = !bTemplate;
    } else if (key == 'f') {
        ofToggleFullscreen();
    } else if (key == 'r') {
        reset();
    }
}

void ofApp::play() {
    cout << "PLAY" << endl;
    videos[0].play();
    videos[1].play();
    videos[2].play();
    videos[3].play();
//    for (int i = 0; i < NUM_VIDEOS; i++)
//        videos[i].play();
}

void ofApp::reset() {
    cout << "RESET" << endl;
    videos[0].stop();
    videos[1].stop();
    videos[2].stop();
    videos[3].stop();
    
    videos[0].play();
    videos[1].play();
    videos[2].play();
    videos[3].play();
//    for (int i = 0; i < NUM_VIDEOS; i++) {
//        videos[i].stop();
//        videos[i].play();
//    }
}

void ofApp::stop() {
    cout << "STOP" << endl;
    videos[0].setPaused(true);
    videos[1].setPaused(true);
    videos[2].setPaused(true);
    videos[3].setPaused(true);
//    for (int i = 0; i < NUM_VIDEOS; i++)
//        videos[i].setPaused(true);
}
