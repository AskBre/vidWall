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
		void drawDragPoints();
		void drawLayer();

		ofVideoPlayer vid;
		ofRectangle vidRect;

		bool isCornerDragged = false;
		bool isVidRectDragged = false;
		ofVec2f prevPos;
};
