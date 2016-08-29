#include "VideoSquare.h"
//TODO Add symbols to middle and corner dragging

void VideoSquare::setup(ofVec2f pos) {
	// TODO Change from movie to texture as default
	vid.load("ussr_testCard.mov");
	vidRect.setFromCenter(pos.x, pos.y, vid.getWidth()*0.25, vid.getHeight()*0.25);
	vid.play();
}

void VideoSquare::update() {
	updateSize();
	updatePos();

	(mode == VIDEO) ? vid.update() : cam.update();

	if(!ofGetMousePressed()) {
		isCornerDragged = false;
		isVidRectDragged = false;
	}

	if(isDoubleClicked) {
		cout << "Click!" << endl;
	}
}

void VideoSquare::draw() {
	(mode == VIDEO) ? vid.draw(vidRect) : cam.draw(vidRect);
	drawLayer();
}

void VideoSquare::setSource(string source) {
	mode = VIDEO;
	vid.load(source);
	vid.play();
}

void VideoSquare::setSource(MODE m) {
	mode = m;

	if(mode == CAM) {
		vid.stop();
		setupCam();
	} else if (mode == VIDEO){
		vid.play();
	} else {
		cerr << "Need MODE or string as argument" << endl;
	}
}

//--------------------------------------------------------------
void VideoSquare::setupCam() {
	cam.initGrabber(480, 340);
}

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

	if(dist<(vidRect.getWidth()) && ofGetMousePressed()) isCornerDragged = true;

	if(isCornerDragged) {
		ofPoint p2(m.x, m.y);
		ofRectangle r(prevPos, p2);
		vidRect.scaleTo(r, OF_SCALEMODE_FILL);
		vidRect.alignTo(prevPos, OF_ALIGN_HORZ_LEFT, OF_ALIGN_VERT_TOP);
	} else {
		prevPos = vidRect.getPosition();
	}
}

void VideoSquare::drawLayer() {
	ofVec2f m(ofGetMouseX(), ofGetMouseY());
	ofRectangle r(vidRect);
	r.scale(1.1);
	if(r.inside(m)) {
		ofPushStyle();
			ofNoFill();
			ofSetLineWidth(2);

			isVidRectDragged ? ofSetHexColor(0xFF0000) : ofSetHexColor(0xFFFFFF);
			ofRectangle dragRect(vidRect);
			ofRectangle resizeRect(vidRect);
			dragRect.scaleFromCenter(0.1);
			ofDrawRectangle(dragRect);

			isCornerDragged ? ofSetHexColor(0xFF0000) : ofSetHexColor(0xFFFFFF);
			resizeRect.scale(0.05);
			ofVec2f s(resizeRect.getWidth(), resizeRect.getHeight());
			resizeRect.setPosition(vidRect.getBottomRight()-s);
			ofDrawRectangle(resizeRect);
		ofPopStyle();
	}
}

void VideoSquare::mouseReleased(int x, int y, int button) {
	if(ofGetElapsedTimeMillis() - lastClick < 500) {
		ofFileDialogResult file = ofSystemLoadDialog();

		if(file.bSuccess) {
			cout << "Loaded file " << file.fileName << endl;
			setSource(file.getPath());
		} else {
			cerr << "Can't load file " << file.fileName << endl;
		}
	}

	if(vidRect.inside(ofVec2f(x, y))) {
		lastClick = ofGetElapsedTimeMillis();
	}
}
