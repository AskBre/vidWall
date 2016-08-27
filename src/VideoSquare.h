#pragma once

#include "ofMain.h"

class VideoSquare : public ofBaseApp {
	public:
		VideoSquare() {setup();};

		void setup();
		void update();
		void draw();
		void setSource(string s);

	private:

		void updatePos();
		void updateSize();
		void updateCornerRects();
		void drawLayer();

		bool isDragged(ofRectangle r);
		bool isHover(ofRectangle r);

		ofRectangle getVidRect();

		float cornerSize = 0.1;

		ofVideoPlayer vid;
		ofRectangle TLCorner;
		ofRectangle TRCorner;
		ofRectangle BLCorner;
		ofRectangle BRCorner;

		ofVec2f pos{(float)(ofGetWidth()*0.5), (float)(ofGetHeight()*0.5)};
};
