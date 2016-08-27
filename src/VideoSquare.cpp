#include "VideoSquare.h"
//TODO Add graphics to middle and corner dragging

void VideoSquare::setup() {
	vid.load("ussr_testCard.mov");
	vidRect.setFromCenter(ofGetWidth()*0.5, ofGetHeight()*0.5,
				vid.getWidth(), vid.getHeight());
	vid.play();
}

void VideoSquare::update() {
	updateSize();
	updatePos();

	vid.update();

	if(!ofGetMousePressed()) {
		isCornerDragged = false;
		isVidRectDragged = false;
	}
}

void VideoSquare::draw() {
	vid.draw(vidRect);
}

void VideoSquare::setSource(string source) {
	vid.load(source);
}

//--------------------------------------------------------------
void VideoSquare::updatePos() {
	// TODO Move square with offset based on mousePos on drag start
	// TODO Stop if less than zero
	ofRectangle r(vidRect);
	ofVec2f m(ofGetMouseX(), ofGetMouseY());
	r.scaleFromCenter(0.1);

	if(r.inside(m) && ofGetMousePressed()) isVidRectDragged = true;

	if(isVidRectDragged) vidRect.setFromCenter(m.x, m.y, vidRect.width, vidRect.height);
}

void VideoSquare::updateSize() {
	ofVec2f c(vidRect.getBottomRight());
	ofVec2f m(ofGetMouseX(), ofGetMouseY());
	int dist = ofDistSquared(c.x, c.y, m.x, m.y);

	if(dist<(vidRect.getWidth()*0.1) && ofGetMousePressed()) isCornerDragged = true;

	if(isCornerDragged) {
		ofPoint p2(m.x, m.y);
		ofRectangle r(prevPos, p2);
		vidRect.scaleTo(r, OF_SCALEMODE_FILL);
		vidRect.alignTo(prevPos, OF_ALIGN_HORZ_LEFT, OF_ALIGN_VERT_TOP);
	} else {
		prevPos = vidRect.getPosition();
	}
}
