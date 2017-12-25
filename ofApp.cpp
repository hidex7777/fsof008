#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(60);
	ofSetBackgroundColor(255);
	ofEnableAlphaBlending();
	ofEnableDepthTest();
	for (int i = 0; i < 1000; i++) {
		this->particles.push_back(new Particle(ofGetWidth()*0.4, this->setColor()));
	}
}
void ofApp::setnewParticle() {
	this->particles.push_back(new Particle(ofGetWidth()*0.4, this->setColor()));
}
//--------------------------------------------------------------
void ofApp::update(){
	for (int i = this->particles.size() - 1; i > -1; i--) {
		this->particles[i]->update();
		if (this->particles[i]->isDead()) {
			delete this->particles[i];
			this->particles.erase(this->particles.begin() + i);
			setnewParticle();
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.1);
	for (int i = 0; i < this->particles.size(); i++) {
		this->particles[i]->draw();
		for (int j = i + 1; j < this->particles.size(); j++) {
			float dist = this->particles[i]->getLocation().distance(this->particles[j]->getLocation());
			if (dist < 100) {
				float ma = ofMap(dist, 0, 99, 200, 20);
				ofSetColor(this->particles[i]->getColor(), ma);
				ofSetLineWidth(1);
				ofDrawLine(this->particles[i]->getLocation(), this->particles[j]->getLocation());
			}
		}
	}
	this->cam.end();
	//std::cout << this->particles.size() << std::endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'x') {
		string now = ofGetTimestampString("%Y%m%d%H%M%S");
		this->img.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		this->img.saveImage("of" + now + ".jpg");
	}
}

ofColor ofApp::setColor() {
	ofColor myc[] = {
		ofColor(166, 29, 57),
		ofColor(171, 61, 29),
		ofColor(177, 108, 0),
		ofColor(179, 147, 0),
		ofColor(116, 132, 0),
		ofColor(0, 114, 67),
		ofColor(0, 102, 100),
		ofColor(0, 84, 118),
		ofColor(0, 66, 128),
		ofColor(62, 51, 123),
		ofColor(97, 36, 105),
		ofColor(134, 29, 85)
	};
	return myc[int(ofRandom(12))];
}
