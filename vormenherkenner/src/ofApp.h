#pragma once

#include "ofMain.h"

#include "ofxOpenCv.h"
#include "ofxOsc.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp{

    
    ofxCvContourFinder      contourFinder;
    
    bool debug;
    bool isSending;
    ofxOscSender oscSender;
    //ofxOscReceiver oscReceiver;
    
    int receiverResult;
    int nrOfCountourFinderResults;
    
    ofxPanel gui;
    ofxFloatSlider threshold;
    ofxFloatSlider minArea;
    ofxFloatSlider maxArea;
    
    
    ofVideoGrabber   vidGrabber;
    
    // originele beeld van de webcam omgezet naar opencv
    ofxCvColorImage         colorImg;
    ofxCvGrayscaleImage     grayImage;
    ofxCvGrayscaleImage     thresholdImage;
   // ofxCvGrayscaleImage     result;
    ofImage previewResult;
    
    
    int webcamWidth;
    int webcamHeight;
    

    // debug variables
    ofVec3f   center;
    ofRectangle newBoundingBox;
    
    bool isCameraReadySetupDone;

    
	public:
		void setup();
        void setupWhenCameraReady();
    
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
		
};
