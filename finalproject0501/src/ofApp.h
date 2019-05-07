#pragma once
#include "ofMain.h"
#include "Particle.h"
#include "ofxLeapMotion2.h"


// Leap Motion SDK
#include "Leap.h"
#pragma comment(lib, "Leap.lib")

class ofApp : public ofBaseApp{
    
public:
    ~ofApp();
    
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key) { }
    void keyReleased(int key) { }
    void mouseMoved(int x, int y) { }
    void mouseDragged(int x, int y, int button) { }
    void mousePressed(int x, int y, int button) { }
    void mouseReleased(int x, int y, int button) { }
    void mouseEntered(int x, int y) { }
    void mouseExited(int x, int y) { }
    void windowResized(int w, int h) {}
    void dragEvent(ofDragInfo dragInfo) { }
    void gotMessage(ofMessage msg) {}
    
    vector<ofSoundPlayer> sounds;

    
    ofEasyCam cam;
    vector<Particle*> particles;
    
    Leap::Controller leap;
    
};
