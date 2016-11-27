#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofBackground(0);
	ofSetDataPathRoot("../Resources/data");
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

	load();
}

void ofApp::update(){
	if(vidSqrs.size() == 1) {
		vidSqrs.at(0).setFullscreen(true);
	} else {
		vidSqrs.at(0).setFullscreen(false);
	}

	for(auto &v : vidSqrs) v.update();
}

void ofApp::draw(){
	for(auto &v : vidSqrs) v.draw();
}
//--------------------------------------------------------------
void ofApp::addScreen() {
	ofVec2f p(ofRandom(0, ofGetWidth()),
			ofRandom(0, ofGetHeight()));
	VideoSquare v;
	v.setup(p);
	cout << "Adding screen" << endl;
	vidSqrs.push_back(v);
}

void ofApp::removeScreen() {
	if(vidSqrs.size()>1) {
		cout << "Removing screen" << endl;
		vidSqrs.pop_back();
	}
}

//--------------------------------------------------------------
void ofApp::save() {
	ofxXmlSettings settings;
	settings.addTag("vidSqrs");
	settings.pushTag("vidSqrs");

	for(unsigned i=0; i<vidSqrs.size(); i++) {
		settings.addTag("vidSqr");
		settings.pushTag("vidSqr", i);

		settings.addValue("source", vidSqrs.at(i).getSource());

		settings.addTag("pos");
		settings.pushTag("pos");
		settings.addValue("x", vidSqrs.at(i).getPos().x);
		settings.addValue("y", vidSqrs.at(i).getPos().y);
		settings.popTag();

		settings.addTag("size");
		settings.pushTag("size");
		settings.addValue("width", vidSqrs.at(i).getWidth());
		settings.addValue("height", vidSqrs.at(i).getHeight());
		settings.popTag();

		settings.popTag();
	}
	settings.popTag();
	settings.saveFile("settings.xml");
	settings.saveFile("../../../../vidWall_settings.xml");
	cout << "Settings are saved" << endl;
}

void ofApp::load() {
	ofxXmlSettings settings;
	if(!settings.loadFile("settings.xml")) {
		cerr << "No settings-file found" << endl;
		return;
	}
	settings.pushTag("vidSqrs");
	vidSqrs.resize(settings.getNumTags("vidSqr"));
	cout << "Found " << vidSqrs.size() << " numtags" << endl;

	for(unsigned i=0; i<vidSqrs.size(); i++) {
		settings.pushTag("vidSqr", i);

		string source = settings.getValue("source", "EMPTY");
		vidSqrs.at(i).setSource(source);

		settings.pushTag("pos");
			ofPoint p;
			p.x = settings.getValue("x", 0);
			p.y = settings.getValue("y", 0);
			vidSqrs.at(i).setPos(p);
		settings.popTag();

		settings.pushTag("size");
			vidSqrs.at(i).setWidth(settings.getValue("width", 0));
			vidSqrs.at(i).setHeight(settings.getValue("height", 0));
		settings.popTag();

		settings.popTag();
	}
	settings.popTag();
	cout << "Settings are loaded" << endl;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	switch(key) {
		case OF_KEY_RIGHT:
			addScreen();
			break;
		case OF_KEY_LEFT:
			removeScreen();
			break;
		case 's':
			save();
			break;
		case 'l':
			load();
			break;
		default:
			break;
	}
}

void ofApp::keyReleased(int key){

}

void ofApp::mouseMoved(int x, int y){

}

void ofApp::mouseDragged(int x, int y, int button){

}

void ofApp::mousePressed(int x, int y, int button){

}

void ofApp::mouseReleased(int x, int y, int button){
	for(auto &v : vidSqrs) v.mouseReleased(x, y, button);
}

void ofApp::mouseEntered(int x, int y){

}

void ofApp::mouseExited(int x, int y){

}

void ofApp::windowResized(int w, int h){

}

void ofApp::gotMessage(ofMessage msg){

}

void ofApp::dragEvent(ofDragInfo dragInfo){

}
