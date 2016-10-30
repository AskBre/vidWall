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
		void setFullscreen(bool _isFullscreen) {isFullscreen = _isFullscreen;};

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
