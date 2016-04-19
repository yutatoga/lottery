#pragma once

#include "ofMain.h"
#include "LotteryImage.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

    // ルーレット画像
    vector<LotteryImage> lotteryImageVector;
    bool pause;
    int giftsNumber;
    int currentImageIndex;
    ofSoundPlayer player;
    // ルーレット画像を指定サイズで指定する場合
    //		ofVec2f currentImageSize;
    
    // スタートページ
    bool startPage;
    ofImage startPageBackImage;
    
    // スタートボタンが丸の場合
    //		ofPoint startButtonCenterPoint;
    //		float startButtonRadius;
    
    // スタートボタンが四角の場合
    ofImage startButtonImage;
    ofRectangle startButtonRectangle;
    
    // スタートページに戻るボタン
    ofRectangle backToStartPageButton;
    ofVec2f backToStartPageButtonSize;
};
