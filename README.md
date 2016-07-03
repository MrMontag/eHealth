# eHealth

A collection of programms, scripts and sketches for Arduino/Raspberry PI e-Health kits.

## Content

*arduino* - A collection of Arduino sketches (cooking hacks e-Health Sensor Platform kits only).

*scripts* - A collection of helper scripts, e.g. to collect data or to trigger the measurement via touch screen.

*eHdc* - A C++ program to collect cooking hacks e-Health Sensor Platform kit data. Due to the issues with this platform it should not be considered as a serious solution. 

## e-Health Kits

### cooking hacks e-Health Sensor Platform kits

<https://www.cooking-hacks.com/>


Issues

1. Non linear timeline, i.e. the interval between each measuring point is not constant.

2. The airfolw sensor provides not the full range, i.e. data is missing especially during low breathing.

3. Mutual dependency between sensors during the usage of the sensor platform with a Raspberry PI v1/2/3 and a various combination of sensors.

4. Some sensors may have a higher current going through a proband, which might be an issues if a proband has medical implants.

5. Noisy ECG and skin conductance data.

6. It seams the Pulse and Oxygen sensor does not reach the needed level of quality to provide a sufficient measurment.


### Olimex SHIELD-EKG-EMG

t.b.d.

## Conclusion

t.b.d.

Things to consider for future developmnent:

1. Base line for ECG and skin conductance.

2. Calibration mark for ECG and skin conductance.

3. Measurements with a defined intervall, e.g. 100 ms for all sensors.

7. Analyse lags and minor artifacts during the measurement with Arduino based setup and tty logging on a Raspberry PI.
