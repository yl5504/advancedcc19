//
//  Particle.h
//  finalproject0501
//
//  Created by Yuhan Liu on 2019/5/1.
//

#pragma once
#include "ofMain.h"

class Particle {
public:
    Particle();
    Particle(ofVec2f location, ofVec2f velocity);
    ~Particle();
    
    void update();
    void draw();
    
    bool isDead();
    
private:
    ofVec2f location;
    ofVec2f velocity;
    
    float    body_size;
    ofColor body_color;
    int        alpha;
};
