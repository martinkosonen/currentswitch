// Uses the Energy Monitor Library (openenergymonitor.org)

#include "EmonLib.h"
#define SWITCHPIN D3
#define OUTPUTPIN D2

EnergyMonitor emon1; 		// create instance of the current monitor
float onTime;				// time that trigger is on
float offTime;				// time that trigger is off
float onDelay = 1500;		// delayed turn on (to prevent startup overcurrent on circuit)
float offDelay = 2000;		// keep output on for a period after trigger is off
int stateLast = 0;
double currentLimit = 1

void setup() {
   Serial.begin(112500);
   emon1.current(1, 60.6);	//
   pinMode(2, OUTPUT);		// This pin triggers the SSR to turn on 
   pinMode(3, INPUT_PULLUP); // This switch deactivates the current switch and opens the relay.
   digitalWrite(OUTPUTPIN, LOW);      
}

void loop() {
	double Irms = emon1.calcIrms(1480);
	
//	Serial.print(Irms*120.0); 
//	Serial.print(" ");
//	Serial.println(Irms);
		
	if(Irms >= currentLimit){
		long onTime = millis();
		if(millis() - onTime > onDelay){
			digitalWrite(OUTPUTPIN, HIGH);
			stateLast = HIGH;			
		}
	}
	
	if(Irms < currentLimit && stateLast == HIGH){
		long offTime = millis();
		if(millis() - offTime > offDelay) {
			digitalWrite(OUTPUTPIN, LOW);
			stateLast == LOW;
		}
	}
}