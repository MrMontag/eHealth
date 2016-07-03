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
#ifndef TIMER_H
#define TIMER_H

#include <sys/time.h>

class TimeSpan
{
    public:
        TimeSpan()
            : _baseTime(NULL)
        {
        }

        ~TimeSpan()
        {
            delete _baseTime;
        }

        /**
         * Gets the currents time.
         */
        static timeval currentTime()
        {
            timeval currentTime;
            gettimeofday(&currentTime, NULL);
            return currentTime;
        }

        /**
         * Gets the time span between two calls of this function.
         *
         * @return Returns the time span in seconds.
         *         If called for the first time <c>0</c> is returned.
         */
        double timeSpan()
        {
            timeval currentTime;
            gettimeofday(&currentTime, NULL);

            if (!_baseTime)
            {
                _baseTime = new timeval;
                *_baseTime = currentTime;
            }

            long seconds = currentTime.tv_sec - _baseTime->tv_sec;
            long useconds = currentTime.tv_usec - _baseTime->tv_usec;

            *_baseTime = currentTime;
            return seconds + useconds/1000000.0;
        }

    private:
        timeval *_baseTime;
};

#endif

