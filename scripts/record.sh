# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
# Copyright (C)    2016  Alexander (MrMontag) Fust <MrMontagOpenDev@gmail.com>
#
# This script records a RPI Cam video as well as CSV data received over a serial
# device, e.g. send by an Arduino.
#
#!/bin/bash

if [[ $# -ne 1 ]] ; then
    echo "Usage:"
    echo "record.sh sec_to_run"
    exit 0
fi

DATE=$(date +%Y-%m-%d-%H-%M-%S)

# record video via RPI cam
# -t ms
raspivid -o video_$DATE.h264 -t $1*1000 -n &

# record audio via Zoom H2
# -d sec
#
# This approach does not work:
#   o arecord will not stop after the given time
#   o arecord will flood the current folder with 1k files (due to SIGUSR1?)
#arecord -D plughw:H2,0 -N -c 2 -f cd -t wav -d 10 audio_$DATE.wav &

# record eHealth data via Arduino
# 
# For testing minicom has been use. 
#   minicom -C data_$DATE.csv -b 115200 -D /dev/ttyACM0
# But to do time based tty logging ttylog will be used.
# Please mind that a modified ttylog version has been used for testing.
# In case the final changes are not yet in your software repository
# please go to <https://github.com/rocasa/ttylog>, install the latest
# version and activate the official ttylog call to use raw output (-r)
# as well as time base logging (-t).
#   ttylog -b 115200 -d /dev/ttyACM0 -t $1 -f -r | tee data_$DATE.csv
ttylog -b 115200 -d /dev/ttyACM0 -t $1 -f | tee data_$DATE.csv
