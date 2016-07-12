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
#!/usr/bin/env python
import argparse
import wave
import random
import struct
import csv

class DataWav:
    wavOut = None
    values = None

    def __init__(self):
        self.values = []

    def open(self, outfile):
        self.wavOut = wave.open(outfile, 'w')
        # nchannels, sampwidth, framerate, nframes, comptype, compname
        self.wavOut.setparams((1, 1, 44100, 0, 'NONE', 'not compressed'))

    def add(self, value):
        packed_value = struct.pack('h', float(value))
        self.values.append(packed_value)

    def close(self):
        self.wavOut.writeframes(''.join(self.values))
        self.wavOut.close()

def createOutFiles(outfile):
    prefixes = ['air', 'skin', 'ecg', 'temp', 'bpm', 'oxygen']
    outFiles = []
    for prefix in prefixes:
        outFile = DataWav()
        outFile.open(prefix + '-' + outfile)
        outFiles.append(outFile)
    return outFiles

def closeOutFiles(outFiles):
    for outFile in outFiles:
        outFile.close()

def processRow(row, outFiles):
    for i in range(len(row)):
        outFiles[i].add(row[i])

def process(infile, outfile):
    csvIn = open(infile, 'rb')
    reader = csv.reader(csvIn, delimiter=';')
    outFiles = createOutFiles(outfile)
    for row in reader:
        processRow(row, outFiles)
    csvIn.close()
    closeOutFiles(outFiles)

def main():
    parser = argparse.ArgumentParser(description='eHealth csv to wav converter')
    parser.add_argument('inFile')
    parser.add_argument('outFile')
    args = parser.parse_args()
    process(args.inFile, args.outFile)
   
if __name__ == "__main__":
    main()
