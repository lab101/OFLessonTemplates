#include "ofApp.h"



//--------------------------------------------------------------
void ofApp::setup(){
    
    webcamWidth = 1280;
    webcamHeight = 720;

    isSending = true;
    // allocate opencv images
    colorImg.allocate(webcamWidth, webcamHeight);
    grayImage.allocate(webcamWidth, webcamHeight);
    thresholdImage.allocate(webcamWidth, webcamHeight);
    
    // starting the videograbber.
    vidGrabber.setVerbose(true);
    vidGrabber.initGrabber(webcamWidth, webcamHeight);

    // gui for tweaking
    gui.setup();
    gui.add(threshold.setup("threshold",100,0,255));
    gui.add(minArea.setup("minArea",100,0,webcamWidth * webcamHeight * 0.01));
    gui.add(maxArea.setup("maxArea",100,0,webcamWidth * webcamHeight));
    gui.loadFromFile("settings.xml");
}

//--------------------------------------------------------------
void ofApp::update(){
    vidGrabber.update();
    
    // conversie webcam pixels naar opencv colorimg
    colorImg.setFromPixels(vidGrabber.getPixels());
    // opencv color image omzetten naar gray
    grayImage = colorImg;

    thresholdImage = grayImage;
    thresholdImage.threshold(threshold);

    // zoeken naar blobs
    // paramaters: 1 input image, 2 min blob grootte, 3 max blob grootte, max aantal blobs (less = minder werk), true is voor holes
    nrOfCountourFinderResults = contourFinder.findContours(thresholdImage, minArea, maxArea, 4, true);
    
    
    if(isSending && nrOfCountourFinderResults > 0){
        
      ofRectangle boundingBox  = contourFinder.blobs[0].boundingRect;
      center = boundingBox.getCenter();
        
        int maxLenght = std::max(boundingBox.getWidth(),boundingBox.getHeight());
        
        
        newBoundingBox.set(center.x -maxLenght * 0.5, center.y -maxLenght * 0.5, maxLenght,maxLenght);
      
        thresholdImage.setROI(newBoundingBox);
        previewResult.setFromPixels(thresholdImage.getRoiPixels());
        previewResult.resize(10, 10);
        
        ofxOscMessage message;
        message.setAddress("/wek/inputs");
        
        for(unsigned char p : previewResult.getPixels()){
            message.addFloatArg(p);
        }
        oscSender.sendMessage(message);

        
        //sending to wekinator
        
        
        
        
        thresholdImage.resetROI();
        
        
    }

    // OSC PART
    // sending to wekinator
    oscSender.setup("127.0.0.1", 6448);
    // receiving results back
    //oscReceiver.setup(12000);

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofPushMatrix();
    ofScale(0.45, 0.45);
    vidGrabber.draw(0, 0);
    grayImage.draw(webcamWidth + 2,0);
    thresholdImage.draw(0,webcamHeight +2 );
    contourFinder.draw(0, webcamHeight +2);
    
  
    
    // debug
    ofDrawCircle(center.x, center.y, 40);
    ofDrawRectangle(newBoundingBox);
    
    ofPopMatrix();
    
    
    ofPushMatrix();
    ofScale(10.45, 10.45);
    previewResult.draw(0, 0);
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
