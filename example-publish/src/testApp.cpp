#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	ofSetFrameRate(30);
	ofSetLogLevel(OF_LOG_VERBOSE);
	mosquitto = new ofxMosquitto("examplePublisher");
	mosquitto->setup();
}

//--------------------------------------------------------------
void testApp::update(){
	mosquitto->update();	
}

//--------------------------------------------------------------
void testApp::draw(){

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	uint8_t mousedata[1024];
	ofPoint p(x,y);
	memcpy(mousedata, &(p[0]), sizeof(ofPoint));
	mosquitto->publish( "/computer1/mouse", sizeof(ofPoint), mousedata);

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}