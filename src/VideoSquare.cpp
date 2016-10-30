#include "VideoSquare.h"

void VideoSquare::setup(ofVec2f pos) {
	emptyImg.load("ussr_testCard.png");
	moveIcn.load("move_icon.png");
	resizeIcn.load("resize_icon.png");

	vidRect.setFromCenter(pos.x, pos.y, emptyImg.getWidth()*0.25, emptyImg.getHeight()*0.25);
}

void VideoSquare::update() {
	updateSize();
	updatePos();

	switch (mode) {
		case EMPTY:
			break;
		case VIDEO:
			vid.update();
			break;
		case CAM:
			cam.update();
		default:
			break;
	}

	if(!ofGetMousePressed()) {
		isCornerDragged = false;
		isVidRectDragged = false;
	}
}

void VideoSquare::draw() {
	switch (mode) {
		case EMPTY:
			emptyImg.draw(vidRect);
			break;
		case VIDEO:
			vid.draw(vidRect);
			break;
		case CAM:
			cam.draw(vidRect);
		default:
//			emptyImg.draw(vidRect);
			break;
	}

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
		cerr << "Set video-mode with string being filename" << endl;
		mode = EMPTY;
	} else {
		cerr << "Need MODE or string as argument" << endl;
		mode = EMPTY;
	}
}

//--------------------------------------------------------------
void VideoSquare::setupCam() {
	cam.initGrabber(480, 340);
}

void VideoSquare::updatePos() {
	// TODO Move square with offset based on mousePos on drag start
	// TODO Stop if less than zero
	if(!isFullscreen) {
		ofRectangle r(vidRect);
		ofVec2f m(ofGetMouseX(), ofGetMouseY());
		r.scaleFromCenter(0.1);

		if(r.inside(m) && ofGetMousePressed()) isVidRectDragged = true;

		if(isVidRectDragged) vidRect.setFromCenter(m.x, m.y, vidRect.width, vidRect.height);
	}
}

void VideoSquare::updateSize() {
	if(isFullscreen) {
		ofRectangle r(0, 0, ofGetWidth(), ofGetHeight());
		vidRect.scaleTo(r, OF_SCALEMODE_FIT);
		return;
	}

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
			isVidRectDragged ? ofSetHexColor(0x222222) : ofSetHexColor(0x999999);
			ofRectangle dragRect(vidRect);
			ofRectangle resizeRect(vidRect);
			dragRect.scaleFromCenter(0.1);
			moveIcn.draw(dragRect);

			isCornerDragged ? ofSetHexColor(0x222222) : ofSetHexColor(0x999999);
			resizeRect.scale(0.05);
			ofVec2f s(resizeRect.getWidth(), resizeRect.getHeight());
			resizeRect.setPosition(vidRect.getBottomRight()-s);
			resizeIcn.draw(resizeRect);
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
