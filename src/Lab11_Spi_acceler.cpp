/******************************************************/
//       THIS IS A GENERATED FILE - DO NOT EDIT       //
/******************************************************/

#include "Particle.h"
#line 1 "d:/Labs/Lab11_Spi_acceler/src/Lab11_Spi_acceler.ino"
#include "LIS3DH.h"
#include "blynk.h"

void setup();
void loop();
#line 4 "d:/Labs/Lab11_Spi_acceler/src/Lab11_Spi_acceler.ino"
SYSTEM_THREAD(ENABLED);
const unsigned long PRINT_SAMPLE_PERIOD = 100;
LIS3DHSPI accel(SPI, D3, WKP);

unsigned long lastPrintSample = 0;

void setup() {
	Blynk.begin("DISy_9aRsQHnyt8mtvZXh09rT-tdy72R", IPAddress(167, 172, 234, 162), 9090); // sets up blynk for when I print the values to Blynk
  Serial.begin(9600);//starts Serial

	delay(5000);
	LIS3DHConfig config;
	config.setAccelMode(LIS3DH::RATE_100_HZ);

	bool setupSuccess = accel.setup(config);
	Serial.printlnf("setupSuccess=%d", setupSuccess);//when the accelerometer successfully starts up, it displays this message. 
}

void loop() {
Blynk.run();//initates Blynk
	if (millis() - lastPrintSample >= PRINT_SAMPLE_PERIOD) {
		lastPrintSample = millis();

		LIS3DHSample sample;
		if (accel.getSample(sample)) {
			Serial.printlnf("%d,%d,%d", sample.x, sample.y, sample.z); //these are the values the accelerometer outputs, and it only does that if the accelerometer is able to get values. ie, is hooked up properly. 
      Blynk.virtualWrite(V1, sample.x);//wrtites the data recieved under the variable "sample.x" to the blynk graph for easy viewing of the number 
      Blynk.virtualWrite(V2, sample.y);//wrtites the data recieved under the variable "sample.y" to the blynk graph for easy viewing of the number 
      Blynk.virtualWrite(V3, sample.z);//wrtites the data recieved under the variable "sample.z" to the blynk graph for easy viewing of the number 
		}
		else {
			Serial.println("no sample");//if the accelerometer is not outputing data in anyway, it will print to the serial monitor that it was not able to gather a sample. 
		}
	}
}

//i attempted to figure out the max and min values from the sensor and print those to the blynk graph, but the blynk graph only goes from 0 - 4095, so my plan for outputting a graph that went from -60,000 to 60,000 didnt work out very well LOL
