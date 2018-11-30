#include "ofApp.h"

#define START_BUTTON_POSITION 0.75
#define GIFT_NUMBER 250

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(ofColor::white);
    ofEnableAlphaBlending();
    ofSetFrameRate(24);
    for (int i =0; i < GIFT_NUMBER; i++) {
        LotteryImage lotteryImage;
        lotteryImage.load("presents/"+ofToString(i)+".jpg");
        //				// ジャンル分け(1等, 2等, 3等など)
        //				// 0 - kakaku.com
        //				// 1 - payment
        //				// 2 - dg
        //				if (i>=0 && i<=3) {
        //						lotteryImage.setKindId(0);
        //				}
        lotteryImageVector.push_back(lotteryImage);
    }
    pause = true;
    player.load("sounds/drumrollloop.wav");
    player.setLoop(true);
    
    // スタートページ
    startPage = true;
    startPageBackImage.load("startPage/background.png");
    
    // スタートボタンが丸の場合
    //		startButtonCenterPoint.set(ofGetWidth()/2., ofGetHeight()*0.8);
    //		startButtonRadius = 30;
    
    // スタートボタンが四角の場合
    startButtonImage.load("startPage/start.png");
    startButtonRectangle.setFromCenter(ofGetWidth()/2.0, ofGetHeight() * START_BUTTON_POSITION, ofGetWidth()/2.0, startButtonImage.getHeight() * ofGetWidth()/2.0 / startButtonImage.getWidth());
    // スタートページに戻るボタン
    backToStartPageButtonSize.set(28, 28);
    backToStartPageButton.setFromCenter(backToStartPageButtonSize.x/2., backToStartPageButtonSize.y/2., backToStartPageButtonSize.x, backToStartPageButtonSize.y);
}

//--------------------------------------------------------------
void ofApp::update(){
    if(!pause){
        currentImageIndex = rand()%(int)lotteryImageVector.size();
    }
    ofLogNotice(ofToString(currentImageIndex));
}

//--------------------------------------------------------------
void ofApp::draw(){
    //		ofLogNotice("draw:"+ofToString(currentPhotoId));
    
    if (startPage) {
        // 背景画像を描画
        startPageBackImage.draw(0, 0, ofGetWidth(), ofGetHeight());
        
        ofPushStyle();
        //				ofSetColor(ofColor::red);
        // スタートボタンが丸の場合
        //				ofCircle(startButtonCenterPoint, 40);
        
        // スタートボタンが四角の場合
        //				ofRect(startButtonRectangle.getCenter(), 100, 100);
        if (lotteryImageVector.size()>0) {
            startButtonImage.draw(startButtonRectangle.getPosition().x, startButtonRectangle.getPosition().y, startButtonRectangle.getWidth(), startButtonRectangle.getHeight());
        }
        ofPopStyle();
    }else{
        // ルーレット画面の画像
        ofPushMatrix();
        ofPushStyle();
        ofTranslate(ofGetWidth()/2., ofGetHeight()/2.);
        ofSetRectMode(OF_RECTMODE_CENTER);
        ofLogNotice("currentImageIndex:"+ofToString(currentImageIndex));
        lotteryImageVector[currentImageIndex].draw(0, 0, lotteryImageVector[currentImageIndex].getWidth(), lotteryImageVector[currentImageIndex].getHeight());
        ofPopStyle();
        ofPopMatrix();
        
        if (pause) {
            // スタートページに戻るボタンを表示
            ofPushStyle();
            // ボタンの四角
            ofSetColor(10, 79, 214);
            ofDrawRectangle(backToStartPageButton);
            // ボタン内のバッテン
            ofSetColor(ofColor::white);
            ofDrawLine(backToStartPageButton.getPosition().x, backToStartPageButton.getPosition().y, backToStartPageButton.getPosition().x+backToStartPageButton.getWidth(), backToStartPageButton.getPosition().y+backToStartPageButton.getHeight());
            ofDrawLine(backToStartPageButton.getPosition().x, backToStartPageButton.getPosition().y+backToStartPageButton.getHeight(), backToStartPageButton.getPosition().x+backToStartPageButton.getWidth(), backToStartPageButton.getPosition().y);
            ofPopStyle();
        }
    }
    ofPushStyle();
    ofSetColor(255, 127, 0, 127);
    ofDrawCircle(mouseX, mouseY, 30);
    ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    switch (key) {
        case 'f':
            ofToggleFullscreen();
            // 座標更新
            startButtonRectangle.setFromCenter(ofGetWidth()/2.0, ofGetHeight() * START_BUTTON_POSITION, ofGetWidth()/2.0, startButtonImage.getHeight() * ofGetWidth()/2.0 / startButtonImage.getWidth());
            backToStartPageButton.setFromCenter(backToStartPageButtonSize.x/2., backToStartPageButtonSize.y/2., backToStartPageButtonSize.x, backToStartPageButtonSize.y);
            break;
        default:
            break;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if (startPage) {
        // スタートボタンが円の場合
        //				if (ofDist(x, y, startButtonCenterPoint.x, startButtonCenterPoint.y) <= startButtonRadius) {
        
        // スタートボタンが四角の場合
        if (startButtonRectangle.inside(x, y) && lotteryImageVector.size()>0) {
            // ルーレット中の音(ドラムロール)
            player.load("sounds/drumrollloop.wav");
            player.setLoop(true);
            player.play();
            
            // ルーレット開始
            pause = false;
            
            // スタートページを非表示
            startPage = false;
        }
    }else{
        if (pause) {
            if (backToStartPageButton.inside(x, y)) {
                // スタートページに戻る
                // 一回出たら出ないようにする
                lotteryImageVector.erase(lotteryImageVector.begin()+currentImageIndex);
                startPage = true;
            }
        }else{
            // 停止
            
            // 音
            player.load("sounds/result.wav");
            player.setLoop(false);
            player.play();
            
            
            ofLogNotice(ofToString(currentImageIndex));
            
            
            pause = true;
        }
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
