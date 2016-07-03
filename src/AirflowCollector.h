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
#ifndef AIRFLOW_COLLECTOR_H
#define AIRFLOW_COLLECTOR_H

#include "AbstractCollector.h"

class AirflowCollector
    : public AbstractCollector
{
    public:
        AirflowCollector(const std::string &fileNamePostfix, unsigned count, unsigned interval)
            : AbstractCollector("airflow-" + fileNamePostfix + ".csv", count, interval)
        {
        }

        virtual int type()
        {
            return AbstractCollector::AIRFLOW;
        }
        
    protected:
        virtual double value()
        {
            pthread_mutex_lock(&pthread_mutex);
            double airflow = analogRead(1);
            pthread_mutex_unlock(&pthread_mutex);
            return airflow;
        }
};

#endif

