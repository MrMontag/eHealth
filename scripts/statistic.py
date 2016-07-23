#!/usr/bin/env python
#
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
# This Python script generates a CSV file (based on eHealth.ino and WAV data)
# with additional management ratios.
#
import argparse
import csv
import wave
import os

class CsvAnalyzer:
    def run(self, infile):
        csvin = open(infile, 'rb')
        reader = csv.reader(csvin, delimiter=';')
        counter = 0;
        for row in reader:
            if len(row) != 6:
                continue
            else:
                counter += 1
        csvin.close()
        return counter

class WavAnalyzer:
    framerate = 0;
    nframes = 0;
    
    def getduration(self):
        return self.nframes / float(self.framerate)

    def run(self, infile):
        wavin = wave.open(infile, 'rb')
        self.framerate = wavin.getframerate()
        self.nframes = wavin.getnframes()
        wavin.close()

class Statistic:
    header = ['measurement', 'npoints (csv)', 'framerate (wav)', 'nframes (wav)', 'duration (wav)', 'resolution']
    outfile = None

    def __init__(self, outfile):
        self.outfile = outfile

    def getRow(self, incsv, inwav):
        row = []
        row.append(os.path.dirname(incsv))
        csvan = CsvAnalyzer()
        npoints = csvan.run(incsv)
        row.append(npoints)
        wavan = WavAnalyzer()
        wavan.run(inwav)
        row.append(wavan.framerate)
        row.append(wavan.nframes)
        duration = wavan.getduration()
        row.append(duration)
        row.append(duration/npoints)
        return row

    def generate(self, incsv, inwav):
        exists = os.path.exists(self.outfile)
        csvfile = open(self.outfile, 'a')
        csvwriter = csv.DictWriter(csvfile, fieldnames=self.header, delimiter=';')
        if not exists:
            csvwriter.writeheader()
        row = self.getRow(incsv, inwav)
        csvwriter.writerow({'measurement': row[0], 'npoints (csv)': row[1], 'framerate (wav)': row[2], 'nframes (wav)': row[3], 'duration (wav)': row[4], 'resolution': row[5]})
        csvfile.close()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='eHealth statistic generator')
    parser.add_argument('incsv')
    parser.add_argument('inwav')
    parser.add_argument('outfile')
    args = parser.parse_args()
    statistic = Statistic(args.outfile)
    statistic.generate(args.incsv, args.inwav)

