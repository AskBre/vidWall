#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(0);

	//TODO BUG If squares are ontop of each other, they move together
	int nVidSqrs(4);
	for(int i=0; i<nVidSqrs; i++) {
		float offset((float)(i+1)/(float)(nVidSqrs+1));
		ofVec2f p(ofGetWidth()*offset, ofGetHeight()*0.5);
		VideoSquare v;
		v.setup(p);
		vidSqrs.push_back(v);
	}

	vidSqrs.back().setSource(CAM);
}

//--------------------------------------------------------------
void ofApp::update(){
	for(auto &v : vidSqrs) v.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	for(auto &v : vidSqrs) v.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	for(auto &v : vidSqrs) v.mouseReleased(x, y, button);
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
