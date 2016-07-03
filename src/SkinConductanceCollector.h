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
#ifndef SKIN_CONDUCTANCE_COLLECTOR_H
#define SKIN_CONDUCTANCE_COLLECTOR_H

#include "AbstractCollector.h"

class SkinConductanceCollector
    : public AbstractCollector
{
    public:
        SkinConductanceCollector(const std::string &fileNamePostfix, unsigned count, unsigned interval)
            : AbstractCollector("skinConductance-" + fileNamePostfix + ".csv", count, interval)
        {
        }

        virtual int type()
        {
            return AbstractCollector::SKIN_CONDUCTANCE;
        }

    protected:
        virtual double value()
        {
            delay(2);

            pthread_mutex_lock(&pthread_mutex);
            int sensorValue = analogRead(2);
            pthread_mutex_unlock(&pthread_mutex);

            float voltage = ( sensorValue * 5.0 ) / 1023;
            delay(2);

            return voltage;
        }
};

#endif

