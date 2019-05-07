//
//  Particle.cpp
//  finalproject0501
//
//  Created by Yuhan Liu on 2019/5/1.
//

#include "Particle.h"

Particle::Particle() : Particle(ofVec2f(0, 0), ofVec2f(0, 0)) { }

Particle::Particle(ofVec2f location, ofVec2f velocity)
{
    this->location = location;
    this->velocity = velocity;
    this->alpha = 255;
    this->body_size = velocity.length() * 12;  //particle's size based on hand's velocity
    this->body_color.set(ofRandom(0,255), ofRandom(0,255), ofRandom(0,255));  //random color of particle
}

Particle::~Particle() { }

void Particle::update()
{
    this->location += this->velocity;
    this->alpha -= 2;  //particle will fade away
}

void Particle::draw()
{
    //draw circles
    ofFill();
    ofSetColor(this->body_color, this->alpha);
    ofDrawEllipse(this->location, this->body_size, this->body_size);
    
    //draw vertices
    ofPushMatrix();
    ofTranslate(this->location);
    
    int base_radius = 200;
    for (int radius = base_radius; radius > 0; radius -= 10) {
        
        //draw vertices based on noise
        vector<glm::vec2> vertices;
        for (int deg = 0; deg < 360; deg += 10) {
            glm::vec2 noise_location = glm::vec2(cos(deg * DEG_TO_RAD), sin(deg * DEG_TO_RAD));
            float noise_value = ofMap(ofNoise(noise_location.x, noise_location.y, radius * 0.005 + ofGetFrameNum() * 0.005), 0, 1, 0.5, 1);
            float noise_radius = radius * noise_value;
            vertices.push_back(glm::vec2(noise_radius * cos(deg * DEG_TO_RAD), noise_radius * sin(deg * DEG_TO_RAD)));
        }

        ofBeginShape();
        ofNoFill();
        ofSetColor(this->body_color, this->alpha);
        ofVertices(vertices);
        ofEndShape(true);
    }
    ofPopMatrix();
}

bool Particle::isDead()
{
    return this->alpha < 0;
}
