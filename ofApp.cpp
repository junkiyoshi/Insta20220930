#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(0);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->face.clear();

	int span = 20;
	float threshold = 0.55;
	float frame_param = ofGetFrameNum() * 0.05;
	float coordinate_param = 0.0075;

	for (int len = 300; len > 160; len -= 10) {

		ofColor color = ofColor(ofMap(len, 150, 300, 255, 0));
		int z = len + span * 0.5;

		float angle;
		glm::highp_mat4 rotation;
		for (int i = 0; i <= 6; i++) {

			for (int x = -len; x <= len; x += span) {

				for (int y = -len; y <= len; y += span) {

					if (i <= 4) {

						angle = PI * 0.5 * i;
						rotation = glm::rotate(glm::mat4(), angle, glm::vec3(0, 1, 0));
					}

					if (i == 5) {

						angle = PI * 0.5;
						rotation = glm::rotate(glm::mat4(), angle, glm::vec3(1, 0, 0));
					}

					if (i == 6) {

						angle = PI * 0.5 * 3;
						rotation = glm::rotate(glm::mat4(), angle, glm::vec3(1, 0, 0));
					}


					glm::vec3 noise_location = glm::vec4(x, y, z, 0) * rotation;
					auto noise_value = ofNoise(glm::vec4(noise_location * coordinate_param, frame_param));
					if (noise_value < threshold) { continue; }

					auto index = this->face.getNumVertices();
					vector<glm::vec3> vertices;

					vertices.push_back(glm::vec4(x - span * 0.5, y - span * 0.5, z, 0) * rotation);
					vertices.push_back(glm::vec4(x + span * 0.5, y - span * 0.5, z, 0) * rotation);
					vertices.push_back(glm::vec4(x + span * 0.5, y + span * 0.5, z, 0) * rotation);
					vertices.push_back(glm::vec4(x - span * 0.5, y + span * 0.5, z, 0) * rotation);

					this->face.addVertices(vertices);

					this->face.addColor(color);
					this->face.addColor(color);
					this->face.addColor(color);
					this->face.addColor(color);

					this->face.addIndex(index + 0); this->face.addIndex(index + 1); this->face.addIndex(index + 2);
					this->face.addIndex(index + 0); this->face.addIndex(index + 2); this->face.addIndex(index + 3);
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum());
	ofRotateX(ofGetFrameNum() * 1.5);

	this->face.draw();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}