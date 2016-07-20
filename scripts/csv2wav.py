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
# Copyright (C)    2015, 2016  Alexander (MrMontag) Fust <MrMontagOpenDev@gmail.com>
#
# This Python script converts a eHealth CSV file (eHealth.ino data) to WAV.
#
import argparse
import wave
import random
import struct
import csv
import os

class DataWav:
    wavOut = None
    values = None
    targetfile = None

    def __init__(self):
        self.values = []

    def open(self, prefix, outfile):
        filename = prefix + '-' + os.path.basename(outfile)
        self.targetfile = os.path.dirname(outfile) + '/' + filename
        self.wavOut = wave.open(self.targetfile, 'w')
        # nchannels, sampwidth, framerate, nframes, comptype, compname
        self.wavOut.setparams((1, 1, 44100, 0, 'NONE', 'not compressed'))

    def add(self, value):
        packed_value = struct.pack('h', float(value))
        self.values.append(packed_value)

    def close(self):
        print self.targetfile
        self.wavOut.writeframes(''.join(self.values))
        self.wavOut.close()

class CsvProcessor:
    prefixes = ['air', 'skin', 'ecg', 'temp', 'bpm', 'oxygen']
    outfiles = []

    def createOutFiles(self, outfile):
        for prefix in self.prefixes:
            of = DataWav()
            of.open(prefix, outfile)
            self.outfiles.append(of)

    def closeOutFiles(self):
        for outfile in self.outfiles:
            outfile.close()

    def process(self, row):
        if len(row) != 6:
            return
        for i in range(len(row)):
            self.outfiles[i].add(row[i])

    def run(self, infile, outfile):
        csvin = open(infile, 'rb')
        reader = csv.reader(csvin, delimiter=';')
        self.createOutFiles(outfile)
        for row in reader:
            self.process(row)
        csvin.close()
        self.closeOutFiles()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='eHealth csv to wav converter')
    parser.add_argument('inFile')
    parser.add_argument('outFile')
    args = parser.parse_args()
    processor = CsvProcessor()
    processor.run(args.inFile, args.outFile)

