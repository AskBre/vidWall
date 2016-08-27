#include "VideoSquare.h"

void VideoSquare::setup() {
	vid.load("ussr_testCard.mov");
	vid.play();
}

void VideoSquare::update() {
	updatePos();
	updateSize();

	vid.update();
}

void VideoSquare::draw() {
	vid.draw(pos);

	if(isHover(getVidRect())) drawLayer();
}

void VideoSquare::setSource(string source) {
	vid.load(source);
}

//--------------------------------------------------------------
void VideoSquare::updatePos() {
	// TODO Move square with offset based on mousePos on drag start
	if(isDragged(getVidRect())) {
		ofVec2f mouse(ofGetMouseX(), ofGetMouseY());
		ofVec2f newPos(mouse.x - (vid.getWidth()*0.5),
			mouse.y - (vid.getHeight()*0.5));

		pos = newPos;
	}
}

void VideoSquare::updateSize() {
	if(!isHover(getVidRect())) return;
	updateCornerRects();
}

void VideoSquare::updateCornerRects() {
	ofRectangle r = getVidRect();
	ofVec2f s(r.width * cornerSize, r.height * cornerSize);

	TLCorner.set(r.getTopLeft(), s.x, s.y);
	TRCorner.set(r.getTopRight(), -s.x, s.y);
	BLCorner.set(r.getBottomLeft(), s.x, -s.y);
	BRCorner.set(r.getBottomRight(), -s.x, -s.y);
}

void VideoSquare::drawLayer() {
	ofPushStyle();
		ofSetHexColor(0xFF0000);
		ofNoFill();

		ofDrawRectangle(getVidRect());
		ofDrawRectangle(TLCorner);
		ofDrawRectangle(TRCorner);
		ofDrawRectangle(BLCorner);
		ofDrawRectangle(BRCorner);
	ofPopStyle();
}

//--------------------------------------------------------------
bool VideoSquare::isDragged(ofRectangle r) {
	//TODO Do the maths, not the obj.
	if(!ofGetMousePressed()) return false;

	return r.inside(ofVec2f(ofGetMouseX(), ofGetMouseY()));
}

bool VideoSquare::isHover(ofRectangle r) {
	return r.inside(ofVec2f(ofGetMouseX(), ofGetMouseY()));
}

ofRectangle VideoSquare::getVidRect() {
	ofRectangle r(pos, vid.getWidth(), vid.getHeight());
	return r;
}
