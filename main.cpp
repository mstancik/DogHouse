/*
 * doghouse.cpp
 *
 *  Created on: 4 November 2018
 *
 *      compile with "g++ doghouse.cpp ABE_ADCDACPi.cpp  -o doghouse"
 *      run with "./doghouse"
 */
#include <ctime>
#include <iomanip>
#include <wiringPi.h>
#include "doghouse.h"
#include "DS18B20.h"
using namespace std;

void clearscreen ()
{
    printf("\033[2J\033[1;1H");
}

int main(int argc, char **argv){
	double tempBottom, tempTop, tempOut;
	time_t t;
	struct tm* now;

	setvbuf (stdout, NULL, _IONBF, 0); // needed to print to the command line

	wiringPiSetup();

	if(!strcmp(argv[1],"OFF")){ // turn off heating, light and exit process
		pinMode(8, OUTPUT);	// 15 W - LOW /30 W - HIGH
		pinMode(9, OUTPUT);	// Heating ON - HIGH / OFF - LOW
		pinMode(1, OUTPUT);	// LED ON - HIGH / OFF - LOW

		digitalWrite(8, LOW);
		digitalWrite(9, LOW);
		digitalWrite(1, LOW);
		cout << "Heating Off, Light Off..." << endl;
		return (0);
	}  

	DS18B20 w1Device1 ("28-00000970151e");
	DS18B20 w1Device2 ("28-031681ce72ff");
	DS18B20 w1Device3 ("28-0516848d9aff");
	

	DogHouse doghouse1; 
	if (doghouse1.Init()) 
		return (1);	// ADCDAC open failed

	pinMode(8, OUTPUT);	// 15 W - LOW /30 W - HIGH
	pinMode(9, OUTPUT);	// Heating ON - HIGH / OFF - LOW
	pinMode(1, OUTPUT);	// LED ON - HIGH / OFF - LOW

	digitalWrite(8, LOW);
    digitalWrite(9, LOW);
	digitalWrite(1, HIGH);

	while (1){
		doghouse1.update_values();
		//printf("Battery voltage: %G \n", doghouse1.GetVoltBattery()); // read the voltage from channel 1 in single ended mode
		//printf("Raspberry voltage: %G \n", doghouse1.GetVoltRpi()); // read the voltage from channel 2 in single ended mode
		
		tempBottom = w1Device1.getTemp();
		tempOut = w1Device2.getTemp();
		tempTop = w1Device3.getTemp();

		//clearscreen();
		t = time(0);   // get time now
    	now = localtime(&t);
    	cout <<  now->tm_mday  << '-' << (now->tm_mon + 1) << '-' << (now->tm_year + 1900) << ";";
		cout << setw(2) << setfill('0') << now->tm_hour << ":" << setw(2) << setfill('0') << now->tm_min << "." << setw(2) << setfill('0') << now->tm_sec << ";";
		cout << fixed << setprecision(2) << doghouse1.GetVoltBattery() << ";";
		cout << doghouse1.GetVoltRpi() << ";";
		cout << tempBottom << ";";
		cout << tempTop << ";";
		cout << tempOut << ";" << endl;
		delay (5*60*1000);
		//digitalWrite(1, HIGH);


		if (doghouse1.GetVoltBattery() < 11.0)
			break;
		
		//usleep(1000000); // sleep 0.2 seconds
	}

	digitalWrite(8, LOW);
    digitalWrite(9, LOW);
	return (0);
}
