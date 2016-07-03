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
#ifndef SENSOR_FACTORY_H
#define SENSOR_FACTORY_H

#include <vector>

#include "eHdcParams.h"
#include "AirflowCollector.h"
#include "EcgCollector.h"
#include "TemperatureCollector.h"
#include "BpmCollector.h"
#include "OxygenCollector.h"
#include "SkinConductanceCollector.h"

class CollectorFactory
{
    public:
        CollectorFactory(const eHdcParams &params)
            : _params(params)
        {
        }

        ~CollectorFactory()
        {
            for(std::vector<AbstractCollector*>::iterator iter=_sensors.begin();
                    iter != _sensors.end(); ++iter)
            {
                delete (*iter);
            }
        }

        std::vector<AbstractCollector*> create()
        {
            if (_sensors.size() > 0)
            {
                return _sensors;
            }
            if (_params.airflow())
            {
                _sensors.push_back(new AirflowCollector(_params.fileNamePostfix(),
                                                        _params.count(),
                                                        _params.airflow()));
            }
            if (_params.ecg())
            {
                _sensors.push_back(new EcgCollector(_params.fileNamePostfix(),
                                                    _params.count(),
                                                    _params.ecg()));
            }
            if (_params.bpm())
            {
                _sensors.push_back(new BpmCollector(_params.fileNamePostfix(),
                                                    _params.count(),
                                                    _params.bpm()));
            }
            if (_params.oxygenSaturation())
            {
                _sensors.push_back(new OxygenCollector(_params.fileNamePostfix(),
                                                       _params.count(),
                                                       _params.oxygenSaturation()));
            }
            if (_params.temperature())
            {
                _sensors.push_back(new TemperatureCollector(_params.fileNamePostfix(),
                                                            _params.count(),
                                                            _params.temperature()));
            }
            if (_params.skinConductance())
            {
                _sensors.push_back(new SkinConductanceCollector(_params.fileNamePostfix(),
                                                                _params.count(),
                                                                _params.skinConductance()));
            }
            return _sensors;
        }

    private:
        eHdcParams _params;
        std::vector<AbstractCollector*> _sensors;
};

#endif

