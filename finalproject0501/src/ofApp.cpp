#include "ofApp.h"

//--------------------------------------------------------------
ofApp::~ofApp() {
    for (int i = this->particles.size() - 1; i > -1; i--) {
        delete this->particles[i];
        this->particles.erase(this->particles.begin() + i);
    }
}

//--------------------------------------------------------------
void ofApp::setup() {
    ofSetFrameRate(30);
    //ofBackground(167,167,235);
    ofBackground(0,0,0);
    ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
    
    //set the guitar sounds
    string sound_path_list[] = {"1.mp3", "2.mp3", "3.mp3", "4.mp3", "5.mp3", "6.mp3"};
    for (int i = 0; i < 6; i++) {
        ofSoundPlayer sound;
        sound.load(sound_path_list[i]);
        sound.setMultiPlay(true);
        this->sounds.push_back(sound);
    }
    
}

//--------------------------------------------------------------
void ofApp::update(){
    Leap::Controller controller;
    Leap::Frame frame = controller.frame();
    for (Leap::Hand hand : frame.hands()) {
        if (hand.grabStrength() < 1) {
            //define the velocity of hand palm
            ofVec2f velocity = ofVec2f(hand.palmVelocity().x, hand.palmVelocity().y);
            velocity.limit(10);
            
            //generate new particles. particles location is based on hand palm's location, moving velocity is based on hand palm's velocity
            this->particles.push_back(new Particle(ofVec2f(hand.palmPosition().x, hand.palmPosition().y - ofGetHeight()/4 ), velocity));
        }
    }
    
    for (int i = this->particles.size() - 1; i > -1; i--) {
        //update the particle's look
        this->particles[i]->update();
        
        //erase the patterns
        if (this->particles[i]->isDead()) {
            delete this->particles[i];
            this->particles.erase(this->particles.begin() + i);
        }
    }
    
    for (Leap::Hand hand : frame.hands()) {
        for (Leap::Finger finger : hand.fingers()) {
            ofVec2f vel = ofVec2f(finger.tipVelocity().x, -finger.tipVelocity().y);
            if (vel.length() > 50) {
                //if finger tip is moving actively, play the guitar sound
                this->sounds[ofGetFrameNum() % 6].play();
            }
        }
    }
    ofSoundUpdate();
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    this->cam.begin();
    
    for (Particle* p : this->particles) {
        p->draw();
    }
    
    this->cam.end();
}
