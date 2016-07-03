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
#include <cstdlib>
#include <string>
#include <argp.h>

#include "config.h"
#include "Controller.h"
#include "CollectorFactory.h"

const char *argp_program_version = std::string(PACKAGE_NAME).append(" ").append(VERSION).c_str();

const char *argp_program_bug_address = PACKAGE_BUGREPORT;

static char program_documentation[] =
"eHdc -- a program to collect eHealth sensor data";

static struct argp_option program_options[] = {
    {"airflow", 'a', "INTERVAL", 0, "Get airflow"},
    {"bpm", 'b', "INTERVAL", 0, "Get beats per minute (pulse)"},
    {"oxygen-saturation", 'O', "INTERVAL", 0, "Get oxygen saturation"},
    {"ecg", 'e', "INTERVAL", 0, "Get Electrocardiography"},
    {"skin-conductance-voltage", 's', "INTERVAL", 0, "Get skin conductance voltage"},
    {"temperature", 't', "INTERVAL", 0, "Get corporal temperature"},
    {"postfix", 'p', "POSTFIX", 0, "CSV file name POSTFIX"},
    {"count", 'c', "COUNT", 0, "Get a specific number of measuring points"},
    {"verbose", 'v', 0, 0, "Display detailed measurement information"},
    { 0 } 
};

static unsigned getInterval(char *arg)
{
    int interval = std::atoi(arg);
    return interval <= 0 ? INACTIVE : interval;
}

static error_t parse_option(int key, char *arg, struct argp_state *state)
{
    eHdcParams *params = static_cast<eHdcParams*>(state->input);
    switch (key)
    {
        case 'a':
            params->setAirflow(getInterval(arg));
            break;
        case 'b':
            params->setBpm(getInterval(arg));
            break;
        case 'c':
            {
                int count = std::atoi(arg);
                params->setCount(count < 0 ? 0 : count);
            }
            break;
        case 'O':
            params->setOxygenSauration(getInterval(arg));
            break;
        case 'e':
            params->setEcg(getInterval(arg));
            break;
        case 't':
            params->setTemperture(getInterval(arg));
            break;
        case 'p':
            params->setFileNamePostfix(arg);
            break;
        case 's':
            params->setSkinConductance(getInterval(arg));
            break;
        case 'v':
            params->setVerbosity(true);
            break;
        default:
            return ARGP_ERR_UNKNOWN;
    }
    return 0;
}

static struct argp argp = {
    program_options,
    parse_option,
    0,
    program_documentation
};

/**
 * @todo Keep arduPi stuff? 
 */
void loop()
{
}

/**
 * @todo Move to up-to-date C++ standard...<br />
 *       config script bcm2835-1.46 lib check<br />
         pulse, oxygen, temperatur probably not needed...
 */
int main(int argc, char **argv)
{
    eHdcParams params;
    argp_parse(&argp, argc, argv, 0, 0, &params);

    CollectorFactory *factory = new CollectorFactory(params);
    std::vector<AbstractCollector*> collectors = factory->create(); 

    Controller *controller = new Controller;
    controller->start(collectors);

    delete factory;

    exit(EXIT_SUCCESS);
}

