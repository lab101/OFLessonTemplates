#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){


    gui.setup();
    gui.add(noiseScale.setup("noiseScale", 0.005,0,0.01));
    gui.add(noiseDisplacement.setup("noiseDisplacement", 124.0, 10, 300));
    gui.add(noiseSpeed.setup("noiseSpeed", 4.0, 0, 18));
    gui.add(isShowDebug.setup("isShowDebug", false));

    // load previous settings
    gui.loadFromFile("settings.xml");
    
    
    // work with texture coordinates between 0 and 1
    ofDisableArbTex();
    vidGrabber.initGrabber(1280,720);
    
    mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_TRIANGLE_STRIP);
    
    
    // add texture coordinates
    // do the vertices later in update
    float stepSize = 100;
    // subtract one step because we already do a extra step when making the mesh
    // to the rightside.
    float width = vidGrabber.getWidth()-stepSize;
    float height = vidGrabber.getHeight()-stepSize;

    for(float x = 0; x < width; x += stepSize ){
        for(float y = 0; y < height; y += stepSize ){
            
            // textures
            //left top
            mesh.addTexCoord(ofVec2f(x / vidGrabber.getWidth(),y / vidGrabber.getHeight()));
            //left bottom
            mesh.addTexCoord(ofVec2f(x / vidGrabber.getWidth(),(y+stepSize) / vidGrabber.getHeight()));
            //right top
            mesh.addTexCoord(ofVec2f((x + stepSize) / vidGrabber.getWidth(),y / vidGrabber.getHeight()));
            //right bottom
            mesh.addTexCoord(ofVec2f((x + stepSize) / vidGrabber.getWidth(),(y + stepSize) / vidGrabber.getHeight()));

        }
    }
    
    
}

//--------------------------------------------------------------
void ofApp::update(){

    vidGrabber.update();
    mesh.clearVertices();
    

    float stepSize = 100;
    
    for(float x = 0; x < vidGrabber.getWidth()-stepSize; x += stepSize ){
        for(float y = 0; y < vidGrabber.getHeight()-stepSize; y += stepSize ){
            
            float time = ofGetElapsedTimef() * noiseSpeed;
            float offsetX = ofSignedNoise((x* noiseScale) + time) * noiseDisplacement;
            float offsetY = ofSignedNoise((y* noiseScale) + time) * noiseDisplacement;
            
            float offsetXStep = ofSignedNoise(((x + stepSize)  * noiseScale) + time) * noiseDisplacement;
            float offsetYStep = ofSignedNoise(((y + stepSize)  * noiseScale) + time) * noiseDisplacement;

            
            // adding the vertex points
            //left top
            mesh.addVertex(ofVec3f(x + offsetX, y + offsetY ,0));
            //left bottom
            mesh.addVertex(ofVec3f(x + offsetX, y + stepSize + offsetYStep,0));

            //right top
            mesh.addVertex(ofVec3f(x + stepSize + offsetXStep , y + offsetY ,0));
            // right bottom
            mesh.addVertex(ofVec3f(x + stepSize + offsetXStep , y + stepSize + offsetYStep ,0));
            
        }
        
        
    }
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(255, 255, 255,255);

    // setting the texture to bind our mesh to.
    vidGrabber.getTexture().bind();
    mesh.draw();
    vidGrabber.getTexture().unbind();

    
    gui.draw();

    if(isShowDebug){
        ofSetColor(255, 255, 255,10);
        mesh.drawWireframe();
    }
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
