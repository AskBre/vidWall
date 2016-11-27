#pragma once

#include "ofMain.h"

enum MODE{
	EMPTY,
	CAM,
	VIDEO
};

class VideoSquare : public ofBaseApp {
	public:
		void setup(ofVec2f pos);
		void update();
		void draw();
		void mouseReleased(int x, int y, int button);

		void setSource(string s);
		void setSource(MODE m);
		string getSource();

		void setFullscreen(bool _isFullscreen) {isFullscreen = _isFullscreen;};

		ofPoint getPos() {return vidRect.getPosition();};
		void setPos(ofPoint p) {vidRect.setPosition(p);};

		float getWidth() {return vidRect.getWidth();};
		void setWidth(float w) {vidRect.setWidth(w);};
		float getHeight() {return vidRect.getHeight();};
		void setHeight(float h) {vidRect.setHeight(h);};


	private:
		void setupCam();

		void updatePos();
		void updateSize();
		void drawDragPoints();
		void drawLayer();

		ofVideoPlayer vid;
		ofImage emptyImg;
		ofVideoGrabber cam;
		ofRectangle vidRect;
		ofImage moveIcn;
		ofImage resizeIcn;

		bool isFullscreen = false;

		bool isHover = false;
		bool isCornerDragged = false;
		bool isVidRectDragged = false;
		bool isDoubleClicked = false;

		int lastClick = 0;

		ofVec2f prevPos;

		MODE mode = EMPTY;
};
