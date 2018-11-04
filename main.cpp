/*
 * doghouse.cpp
 *
 *  Created on: 4 November 2018
 *
 *      compile with "g++ doghouse.cpp ABE_ADCDACPi.cpp  -o doghouse"
 *      run with "./doghouse"
 */
#include "doghouse.h"

void clearscreen ()
{
    printf("\033[2J\033[1;1H");
}

int main(int argc, char **argv){
	setvbuf (stdout, NULL, _IONBF, 0); // needed to print to the command line

	DogHouse doghouse1; 
	if (doghouse1.Init()) 
		return (1);	// ADCDAC open failed

	while (1){
		clearscreen();
		doghouse1.update_values();
		printf("Battery voltage: %G \n", doghouse1.GetVoltBattery()); // read the voltage from channel 1 in single ended mode
		printf("Raspberry voltage: %G \n", doghouse1.GetVoltRpi()); // read the voltage from channel 2 in single ended mode

		usleep(1000000); // sleep 0.2 seconds

	}

	return (0);
}
