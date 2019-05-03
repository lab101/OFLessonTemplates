#include "ofApp.h"


int webcamWidth = 1280;
int webcamHeight = 720;


//--------------------------------------------------------------
void ofApp::setup(){
    colorImg.allocate(webcamWidth, webcamHeight);
    grayImage.allocate(webcamWidth, webcamHeight);
    thresholdImage.allocate(webcamWidth, webcamHeight);
    
    vidGrabber.initGrabber(webcamWidth, webcamHeight);

    gui.setup();
    gui.add(threshold.setup("threshold",100,0,255));
    gui.add(minArea.setup("minArea",100,0,webcamWidth * webcamHeight * 0.01));
    gui.add(maxArea.setup("maxArea",100,0,webcamWidth * webcamHeight));
    gui.loadFromFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    
    thresholdImage = grayImage;
    thresholdImage.threshold(threshold);

    colorImg.setFromPixels(vidGrabber.getPixels());
    // opencv color image omzetten naar gray
    grayImage = colorImg;
    
    foundResults = contourFinder.findContours(thresholdImage, minArea, maxArea, 22, true);
    
    
    if(isSending){
    
    }

    // OSC PART
    // sending to wekinator
    oscSender.setup("127.0.0.1", 6448);
    // receiving results back
    oscReceiver.setup(12000);

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    ofScale(0.45, 0.45);
    vidGrabber.draw(0, 0);
    grayImage.draw(webcamWidth + 2,0);
    thresholdImage.draw(0,webcamHeight +2 );
    contourFinder.draw(0, webcamHeight +2);
    ofPopMatrix();
    
    
    gui.setPosition(100, 600);
    gui.draw();
    
    
    if(isSending){
        ofSetColor(255,0,0);
        ofDrawCircle(900, 500, 20 + (sin(ofGetElapsedTimef() * 6) * 4));
        ofSetColor(255,255,255);

    }

   // thresholdImageDiff.draw(0, webcamHeight * 2 + 4);

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == ' '){
        
        isSending = !isSending;
        //   if(!isDrawing) lastLinePos.x = -1;
        
    }
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
