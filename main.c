// skins: Red(222, 38, 24), Blue(24, 38, 222), Black(0, 0, 0)


#include "ofApp.h"
// Red
float redX = 0;
float redY = 0;
float redRadius = 30;
float redExplode = 0;
float redBarrelAngle = 0;
float redBarrelX = 0;
float redBarrelY = 0;
float redBulletX, redBulletY;
float redBulletAngle;
float redBulletSpeed;
bool redBulletActive;
bool redBulletReached = false;
bool redHit = false;
int redHitTimer = 0;
int redLives = 3;
bool redHit = false;


//Blue
float blueX = 0;
float blueY = 0;
float blueRadius = 30;
float blueExplode = 0;
float blueBarrelAngle = 0;
float blueBarrelX = 0;
float blueBarrelY = 0;
float blueBulletX, blueBulletY;
float blueBulletAngle;
float blueBulletSpeed;
bool blueBulletActive;
bool blueBulletReached = false;
int blueLives = 3;
bool blueWasHit = false;

//--------------------------------------------------------------
void ofApp::setup(){
    blueX = ofGetWidth() / 4;
    blueY = ofGetHeight() / 2;
    blueBarrelAngle = 0;
    blueBulletSpeed = 15;
    blueBulletActive = false;
    
    
    
    redX = ofGetWidth() - blueX;
    redY = blueY;
    ofSetFrameRate(60);
    redBarrelAngle = 180;
    redBulletSpeed = 30;
    redBulletActive = false;
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    

    // Update barrel position
    redBarrelX = redX + redRadius * 2 * cos(ofDegToRad(redBarrelAngle));
    redBarrelY = redY + redRadius * 2 * sin(ofDegToRad(redBarrelAngle));
    
    // Update bullet position if active
    if (redBulletActive) {
        redBulletX += redBulletSpeed * cos(ofDegToRad(redBulletAngle));
        redBulletY += redBulletSpeed * sin(ofDegToRad(redBulletAngle));
        
        if (redBulletX < 0 || redBulletX > ofGetWidth() || redBulletY < 0 || redBulletY > ofGetHeight()) {
            redBulletActive = false;
            redBulletReached = true;
        }
        
        float impacted = (blueX - redBulletX) * (blueX - redBulletX) + (blueY - redBulletY) * (blueY - redBulletY) <= (blueRadius + 5) * (blueRadius + 5);
        
        if (impacted && !blueWasHit) {
    redBulletReached = true;
    redBulletActive = false;
    blueLives--;
    blueWasHit = true;
    }
    //explosion
    if (redBulletReached) {
        redExplode += 10;
        if (redExplode > 100) {
            redBulletReached = false;
            redExplode = 0;
            redWasHit = false;
        }
    }
    
    redBarrelX = redX + redRadius * 2 * cos(ofDegToRad(redBarrelAngle));
    redBarrelY = redY + redRadius * 2 * sin(ofDegToRad(redBarrelAngle));
    
    blueBarrelX = blueX + blueRadius * 2 * cos(ofDegToRad(blueBarrelAngle));
    blueBarrelY = blueY + blueRadius * 2 * sin(ofDegToRad(blueBarrelAngle));
    
    if (blueBulletActive) {
        blueBulletX += blueBulletSpeed * cos(ofDegToRad(blueBulletAngle));
        blueBulletY += blueBulletSpeed * sin(ofDegToRad(blueBulletAngle));
        if (blueBulletX < 0 || blueBulletX > ofGetWidth() || blueBulletY < 0 || blueBulletY > ofGetHeight()) {
            blueBulletActive = false;
            blueBulletReached = true;
        }
        
        float impacted = (redX - blueBulletX) * (redX - blueBulletX) + (redY - blueBulletY) * (redY - blueBulletY) <= (redRadius + 5) * (redRadius + 5);
        
        if (impacted && !redWasHit) {
    blueBulletReached = true;
    blueBulletActive = false;
    redLives--;
    redWasHit = true;
    }
    
    if (blueBulletReached) {
        blueExplode += 10;
        if (blueExplode > 100) {
            blueBulletReached = false;
            blueExplode = 0;
            blueWasHit = false;
        }
    }

    if (redX < ofGetWidth() / 2 + redRadius){
        redX = ofGetWidth() / 2 + redRadius;
    }
    if (redX > ofGetWidth() - redRadius){
        redX = ofGetWidth() - redRadius;
    }

    if (blueX < redRadius){
        blueX = redRadius;
    }
    if (blueX > ofGetWidth() / 2 - blueRadius){
        blueX = ofGetWidth() / 2 - blueRadius;
    }
}

//--------------------------------------------------------------
void ofApp::draw(){


    
for (int i = 0; i < redLives; i++) {
    ofSetColor(222, 38, 24);
    ofDrawCircle(ofGetWidth() - 50 - i * 40, 50, 15);
}


for (int i = 0; i < blueLives; i++) {
    ofSetColor(24, 38, 222);
    ofDrawCircle(50 + i * 40, 50, 15);
}

    
    ofSetColor(100);
    ofSetLineWidth(5);
    ofDrawLine(ofGetWidth() / 2, 0, ofGetWidth() / 2, ofGetHeight());

        if (redBulletReached == true) {
            ofSetColor(255, 0, 0);
            ofDrawCircle(redBulletX, redBulletY, redExplode);
        }

        
        ofSetColor(222, 38, 24);
        ofDrawCircle(redX, redY, redRadius);
        ofSetColor(0);
        ofSetLineWidth(50);
        ofDrawLine(redX, redY, redBarrelX, redBarrelY);

        
        if (redBulletActive) {
            ofSetColor(255, 50, 50);
            ofDrawCircle(redBulletX, redBulletY, 5);
        }

        
        ofSetColor(24, 38, 222);
        ofDrawCircle(blueX, blueY, redRadius);
        ofSetColor(0);
        ofSetLineWidth(50);
        ofDrawLine(blueX, blueY, blueBarrelX, blueBarrelY);

        
        if (blueBulletActive) {
            ofSetColor(50, 50, 255);
            ofDrawCircle(blueBulletX, blueBulletY, 5);
        }

        
        if (blueBulletReached) {
            ofSetColor(0, 0, 255);
            ofDrawCircle(blueBulletX, blueBulletY, blueExplode);
        }

        
        ofSetColor(255);
        ofDrawBitmapString("Player RED Angle: " + ofToString(redBarrelAngle, 1), 825, 20);
        ofDrawBitmapString("Player BLUE Angle: " + ofToString(blueBarrelAngle, 1), 20, 20);
    }

    

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(ofKeyEventArgs &key){
    //keypressed

        if (key.key == '.') {
            redBarrelAngle = fmod(redBarrelAngle - 5, 360);
        }
        else if (key.key == ',') {
            redBarrelAngle = fmod((redBarrelAngle + 5 + 360), 360);
        
    }
    
    if (key.key == OF_KEY_SPACE && !redBulletActive) {
        redBulletX = redBarrelX;
        redBulletY = redBarrelY;
        redBulletAngle = redBarrelAngle;
        redBulletActive = true;
        return;
    }
    
    
    if (redX > ofGetWidth() - redRadius)  redX -= 15;
    if (redX < redRadius)                 redX += 15;
    if (redY > ofGetHeight() - redRadius) redY -= 15;
    if (redY < redRadius)                 redY += 15;

    
    if (key.key == OF_KEY_RIGHT) redX += 15;
    if (key.key == OF_KEY_LEFT)  redX -= 15;
    if (key.key == OF_KEY_DOWN)  redY += 15;
    if (key.key == OF_KEY_UP)    redY -= 15;
    
    if (key.key == 'e') {
        blueBarrelAngle = fmod(blueBarrelAngle - 5 + 360, 360);
    }

    if (key.key == 'q') {
        blueBarrelAngle = fmod(blueBarrelAngle + 5, 360);
    }
    if (key.key == 'f' && !blueBulletActive) {
        blueBulletX = blueBarrelX;
        blueBulletY = blueBarrelY;
        blueBulletAngle = blueBarrelAngle;
        blueBulletActive = true;
        return;
    }
    if (blueX > ofGetWidth() - blueRadius)  blueX -= 15;
    if (blueX < blueRadius)                 blueX += 15;
    if (blueY > ofGetHeight() - blueRadius) blueY -= 15;
    if (blueY < blueRadius)                 blueY += 15;

    if (key.key == 'd') blueX += 15;
    if (key.key == 'a') blueX -= 15;
    if (key.key == 's') blueY += 15;
    if (key.key == 'w') blueY -= 15;
}


//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

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

