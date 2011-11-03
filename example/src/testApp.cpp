#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
	mosquitto.setup();
	mosquitto.setSubscriber(this);
	
	mosquitto.subscribe("/+/mouse/#");
	
	ofSetLogLevel(OF_LOG_NOTICE);
}

//--------------------------------------------------------------
void testApp::update(){
	mosquitto.update();	
}

//--------------------------------------------------------------
void testApp::draw(){

}

void testApp::receivedMessage(const struct mosquitto_message* message){
	ofLog(OF_LOG_NOTICE, "received topic: %s payload: %s ", message->topic, message->payload);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){
//	mosquitto.publish("/mouse/x", "x:"+ofToString(x)+",y:"+ofToString(y));
//	mosquitto.publish("/mouse/y", "x:"+ofToString(x)+",y:"+ofToString(y));

	mosquitto.publish("/computer1/mouse/x", "x:"+ofToString(x)+",y:"+ofToString(y));
	mosquitto.publish("/computer1/mouse/y", "x:"+ofToString(x)+",y:"+ofToString(y));

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