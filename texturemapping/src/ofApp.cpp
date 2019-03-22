#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    // use 0.1 coordinates instead of image size
    ofDisableArbTex();
    
    // load the image from the data folder
    image.load("rubens.jpg");
    
    // set clamping options.
    // check http:///open.gl/textures for clamping options
    image.getTexture().setTextureWrap(GL_CLAMP_TO_BORDER, GL_CLAMP_TO_BORDER);
    
    float color[] = {0.0f,0.0f,0.0f,1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, color);
    
    
    ofSetFrameRate(60);
    ofSetLineWidth(4);
    
    //    different modes
    //
    //    OF_PRIMITIVE_TRIANGLES,
    //    OF_PRIMITIVE_TRIANGLE_STRIP,
    //    OF_PRIMITIVE_TRIANGLE_FAN,
    //    OF_PRIMITIVE_LINES,
    //    OF_PRIMITIVE_LINE_STRIP,
    //    OF_PRIMITIVE_LINE_LOOP,
    //    OF_PRIMITIVE_POINTS
    
    mesh.setMode(OF_PRIMITIVE_TRIANGLE_STRIP);
    
    ofVec3f leftTop(300,100);
    ofVec3f rightBottom(800,600);
    
    mesh.addVertex(leftTop);
    mesh.addVertex(ofVec3f(leftTop.x,rightBottom.y,0));
    mesh.addVertex(ofVec3f(rightBottom.x,leftTop.y,0));
    mesh.addVertex(rightBottom);
    
    
    mesh.addTexCoord(ofVec2f(0,0));
    mesh.addTexCoord(ofVec2f(0,1));
    mesh.addTexCoord(ofVec2f(1,0));
    mesh.addTexCoord(ofVec2f(1,1));
}



//--------------------------------------------------------------
void ofApp::update(){

}


//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 255, 255);
    
    
    image.bind();
    mesh.draw();
    image.unbind();
    
    
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), ofVec2f(10, 20));
    mesh.drawWireframe();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
