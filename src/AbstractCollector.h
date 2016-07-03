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
#ifndef ABSTRACT_COLLECTOR_H
#define ABSTRACT_COLLECTOR_H

#include <pthread.h>

#include "eHealth.h"
#include "TimeSpan.h"
#include "CsvWriter.h"


static pthread_mutex_t pthread_mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * @todo Move column name?
 */
class AbstractCollector
{
    public:
        enum Type
        {
            AIRFLOW             = 1,
            BPM                 = 2,
            ECG                 = 3,
            OXYGEN_SATURATION   = 4,
            SKIN_CONDUCTANCE    = 5,
            TEMPERATURE         = 6
        };

    protected:
        AbstractCollector(const std::string &fileName, unsigned count, unsigned interval)
            :   _count(count),
                _interval(interval),
                _timeSpan(new TimeSpan),
                _csvWriter(new CsvWriter(fileName))
        {
        }

    public:
        ~AbstractCollector()
        {
            delete _timeSpan;
            delete _csvWriter;
        }

        std::string name() const
        {
            return _name;
        }

        unsigned interval() const
        {
            return _interval;
        }

        void collect()
        {
            int i=0;
            while (!_count || i++<_count)
            {
                double ts = _timeSpan->timeSpan();
                double val = value();
                _csvWriter->write(ts, val);
                delayMicroseconds(_interval);
            }
        }

        virtual int type() = 0;

    protected:
        virtual double value() = 0;

    private:
        static std::string map(int type)
        {
            switch (type)
            {
                case AbstractCollector::AIRFLOW:
                    return "airflow (voltage)";
                case AbstractCollector::BPM:
                    return "bpm";
                case AbstractCollector::ECG:
                    return "ecg (voltage)";
                case AbstractCollector::OXYGEN_SATURATION:
                    return "oxygen saturation (%)";
                case AbstractCollector::SKIN_CONDUCTANCE:
                    return "skin conductance (voltage)";
                case AbstractCollector::TEMPERATURE:
                    return "temperature (°C)";
                default:
                    return "unknown";
            }
        }

    private:
        std::string _name;
        unsigned _count;
        unsigned _interval;
        TimeSpan *_timeSpan;
        CsvWriter *_csvWriter;
};

#endif

