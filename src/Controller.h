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
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <cstdlib>
#include <pthread.h>
#include <iostream>
#include <vector>

#include "AbstractCollector.h"

class Controller
{
    public:
        Controller()
        {
            pthread_attr_init(&_pthread_attr);
            pthread_attr_setdetachstate(&_pthread_attr, PTHREAD_CREATE_JOINABLE);
        }

        ~Controller()
        {
            pthread_attr_destroy(&_pthread_attr);
        }

        void start(const std::vector<AbstractCollector*> &collectors)
        {
            for (std::vector<AbstractCollector*>::const_iterator iter=collectors.begin();
                 iter!=collectors.end(); ++iter)
            {
                pthread_t pthread;
                int rc = pthread_create(&pthread, &_pthread_attr, collectorThread, *iter);
                if (rc)
                {
                    std::cerr << "ERROR: return code of pthread_create() is " << rc << std::endl;
                    exit(EXIT_FAILURE);
                }
                _pthreads.push_back(pthread);
            }

            void *status;
            for (std::vector<pthread_t>::iterator iter=_pthreads.begin();
                 iter!=_pthreads.end(); ++iter)
            {
                int rc = pthread_join(*iter, &status);
                if (rc)
                {
                    std::cerr << "ERROR: return code pthread_join() is " << rc << std::endl;
                    exit(EXIT_FAILURE);
                }
            }
        }

    private:
        static void *collectorThread(void* args)
        {
            AbstractCollector *collector = static_cast<AbstractCollector*>(args);
            collector->collect();
            pthread_exit(NULL);
        }

    private:
        pthread_attr_t _pthread_attr;
        std::vector<pthread_t> _pthreads;
 };

#endif

