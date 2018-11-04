#include <stdint.h>
#include <stdio.h>
#include <stdexcept>
#include <time.h>
#include <unistd.h>
#include <iostream>
#include "ABE_ADCDACPi.h"

enum HeatingPad { OFF=0, LO=1, HI=2 };

class DogHouse {
    private:
        float temp_pad;
        float temp_inside;
        float temp_outside;
        float volt_battery;
        float volt_rpi;
        HeatingPad heating;

        ABElectronics_CPP_Libraries::ADCDACPi adcdac;

    public:
        DogHouse();
        ~DogHouse();
        int Init(void);

        void update_values(void);

        float GetVoltBattery();
        float GetVoltRpi();

};

