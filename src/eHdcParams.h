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
#ifndef EHDC_ARGUMENTS_H
#define EHDC_ARGUMENTS_H

#define INACTIVE            0
#define DEFAULT_INTERVAL    200000

#include <string>

class eHdcParams
{
    public:
        eHdcParams()
            : _fileNamePostfix(std::string()),
              _airflow(INACTIVE),
              _bpm(INACTIVE),
              _oxygenSaturation(INACTIVE),
              _ecg(INACTIVE),
              _temperature(INACTIVE),
              _skinConductance(INACTIVE),
              _verbosity(INACTIVE),
              _count(0)
        {
        }

        std::string fileNamePostfix() const
        {
            return _fileNamePostfix;
        }

        void setFileNamePostfix(const std::string &fileNamePostfix)
        {
            _fileNamePostfix = fileNamePostfix;
        }

        unsigned airflow() const
        {
            return _airflow;
        }

        void setAirflow(unsigned airflow)
        {
            _airflow = airflow;
        }

        unsigned bpm() const
        {
            return _bpm;
        }

        void setBpm(unsigned bpm)
        {
            _bpm = bpm;
        }

        unsigned oxygenSaturation() const
        {
            return _oxygenSaturation;
        }

        void setOxygenSauration(unsigned oxygenSaturation)
        {
            _oxygenSaturation = oxygenSaturation;
        }

        unsigned ecg() const
        {
            return _ecg;
        }

        void setEcg(unsigned ecg)
        {
            _ecg = ecg;
        }

        unsigned temperature()
        {
            return _temperature;
        }

        void setTemperture(unsigned temperature)
        {
            _temperature = temperature;
        }

        unsigned skinConductance() const
        {
            return _skinConductance;
        }

        void setSkinConductance(unsigned skinConductance)
        {
            _skinConductance = skinConductance;
        }

        unsigned verbosity() const
        {
            return _verbosity;
        }

        void setVerbosity(unsigned verbosity)
        {
            _verbosity = verbosity;
        }

        int count() const
        {
            return _count;
        }

        void setCount(unsigned count)
        {
            _count = count;
        }

    private:
        std::string _fileNamePostfix;
        unsigned _airflow;
        unsigned _bpm;
        unsigned _oxygenSaturation;
        unsigned _ecg;
        unsigned _temperature;
        unsigned _skinConductance;
        unsigned _verbosity;
        unsigned _count;
};

#endif

