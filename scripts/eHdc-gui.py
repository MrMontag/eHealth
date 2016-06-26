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
# This Qt GUI Python script enables the usage of eHdc via touch screen.
#
#!/usr/bin/env python

import os
import subprocess
import sys
import time
from PyQt4.QtGui import *
from PyQt4.QtCore import * 

# It was not possible to grab stdout with
# QProcess (MergedChannels/ForwardedChannels)
# ...so the python way has been used.
class CommandThread(QThread):

    stdout = None
    command = None
    process = None

    def __init__(self):
        QThread.__init__(self)

    def setCommand(self, command):
        self.command = command

    def run(self):
        self.process = subprocess.Popen(self.command, shell=True, stdout=subprocess.PIPE)
        self.stdout = self.process.communicate()[0]
        
    def getStdout(self):
        return self.stdout

    def kill(self):
        os.system("sudo pkill -TERM -P %d"%(self.process.pid))

class TestDataDialog(QWidget):

    textEdit = None 
    commandThread = CommandThread()

    def __init__(self):
        super(TestDataDialog, self).__init__()
        self.initUI()

    def initUI(self):
        hbl = QVBoxLayout()

        self.textEdit = QPlainTextEdit()
        hbl.addWidget(self.textEdit)

        okBtn = QPushButton("OK")
        okBtn.clicked.connect(self.done)
        hbl.addWidget(okBtn)

        self.commandThread.connect(self.commandThread, SIGNAL("finished()"), self.showData)

        self.setLayout(hbl)
        self.resize(500, 300)
        self.setWindowModality(Qt.ApplicationModal)
        self.setWindowTitle("Test Data Dialog")

    def display(self, params):
        self.textEdit.setPlainText("Please wait for data...")
        self.commandThread.setCommand('bash -c "sudo eHdc ' + params + ' -v -c 15"')
        self.commandThread.start()
        self.show()

    @pyqtSlot()
    def showData(self):
        self.textEdit.setPlainText(self.commandThread.getStdout())

    @pyqtSlot()
    def done(self):
        self.close()

class eHdcWidget(QWidget):

    startStopBtn = None
    commandThread = CommandThread()
    btnArray = None
    testDlg = None
    setBtnChecked = True

    def __init__(self):
        super(eHdcWidget, self).__init__()
        self.initUI()

    def initUI(self):
        hbl = QVBoxLayout()

        btnGrid = QGridLayout()

        airflowBtn = QPushButton("airflow")
        airflowBtn.setCheckable(True)
        airflowBtn.setChecked(self.setBtnChecked)
        btnGrid.addWidget(airflowBtn, 0, 0)

        bpmBtn = QPushButton("bpm")
        bpmBtn.setCheckable(True)
        bpmBtn.setChecked(self.setBtnChecked)
        btnGrid.addWidget(bpmBtn, 0, 1)

        ecgBtn = QPushButton("ecg")
        ecgBtn.setCheckable(True)
        ecgBtn.setChecked(self.setBtnChecked)
        btnGrid.addWidget(ecgBtn, 0, 2)

        oxygenBtn = QPushButton("oxygen")
        oxygenBtn.setCheckable(True)
        oxygenBtn.setChecked(self.setBtnChecked)
        btnGrid.addWidget(oxygenBtn, 1, 0)

        skinBtn = QPushButton("skin conductance")
        skinBtn.setCheckable(True)
        skinBtn.setChecked(self.setBtnChecked)
        btnGrid.addWidget(skinBtn, 1, 1)

        temperatureBtn = QPushButton("temperature")
        temperatureBtn.setCheckable(True)
        temperatureBtn.setChecked(self.setBtnChecked)
        btnGrid.addWidget(temperatureBtn, 1, 2)

        hbl.addLayout(btnGrid)
        self.startStopBtn = QPushButton("Start")
        self.startStopBtn.setStyleSheet("background-color: green; font: bold;")
        self.startStopBtn.clicked.connect(self.startStop)
        hbl.addWidget(self.startStopBtn)

        hbl.addSpacing(25)
        testBtn = QPushButton("Test Measurement")
        testBtn.clicked.connect(self.openTestDlg)
        hbl.addWidget(testBtn)

        self.btnArray = [airflowBtn, bpmBtn, ecgBtn, oxygenBtn, skinBtn, temperatureBtn]
        self.testDlg = TestDataDialog()
        self.setLayout(hbl)
        self.setWindowTitle("eHdc - GUI")
        self.show()

    def getSensorParams(self):
        sensorParams = ""
        for btn in self.btnArray:
            if btn.isChecked():
                if sensorParams != "":
                    sensorParams += " ";
                if  btn.text() == "airflow":
                    sensorParams += "-a 100"
                elif btn.text() == "bpm":
                    sensorParams += "-b 100"
                elif btn.text() == "ecg":
                    sensorParams += "-e 100"
                elif btn.text() == "oxygen":
                    sensorParams += "-O 100"
                elif btn.text() == "skin conductance":
                    sensorParams += "-s 100"
                elif btn.text() == "temperature":
                    sensorParams += "-t 100"
        return sensorParams

    @pyqtSlot()
    def startStop(self):
        if self.startStopBtn.text() == 'Start':
            self.startStopBtn.setText("Stop")
            self.startStopBtn.setStyleSheet("background-color: red; font: bold")
            command = 'bash -c "sudo eHdc ' + self.getSensorParams() + " -p " + time.strftime("%Y-%m-%d_%H-%M-%S")
            self.commandThread.setCommand(command)
            self.commandThread.start()
        else:
            self.startStopBtn.setText("Start")
            self.startStopBtn.setStyleSheet("background-color: green; font: bold")
            self.commandThread.kill()

    @pyqtSlot()
    def openTestDlg(self):
        self.testDlg.display(self.getSensorParams())

def main():
    qapp = QApplication(sys.argv)
    widget = eHdcWidget()
    sys.exit(qapp.exec_())

if __name__ == "__main__":
    main()
