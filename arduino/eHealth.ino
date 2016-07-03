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
 * Copyright (C)    2016  Christopher Fust <christopher.fust@online.de>
 * Copyright (C)    2016  Alexander (MrMontag) Fust <MrMontagOpenDev@gmail.com>
 *
 * This Arduino sketch forwards e-Health Sensor Platfrom data to a serial
 * interface. For additional information please go to <https://www.cooking-hacks.com>.
 */

#include <PinChangeInt.h>
#include <eHealth.h>

int cont = 0;

void setup() {
  Serial.begin(115200);

  eHealth.initPulsioximeter();
  
  PCintPort::attachInterrupt(6, readPulsioximeter, RISING);
}

void loop() {
  Serial.print(eHealth.getAirFlow());
  Serial.print(";");
  Serial.print(eHealth.getSkinConductanceVoltage());
  Serial.print(";");
  Serial.print(eHealth.getECG());
  Serial.print(";");
  Serial.print(eHealth.getTemperature());
  Serial.print(";");
  Serial.print(eHealth.getBPM());
  Serial.print(";");
  Serial.print(eHealth.getOxygenSaturation());
  Serial.println();
}

void readPulsioximeter() {  
  if (cont++ == 50) {
    eHealth.readPulsioximeter();  
    cont = 0;
  }
}
