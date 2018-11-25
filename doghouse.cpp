#include "doghouse.h"

DogHouse::DogHouse(){
    heating = OFF;  
}

DogHouse::~DogHouse(){
    adcdac.close_adc(); // close DAC spi channel
}

int DogHouse::Init(void){
    if(adcdac.open_adc() != 1) // open the DAC spi channel
		return (1); // if the SPI bus fails to open exit the program
    else 
        return (0);
}

void DogHouse::update_values(void){
    volt_battery = adcdac.read_adc_voltage(1, 0)*5.01;
    volt_rpi = adcdac.read_adc_voltage(2, 0)*5.01;
}

float DogHouse::GetVoltBattery(){
    return volt_battery;
}

float DogHouse::GetVoltRpi(){
    return volt_rpi;
}