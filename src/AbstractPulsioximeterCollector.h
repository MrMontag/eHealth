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
#ifndef ABSTRACT_PULSIOXIMETER_COLLECTOR_H
#define ABSTRACT_PULSIOXIMETER_COLLECTOR_H

#include "AbstractCollector.h"

class AbstractPulsioximeterCollector
    : public AbstractCollector
{
    protected:
        /**
         * @todo check interrupt stuff.
         */
        AbstractPulsioximeterCollector(const std::string &fileName, unsigned count, unsigned interval)
            : AbstractCollector(fileName, count, interval)
        {
            eHealth.initPulsioximeter();
            attachInterrupt(6, read, RISING);
        }

    public:
        virtual int type() = 0;

    private:
        static void read()
        {
            eHealth.readPulsioximeter();   
        }

    private:
        /**
         * @todo how to handle doubled int init?
         */
        static bool _initialized;
};

#endif

