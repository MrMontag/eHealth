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
#ifndef FILE_WRITER_H
#define FILE_WRITER_H

#include <string>
#include <fstream>

class CsvWriter
{
    public:
        /**
         * @todo value column name.
         */
        CsvWriter(const std::string &fileName)
            : _fileName(fileName),
              _timeSpanColumnName("timeSpan (sec)"),
              _valueColumnName("")
        {
            if (!fileName.empty())
            {
                _outputStream.open(fileName.c_str());
            }
        }

        ~CsvWriter()
        {
            _outputStream.close();
        }

        /**
         * @todo header.
         */
        void write(double timeSpan, double value)
        {
            if (_outputStream.is_open())
            {
                _outputStream << timeSpan << "," << value << "\n";
                _outputStream.flush();
            }
        }
   
    private:
        std::string _fileName;
        std::string _timeSpanColumnName;
        std::string _valueColumnName;
        std::ofstream _outputStream;
};

#endif

