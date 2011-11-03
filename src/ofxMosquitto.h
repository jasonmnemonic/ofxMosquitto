/*
 *  ofxMosquitto.h
 *  mosquittoExample
 *
 *  Created by James George on 11/3/11.
 *
 */

#pragma once

#include "ofMain.h"
#include "mosquittopp.h"

enum ofxMosquittoQoS {
	OF_MOSQ_QOS_0_DONT_CARE = 0,
 	OF_MOSQ_QOS_1_TELL_ME	= 1,
 	OF_MOSQ_QOS_2_MUST_SUCCEED	= 2,
};


class ofxMosquitto : public mosquittopp::mosquittopp {
  public:
	ofxMosquitto();
	~ofxMosquitto();
	
	void setup(string host="localhost", int port=1883, int keepalive=60);
	void update();
	
	void publish(string topic, string message, ofxMosquittoQoS qualityOfService = OF_MOSQ_QOS_0_DONT_CARE);
	void publish(string topic, uint32_t payloadlen, const uint8_t* payload, ofxMosquittoQoS qualityOfService = OF_MOSQ_QOS_0_DONT_CARE);

	void on_connect(int rc);
	void on_disconnect();
	void on_publish(uint16_t mid);
	void on_message(const struct mosquitto_message *message);
	void on_subscribe(uint16_t mid, int qos_count, const uint8_t *granted_qos);
	void on_unsubscribe(uint16_t mid);
	void on_error();
	
  protected:
	
};