#pragma once

#include "ofMain.h"

class VideoSquare : public ofBaseApp {
	public:

		void setup(ofVec2f pos);
		void update();
		void draw();
		void mouseReleased(int x, int y, int button);
		void setSource(string s);

	private:

		void updatePos();
		void updateSize();
		void drawDragPoints();
		void drawLayer();

		ofVideoPlayer vid;
		ofRectangle vidRect;

		bool isHover = false;
		bool isCornerDragged = false;
		bool isVidRectDragged = false;
		bool isDoubleClicked = false;
		int lastClick = 0;

		ofVec2f prevPos;
};
