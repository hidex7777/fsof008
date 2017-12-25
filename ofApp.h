#pragma once

#include "ofMain.h"
#include "Particle.h"

class ofApp : public ofBaseApp{

public:
	void setup();
	void update();
	void draw();
	void setnewParticle();
	ofColor setColor();

	void keyPressed(int key);

private:
	vector<Particle*> particles;
	ofImage img;
	ofEasyCam cam;
};
