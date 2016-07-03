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
#ifndef BPM_COLLECTOR_H
#define BPM_COLLECTOR_H

#include "AbstractPulsioximeterCollector.h"

class BpmCollector
    : public AbstractPulsioximeterCollector
{
    public:
        BpmCollector(const std::string &fileNamePostfix, unsigned count, unsigned interval)
            : AbstractPulsioximeterCollector("bpm-" + fileNamePostfix + ".csv", count, interval)
        {
        }

        virtual int type()
        {
            return AbstractCollector::BPM;
        }
        
    protected:
        virtual double value()
        {
            return eHealth.getBPM();
        }
};

#endif

