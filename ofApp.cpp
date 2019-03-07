#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (int i = 0; i < 10; i++) {

		float noise_seed_x = ofRandom(1000);
		float noise_seed_y = ofRandom(1000);
		float random_deg = ofRandom(360);
		glm::vec3 prev_location;
		for (int radius = 0; radius < 300; radius += 5) {

			auto point = glm::vec3(radius * cos(random_deg * DEG_TO_RAD), radius * sin(random_deg * DEG_TO_RAD), 0);
			auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_x + (radius + ofGetFrameNum()) * 0.003), 0, 1, -PI * 2, PI * 2), glm::vec3(1, 0, 0));
			auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_y + (radius + ofGetFrameNum()) * 0.003), 0, 1, -PI * 2, PI * 2), glm::vec3(0, 1, 0));

			glm::vec3 location = glm::vec4(point, 0) * rotation_x * rotation_y;
			ofDrawSphere(location, 3);

			if (prev_location != glm::vec3()) {

				ofDrawLine(prev_location, location);
			}

			prev_location = location;
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}