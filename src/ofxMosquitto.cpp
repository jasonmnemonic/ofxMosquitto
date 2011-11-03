/*
 *  ofxMosquitto.cpp
 *  mosquittoExample
 *
 *  Created by Jim on 11/3/11.
 *  Copyright 2011 FlightPhase. All rights reserved.
 *
 */

#include "ofxMosquitto.h"

ofxMosquitto::ofxMosquitto(string id)
: mosquittopp::mosquittopp(id.c_str())
{
	lib_init();
	subscriber = NULL;
}

ofxMosquitto::~ofxMosquitto(){
	lib_cleanup();
}

void ofxMosquitto::setSubscriber(ofxMosquittoSubscriber* sub){
	subscriber = sub;
}

void ofxMosquitto::setup(string host, int port, int keepalive){
	ofLogVerbose("ofxMosquitto -- connecting to " + host + " on port " + ofToString(port) );
	connect(host.c_str(), port, keepalive);
}

/*
 * reference for what loop returns
 *	MOSQ_ERR_SUCCESS -   on success.
 * 	MOSQ_ERR_INVAL -     if the input parameters were invalid.
 * 	MOSQ_ERR_NOMEM -     if an out of memory condition occurred.
 * 	MOSQ_ERR_NO_CONN -   if the client isn't connected to a broker.
 *  MOSQ_ERR_CONN_LOST - if the connection to the broker was lost.
 *	MOSQ_ERR_PROTOCOL -  if there is a protocol error communicating with the
 *                       broker.
 */
void ofxMosquitto::update(){
	int ret = loop();
	if(ret != MOSQ_ERR_SUCCESS){
		switch (ret) {
			case MOSQ_ERR_INVAL:
				ofLogError("ofxMosquitto -- MOSQ_ERR_INVAL - the input parameters were invalid.");
				break;
			case MOSQ_ERR_NOMEM:
				ofLogError("ofxMosquitto -- MOSQ_ERR_NOMEM - an out of memory condition occurred.");
				break;
			case MOSQ_ERR_NO_CONN:
				ofLogError("ofxMosquitto -- MOSQ_ERR_NO_CONN - the client isn't connected to a broker.");
				break;
			case MOSQ_ERR_CONN_LOST:
				ofLogError("ofxMosquitto -- MOSQ_ERR_CONN_LOST - the connection to the broker was lost.");
				break;
			case MOSQ_ERR_PROTOCOL:
				ofLogError("ofxMosquitto -- MOSQ_ERR_PROTOCOL - there is a protocol error communicating with the broker.");
				break;
			default:
				ofLogError("ofxMosquitto -- Unknown error");
				break;
		}
	}
	//ret = loop_write();
}

void ofxMosquitto::subscribe(uint16_t* messageId, string topic, ofxMosquittoQoS qualityOfService) {
	mosquittopp::mosquittopp::subscribe(messageId, topic.c_str(), (int)qualityOfService);
}

void ofxMosquitto::subscribe(string topic, ofxMosquittoQoS qualityOfService){
	subscribe(NULL, topic, qualityOfService);
}

void ofxMosquitto::unsubscribe(string topic){
	mosquittopp::mosquittopp::unsubscribe(NULL, topic.c_str());
}

void ofxMosquitto::publish(string topic, string message, ofxMosquittoQoS qualityOfService){
	publish(topic, message.size(), (uint8_t*)(&message[0]), qualityOfService);
}

void ofxMosquitto::publish(string topic, uint32_t payloadlen, const uint8_t* payload, ofxMosquittoQoS qualityOfService){
	mosquittopp::mosquittopp::publish(NULL, topic.c_str(), payloadlen, payload, (int)qualityOfService, false);
}

void ofxMosquitto::on_connect(int rc){
	ofLogNotice("ofxMosquitto -- connected successfully");	
}

void ofxMosquitto::on_disconnect(){

}

void ofxMosquitto::on_publish(uint16_t mid){

}

void ofxMosquitto::on_message(const struct mosquitto_message *message){
	if(subscriber != NULL){
		if(message->payloadlen){
			subscriber->receivedMessage(message);
		}
		else{
			ofLogError("ofxMosquitto -- empty message received");
		}
	}
}

void ofxMosquitto::on_subscribe(uint16_t mid, int qos_count, const uint8_t *granted_qos){
	ofLogNotice("ofxMosquitto -- Subscribed successfully");
}

void ofxMosquitto::on_unsubscribe(uint16_t mid){

}

void ofxMosquitto::on_error(){

}

/*
void ofxMosquitto::message_callback(void *obj, struct mosquitto_message *message)
{
	if(message->payloadlen){
		printf("%s %s\n", message->topic, message->payload);
	}else{
		printf("%s (null)\n", message->topic);
	}
	fflush(stdout);
}

void ofxMosquitto::connect_callback(void *obj, int result)
{
	struct mosquitto *mosq = obj;
	
	int i;
	if(!result){
		mosquitto_subscribe(mosq, topics[i], topic_qos);
	}else{
		fprintf(stderr, "Connect failed\n");
	}
}

void ofxMosquitto::subscribe_callback(void *obj, uint16_t mid, int qos_count, const uint8_t *granted_qos)
{
	int i;
	
	printf("Subscribed (mid: %d): %d", mid, granted_qos[0]);
	for(i=1; i<qos_count; i++){
		printf(", %d", granted_qos[i]);
	}
	printf("\n");
}
*/