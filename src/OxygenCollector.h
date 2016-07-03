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
#ifndef OXYGEN_COLLECTOR_H
#define OXYGEN_COLLECTOR_H

#include "AbstractPulsioximeterCollector.h"

class OxygenCollector
    : public AbstractPulsioximeterCollector
{
    public:
        OxygenCollector(const std::string &fileNamePostfix, unsigned count, unsigned interval)
            : AbstractPulsioximeterCollector("oxygen-" + fileNamePostfix + ".csv", count, interval)
        {
        }

        virtual int type()
        {
            return AbstractCollector::OXYGEN_SATURATION;
        }

    protected:
        virtual double value()
        {
            return eHealth.getOxygenSaturation();
        }
};

#endif

