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
# This script creates a CSV statistic file (based on eHealth.ino and WAV data)
# for the current directory and it's subdirectories. 
#
#!/bin/bash

outfile="statistic.csv"
find -printf "%p\n" | grep -i -e ".*\.csv$" | while read -r fp
do
    cn=$(basename "$fp")
    if [[ $cn =~ statistic\.csv ]]; then
        continue
    fi

    wn=""
    dn=$(dirname "$fp")
    readlink -f $dn/*.wav | while read -r fw
    do
        bn=$(basename "$fw")
        if [[ $bn =~ ^air-.* ]] || [[ $bn =~ ^bpm-.* ]] || [[ $bn =~ ^ecg-.* ]] || [[ $bn =~ ^oxygen-.* ]] || [[ $bn =~ ^skin-.* ]] || [[ $bn =~ ^temp-.* ]]; then
            #echo "skip: $fw"
            continue
        else
            echo "$fw"
            wn="$bn"
            echo "dir: $dn"
            echo "csv: $fp"
            echo "wav: $wn"
            ./statistic.py "$fp" "$dn/$wn" "$outfile"
             echo ""
        fi
    done

    echo "output: $outfile"
done
