#include "Particle.h"

Particle::Particle(float r, ofColor color) {
	this->myradius = r;
	this->mycolor = color;
	//todo
	this->myalp = ofRandom(127, 255);
	this->plusminus = ofRandom(100) < 50 ? 1 : -1;
	this->myweight = ofRandom(2, 6);
	this->phi = ofRandom(TWO_PI);
	this->unitz = ofRandom(-1.0, 1.0);
	float x =  this->myradius * sqrt(1 - this->unitz * this->unitz) * cos(this->phi);
	float y =  this->myradius * sqrt(1 - this->unitz * this->unitz) * sin(this->phi);
	float z =  this->myradius * this->unitz;
	this->location = ofVec3f(x, y, z);
	//todo
	this->mynoise = ofNoise(ofRandom(255));
}
void Particle::update() {
	this->phi += ofDegToRad(this->mynoise * 0.5) * this->plusminus;
	if (this->phi > TWO_PI) {
		this->phi = 0;
	}
	else if (this->phi < 0) {
		this->phi = TWO_PI;
	}
	this->unitz += (this->mynoise * 0.005) * this->plusminus;
	if (unitz > 1.0) {
		unitz = 1.0;
		this->plusminus *= -1;
	}
	else if (unitz < -1.0) {
		unitz = -1.0;
		this->plusminus *= -1;
	}
	float x = this->myradius * sqrt(1 - this->unitz * this->unitz) * cos(this->phi);
	float y = this->myradius * sqrt(1 - this->unitz * this->unitz) * sin(this->phi);
	float z = this->myradius * this->unitz;
	this->location = ofVec3f(x, y, z);
	this->myalp -= 0.1;
}
void Particle::draw() {
	ofSetColor(this->mycolor, this->myalp);
	ofPushMatrix();
	ofTranslate(this->location);
	ofDrawSphere(this->myweight);
	ofPopMatrix();
}
ofVec3f Particle::getLocation() {
	return this->location;
}
bool Particle::isDead() {
	return this->myalp < 0;
}
ofColor Particle::getColor() {
	return this->mycolor;
}