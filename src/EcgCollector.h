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
#ifndef ECG_COLLECTOR_H
#define ECG_COLLECTOR_H

#include "AbstractCollector.h"

class EcgCollector
    : public AbstractCollector
{
    public:
        EcgCollector(const std::string &fileNamePostfix, unsigned count, unsigned interval)
            : AbstractCollector("ecg-" + fileNamePostfix + ".csv", count, interval)
        {
        }

        virtual int type()
        {
            return AbstractCollector::ECG;
        }
        
    protected:
        virtual double value()
        {
            pthread_mutex_lock(&pthread_mutex);
            double ecg = analogRead(0);
            pthread_mutex_unlock(&pthread_mutex);
            return ecg * 5 / 1023.0;
        }
};

#endif

