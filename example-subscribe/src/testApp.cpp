#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	
	mosquitto = new ofxMosquitto("exampleSubscriber");
	mosquitto->setup();
	mosquitto->setSubscriber(this);
	mosquitto->subscribe("/+/mouse/#");
	
	receivedMouse = false;
	
	ofSetLogLevel(OF_LOG_NOTICE);
}

//--------------------------------------------------------------
void testApp::update(){
	mosquitto->update();	
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(255, 200, 10);
	if(receivedMouse){
		ofCircle(lastMouse, 10);
	}
}

void testApp::receivedMessage(const struct mosquitto_message* message){
	ofLog(OF_LOG_NOTICE, "received topic: %s");
	receivedMouse = true;
	memcpy(&lastMouse[0], message->payload, sizeof(ofPoint));
	
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
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