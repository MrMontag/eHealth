/**
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Copyright (C)    2016  Alexander (MrMontag) Fust <MrMontagOpenDev@gmail.com>
 */
#ifndef TEMPERATURE_COLLECTOR_H
#define TEMPERATURE_COLLECTOR_H

#include "AbstractCollector.h"

class TemperatureCollector
    : public AbstractCollector
{
    public:
        TemperatureCollector(const std::string &fileNamePostfix, unsigned count, unsigned interval)
            : AbstractCollector("temperature-" + fileNamePostfix + ".csv", count, interval)
        {
        }

        virtual int type()
        {
            return AbstractCollector::TEMPERATURE;
        }

    protected:
        /**
         * Gets the corporal temperature.
         */
        virtual double value()
        {
            //Local variables
            float Temperature; //Corporal Temperature 
            float Resistance;  //Resistance of sensor.
            float ganancia=5.0;
            float Vcc=3.3;
            float RefTension=3.0; // Voltage Reference of Wheatstone bridge.
            float Ra=4618.0; //Wheatstone bridge resistance.
            float Rc=4618.0; //Wheatstone bridge resistance.
            float Rb=819.0; //Wheatstone bridge resistance.

            pthread_mutex_lock(&pthread_mutex);
            int sensorValue = analogRead(3);
            pthread_mutex_unlock(&pthread_mutex);

            float voltage2=((float)sensorValue*Vcc)/1023; // binary to voltage conversion  

            // Wheatstone bridge output voltage.
            voltage2=voltage2/ganancia;
            // Resistance sensor calculate  
            float aux=(voltage2/RefTension)+Rb/(Rb+Ra);
            Resistance=Rc*aux/(1-aux);    
            if (Resistance >=1822.8) {
                // if temperature between 25ºC and 29.9ºC. R(tª)=6638.20457*(0.95768)^t
                Temperature=log(Resistance/6638.20457)/log(0.95768);  
            } else {
                if (Resistance >=1477.1){
                    // if temperature between 30ºC and 34.9ºC. R(tª)=6403.49306*(0.95883)^t
                    Temperature=log(Resistance/6403.49306)/log(0.95883);  
                } else {
                    if (Resistance >=1204.8){
                        // if temperature between 35ºC and 39.9ºC. R(tª)=6118.01620*(0.96008)^t
                        Temperature=log(Resistance/6118.01620)/log(0.96008); 
                    }
                    else{
                        if (Resistance >=988.1){
                            // if temperature between 40ºC and 44.9ºC. R(tª)=5859.06368*(0.96112)^t
                            Temperature=log(Resistance/5859.06368)/log(0.96112); 
                        }
                        else {
                            if (Resistance >=811.7){
                                // if temperature between 45ºC and 50ºC. R(tª)=5575.94572*(0.96218)^t
                                Temperature=log(Resistance/5575.94572)/log(0.96218); 
                            }
                        }
                    }
                }  
            }

            return Temperature;
        }
};

#endif
