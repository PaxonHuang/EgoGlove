## 6-axis inertial measurement unit (IMU) and AI sensor with embedded sensor fusion, Qvar for high-end applications

![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/a8a5580c16e6ada32e34b40dab83896fa40c9124062af748fb1ff09abfb28c61.jpg)



LGA-14L (2.5 x 3.0 x 0.83 mm) typ.


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/b41bd8e922a31e37ce71721259ceb98fa610b6d894280cf50648f713bd0e1ef5.jpg)


## Product status link

LSM6DSV16X 

<table><tr><td colspan="3">Product summary</td></tr><tr><td>Order code</td><td>LSM6DSV16X</td><td>LSM6DSV16XTR</td></tr><tr><td>Temp. range [°C]</td><td colspan="2">-40 to +85</td></tr><tr><td>Package</td><td colspan="2">LGA-14L(2.5 x 3.0 x 0.83 mm)</td></tr><tr><td>Packing</td><td>Tray</td><td>Tape and reel</td></tr></table>

## Product resources

AN5763 (device application note) 

AN5882 (finite state machine) 

AN5804 (machine learning core) 

AN5755 (Qvar sensing) 

TN0018 (design and soldering) 

## Product label

![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/aa683ea6ef95399d871b8e163fd73a254b21b5be4754fe47edd3159d3cf368a7.jpg)


## Features

Triple-channel architecture for UI, EIS, and OIS data processing 

"Always-on" experience with low power consumption for both accelerometer and gyroscope 

Smart FIFO up to 4.5 KB 

Android compliant 

±2/±4/±8/±16 g full scale 

±125/±250/±500/±1000/±2000/±4000 dps full scale 

SPI / I²C & MIPI I3C<sup>®</sup> v1.1 serial interface with main processor data synchronization 

Auxiliary SPI for OIS data output for gyroscope and accelerometer 

OIS configurable from aux. SPI, primary interface (SPI / I²C & MIPI I3C<sup>®</sup> v1.1) 

EIS dedicated channel on primary interface with dedicated filtering 

Advanced pedometer, step detector, and step counter 

Significant motion detection, tilt detection 

Standard interrupts: free-fall, wake-up, 6D/4D orientation, click and double click 

Programmable finite state machine for accelerometer, gyroscope, and externa sensor data processing with high rate @ 960 Hz 

Machine learning core with exportable features and filters for AI applications 

Embedded adaptive self-configuration (ASC) 

Embedded Qvar (electrostatic sensor) for user interface functions (tap, double tap, triple tap, long press, L/R – R/L swipe) 

Embedded analog hub for ADC and processing analog input data 

Embedded sensor fusion low-power algorithm 

Embedded temperature sensor 

Analog supply voltage: 1.71 V to 3.6 V 

Independent IO supply (extended range: 1.08 V to 3.6 V) 

Power consumption: 0.65 mA in combo high-performance mode 

Compact footprint: 2.5 mm x 3 mm x 0.83 mm 

ECOPACK and RoHS compliant 

## Applications

Motion tracking and gesture detection, augmented reality (AR) / virtual reality (VR) / mixed reality (MR) applications & metaverse applications 

Wearables 

Indoor navigation 

IoT and connected devices 

Smartphones and handheld devices 

EIS and OIS for camera applications 

Vibration monitoring and compensation 

## Description

The LSM6DSV16X is a high-performance, low-power 6-axis small IMU, featuring a 3-axis digital accelerometer and a 3-axis digital gyroscope, that offers the best IMU sensor with a triple-channel architecture for processing acceleration and angular rate data on three separate channels (user interface, OIS, and EIS) with dedicated configuration, processing, and filtering. 

The LSM6DSV16X enables processes in edge computing, leveraging embedded advanced dedicated features such as a finite state machine (FSM) for configurable motion tracking and a machine learning core (MLC) for context awareness with exportable AI features for IoT applications. 

The LSM6DSV16X supports the adaptive self-configuration (ASC) feature, which allows the FSM to automatically reconfigure the device in real time based on the detection of a specific motion pattern or based on the output of a specific decision tree configured in the MLC, without any intervention from the host processor. 

The LSM6DSV16X embeds Qvar (electric charge variation detection) for user interface functions like tap, double tap, triple tap, long press, or L/R – R/L swipe. 

The LSM6DSV16X embeds an analog hub able to connect an external analog input and convert it to a digita signal for processing. 

## Overview

The LSM6DSV16X is a system-in-package featuring a high-performance 3-axis digital accelerometer and 3-axis digital gyroscope. 

The LSM6DSV16X delivers best-in-class motion sensing that can detect orientation and gestures in order to empower application developers and consumers with features and capabilities that are more sophisticated than simply orienting their devices to portrait and landscape mode. 

The event-detection interrupts enable efficient and reliable motion tracking and context awareness, implementing hardware recognition of free-fall events, 6D orientation, click and double-click sensing, activity or inactivity, stationary/motion detection and wake-up events. Machine learning and finite state machine processing allow moving some algorithms from the application processor to the LSM6DSV16X sensor, enabling consistent reduction of power consumption. 

The LSM6DSV16X supports the main OS requirements, offering real, virtual, and batch mode sensors. In addition, the LSM6DSV16X can efficiently run the sensor-related features specified in Android, saving power and enabling faster reaction time. In particular, the LSM6DSV16X has been designed to implement hardware features such as significant motion detection, stationary/motion detection, tilt, pedometer functions, timestamping and to support the data acquisition of external sensors. 

The LSM6DSV16X offers hardware flexibility to connect the pins with different mode connections to externa sensors to expand functionalities such as adding a sensor hub, auxiliary SPI, and so forth. 

The LSM6DSV16X offers advanced design flexibility for OIS and EIS applications. Both channels have a dedicated processing path with independent filtering and enhanced EIS channel gyroscope data are read over the primary interfaces I²C/ MIPI I3C<sup>®</sup> v1.1 / SPI. 

Channel 1 has been designed for user interface data processing for motion tracking. Data are available on the primary output of I²C / SPI / I3C<sup>®</sup> for the accelerometer and gyroscope with independent ODR and FS. 

Channel 2 has been designed for OIS applications. Data are available on the aux SPI at 7.68 kHz with accelerometer/gyroscope processing with independent FS at ±2 g - ±16 g (accelerometer) / ±125 dps - ±2000 dps (gyroscope). The accelerometer is also available as standalone with dedicated filtering. 

Channel 3 has been design for enhanced EIS. Data are available in freerun mode in the output registers or in FIFO with dedicated tag and timestamp. 

Up to 4.5 KB of FIFO with compression and dynamic allocation of significant data (that is, external sensors, timestamp, and so forth) allows overall power saving of the system. 

The LSM6DSV16X embeds a sensor fusion low-power (SFLP) algorithm able to provide a 6-axis (accelerometer + gyroscope) game rotation vector represented as a quaternion. The X, Y, Z quaternion components are stored in FIFO. 

Like the entire portfolio of MEMS sensor modules, the LSM6DSV16X leverages the robust and mature in-house manufacturing processes already used for the production of micromachined accelerometers and gyroscopes. The various sensing elements are manufactured using specialized micromachining processes, while the IC interfaces are developed using CMOS technology that allows the design of a dedicated circuit, which is trimmed to better match the characteristics of the sensing element. 

The LSM6DSV16X embeds an analog hub, which is able to connect an external analog input and convert it to a digital signal for processing as well as advanced dedicated features like a finite state machine and data filtering for OIS, EIS, and motion processing. 

The LSM6DSV16X embeds Qvar functionality, which is an electrostatic sensor able to measure the variation of the quasi-electrostatic potential. The Qvar sensing channel can be used for user interface applications like tap, double tap, triple tap, long press, and L/R – R/L swipe. 

The LSM6DSV16X is available in a small plastic land grid array (LGA) package of 2.5 x 3.0 x 0.83 mm to address ultracompact solutions. 

## Embedded low-power features

The LSM6DSV16X has been designed to be fully compliant with Android, featuring the following on-chip functions: 

4.5 KB FIFO data buffering, data can be compressed two or three times 

100% efficiency with flexible configurations and partitioning 

Possibility to store timestamp 

Event-detection interrupts (fully configurable) 

Free-fall 

Wake-up 

6D orientation 

Click and double-click sensing 

Activity/inactivity recognition 

Stationary/motion detection 

Specific IP blocks (called "embedded functions") with negligible power consumption and high performance 

Pedometer functions: step detector and step counters 

Tilt 

Significant motion detection 

Finite state machine (FSM) 

Machine learning core (MLC) with exportable features and filters for AI applications 

Adaptive self-configuration (ASC) 

Embedded sensor fusion low-power (SFLP) algorithm 

Sensor hub 

Up to six total sensors: two internal (accelerometer and gyroscope) and four external sensors 

Analog hub for processing external analog input data 

Qvar: electric charge variation detection 

## Pedometer functions: step detector and step counters

The LSM6DSV16X embeds an advanced pedometer with an algorithm running in an ultralow-power domain in order to ensure extensive battery life in battery-constrained applications. 

Leveraging enhanced configurability, the advanced embedded pedometer is suitable for a large range of applications from mobile to wearable devices. 

The algorithm processes and analyzes the accelerometer waveform in order to count the user's steps during walking and running activities. 

The pedometer works at 30 Hz and it is not affected by the selected device power mode (ultralow-power, lowpower, high-performance), thus guaranteeing an ultralow-power experience and extreme flexibility in conjunction with other device functionalities. 

The pedometer output can be batched in the device's FIFO buffer, in order to decrease overall system current consumption. 

ST freely provides the support and the tools for easily configuring the device and tuning the algorithm configuration for a best-in-class user experience. 

## 2.2

## Pedometer algorithm

The pedometer algorithm is composed of a cascade of four stages: 

1. Computation of the acceleration magnitude signal in order to detect the signal independently from device orientation; 

2. FIR filter to extract relevant frequency components and to smooth the signal by cutting off high frequencies; 

3. Peak detector to find the maximum and minimum of the waveform and compute the peak-to-peak value; 

4. Step count: if the peak-to-peak value is greater than the settled threshold, a step is counted. 


Figure 1. Four-stage pedometer algorithm


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/d76793f13dee4b63d986e06519160815001afbe1e4e51386fef4093baf804307.jpg)


The LSM6DSV16X embeds a dynamic internal threshold for step detection that is updated after each peak-topeak evaluation: the internal threshold is increased with a configurable speed if a step is detected or decreased with a configurable speed if a step is not detected. 

This approach ensures high accuracy when the user starts to walk and a false peak rejection when the user is walking or running. 

An internal configurable debounce algorithm can be also set to filter false walks: indeed, an accelerometer pattern is recognized as a walk or run only if a minimum number of steps are counted. 

The LSM6DSV16X has been designed to reject a false-positive signal inside the algorithm core. 

On top of the mechanisms detailed above, the LSM6DSV16X allows enabling and configuring a dedicated false-positive rejection block to further boost pedometer accuracy. 

## 2.3

## Tilt detection

The tilt function helps to detect activity change and has been implemented in hardware using only the accelerometer to achieve targets of both ultralow power consumption and robustness during the short duration of dynamic accelerations. 

The tilt function is based on a trigger of an event each time the device's tilt changes and can be used with different scenarios, for example: 

Triggers when a phone is in a front pants pocket and the user goes from sitting to standing or standing to sitting; 

Does not trigger when a phone is in a front pants pocket and the user is walking, running, or going upstairs. 

## 2.4

## Significant motion detection

The significant motion detection (SMD) function generates an interrupt when a ‘significant motion’, that could be due to a change in user location, is detected. In the LSM6DSV16X device this function has been implemented in hardware using only the accelerometer 

SMD functionality can be used in location-based applications in order to receive a notification indicating when the user is changing location. 

## 2.5

## Finite state machine

The LSM6DSV16X can be configured to generate interrupt signals activated by user-defined motion patterns. To do this, up to 8 embedded finite state machines can be programmed independently for motion detection such as glance gestures, absolute wrist tilt, shake and double-shake detection. 

## Definition of finite state machine

A state machine is a mathematical abstraction used to design logic connections. It is a behavioral model composed of a finite number of states and transitions between states, similar to a flow chart in which one can inspect the way logic runs when certain conditions are met. The state machine begins with a start state, goes to different states through transitions dependent on the inputs, and can finally end in a specific state (called stop state). The current state is determined by the past states of the system. The following figure shows a generic state machine. 


Figure 2. Generic state machine


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/151b8846c68ede872d4d82b9543d9ab449f3b0d3fc5e27f108ffd154708fb78b.jpg)


## Finite state machine in the LSM6DSV16X

The LSM6DSV16X works as a combo accelerometer-gyroscope sensor, generating acceleration and angular rate output data. It is also possible to connect an external sensor like a magnetometer or pressure sensor by using the sensor hub feature (mode 2). These data can be used as input of up to 8 programs in the embedded finite state machine (Figure 3. State machine in the LSM6DSV16X). 

All 8 finite state machines are independent: each one has its dedicated memory area and it is independently executed. An interrupt is generated when the end state is reached or when some specific command is performed. 


Figure 3. State machine in the LSM6DSV16X


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/7b06b9659b12980ed79709510e10e466e05f4962d071915e6cde839d6e03c94a.jpg)


## 2.6

## Machine learning core

The LSM6DSV16X embeds a dedicated core for machine learning processing that provides system flexibility, allowing some algorithms run in the application processor to be moved to the MEMS sensor with the advantage of consistent reduction in power consumption. 

Machine learning core logic allows identifying if a data pattern (for example motion, pressure, temperature, magnetic data, and so forth) matches a user-defined set of classes. Typical examples of applications could be activity detection like running, walking, driving, and so forth. 

The LSM6DSV16X machine learning core works on data patterns coming from the accelerometer and gyro sensors, but it is also possible to connect and process external sensor data (like magnetometer or pressure sensor) by using the sensor hub feature (mode 2). 

The input data can be filtered using a dedicated configurable computation block containing filters and features computed in a fixed time window defined by the user. Computed feature values and filtered data values can also be read through the FIFO buffer. 

Machine learning processing is based on logical processing composed of a series of configurable nodes characterized by "if-then-else" conditions where the "feature" values are evaluated against defined thresholds. 


Figure 4. Machine learning core in the LSM6DSV16X


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/d8300a1fe98c694c0d3bf8ecaf3f6998c7bd9b4ba430eee0e0a4208f967fe7d9.jpg)


The LSM6DSV16X can be configured to run up to 4 decision trees simultaneously and independently and every decision tree can generate up to 16 results. The total number of nodes can be up to 128. 

The results of the machine learning processing are available in dedicated output registers readable from the application processor at any time. 

The LSM6DSV16X machine learning core can be configured to generate an interrupt when a change in the result occurs. 

## 2.7

## Adaptive self-configuration (ASC)

The LSM6DSV16X supports the adaptive self-configuration (ASC) feature, which allows the FSM to automatically reconfigure the device in real time based on the detection of a specific motion pattern or based on the output of a specific decision tree configured in the MLC, without any intervention from the host processor. The FSM can write a subset of the device registers using the SETR command, which allows indicating the register address and the new value to be written in such a register. The access to these device registers is mutually exclusive to the host. 

## 2.8

## Sensor fusion low power

A sensor fusion low-power (SFLP) block is available in the LSM6DSV16X for generating the following data based on the accelerometer and gyroscope data processing: 

Game rotation vector, which provides a quaternion representing the attitude of the device 

Gravity vector, which provides a three-dimensional vector representing the direction of gravity 

Gyroscope bias, which provides a three-dimensional vector representing the gyroscope bias 

The SFLP block is enabled by setting the SFLP_GAME_EN bit to 1 of the EMB_FUNC_EN_A (04h) embedded functions register. 

The SFLP block can be reinitialized by setting the SFLP_GAME_INIT bit to 1 of the EMB_FUNC_INIT_A (66h) embedded functions register. 


Table 1. Sensor fusion performance


<table><tr><td colspan="2">Parameter</td><td>Value</td></tr><tr><td rowspan="3">Static accuracy</td><td>heading / yaw</td><td>0.5 deg. / 5 minutes</td></tr><tr><td>pitch</td><td>1.5 deg.</td></tr><tr><td>roll</td><td>1.5 deg.</td></tr><tr><td rowspan="3">Low dynamic accuracy</td><td>heading / yaw</td><td>0.7 deg. / 5 minutes</td></tr><tr><td>pitch</td><td>0.5 deg.</td></tr><tr><td>roll</td><td>0.5 deg.</td></tr><tr><td rowspan="3">High dynamic accuracy</td><td>heading / yaw</td><td>5.9 deg. / 5 minutes</td></tr><tr><td>pitch</td><td>1.6 deg.</td></tr><tr><td>roll</td><td>1.2 deg.</td></tr><tr><td>Calibration time</td><td></td><td><eq>0.8 \text{ seconds}^{(1)}</eq></td></tr><tr><td>Orientation stabilization time</td><td></td><td>0.7 seconds</td></tr></table>

1. Time required to reach steady state 

## Pin description

![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/7a2e68d094762171433dff239316d3a38f39062fe196cd6ace68377e160ad72d.jpg)



Direction of detectable acceleration (top view)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/978df3116f10b874717d68a94d04deaaefc66c2784424a61081b6e6c7c5d89d2.jpg)



Direction of detectable angular rate (top view)



Figure 5. Pin connections


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/d3ec4d53f1b0239cd065b6dd7928aeb2fc546d759727d1cb28e8675020e358a9.jpg)


## 3.1

## Pin connections

The LSM6DSV16X offers flexibility to connect the pins in order to have three different mode connections and functionalities. In detail: 

Mode 1: I²C / MIPI ${ \mathsf { I } } 3 0 ^ { \otimes }$ slave interface or SPI (3- and 4-wire) serial interface is available. The analog hub and Qvar functionalities are available in mode 1 with I²C interface only. 

Mode 2: I²C / MIPI ${ \mathsf { I } } 3 { \mathsf { C } } ^ { \circledast }$ slave interface or SPI (3- and 4-wire) serial interface and I²C interface master for external sensor connections are available. 

Mode 3: I²C / MIPI ${ \mathsf { I } } 3 { \mathsf { C } } ^ { \circledast }$ slave interface or SPI (3- and 4-wire) serial interface is available for the application processor interface while an auxiliary SPI (3- and 4-wire) serial interface for external sensor connections is available for the accelerometer and gyroscope. 

Refer to the product application note for the details regarding operating/power mode configurations, settings, turn-on/off time and on-the-fly changes. 


Figure 6. LSM6DSV16X connection modes


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/eb1c08aae8cfb84d8dfe9e3978cd9e391540a1d308add03f69513c33d0abaee1.jpg)


In the following table, each mode is described for the pin connections and function. 


Table 2. Pin description


<table><tr><td>Pin#</td><td>Name</td><td>Mode 1 function</td><td>Mode 2 function</td><td>Mode 3 function</td></tr><tr><td>1</td><td><eq>SDO/SA0^{(1)}</eq></td><td>SPI 4-wire interface serial data output (SDO)<eq>I^2C least significant bit of the device address (SA0)</eq></td><td>SPI 4-wire interface serial data output (SDO)<eq>I^2C least significant bit of the device address (SA0)</eq></td><td>SPI 4-wire interface serial data output (SDO)<eq>I^2C least significant bit of the device address (SA0)</eq></td></tr><tr><td>2</td><td>SDx/AH1/Qvar1</td><td>Connect to Vdd_IO or GND if the analog hub and Qvar are disabled.AH input 1 (or Qvar electrode 1) is connected if the analog hub (or Qvar functionality) is enabled.</td><td><eq>I^2C serial data master (MSDA)</eq></td><td>Auxiliary SPI 3/4-wire interface serial data input (SDI_Aux)and SPI 3-wire serial data output (SDO_Aux)</td></tr><tr><td>3</td><td>SCx/AH2/Qvar2</td><td>Connect to Vdd_IO or GND if the analog hub and Qvar are disabled.AH input 2 (or Qvar electrode 2) is connected if the analog hub (or Qvar functionality) is enabled.</td><td><eq>I^2C serial clock master (MSCL)</eq></td><td>Auxiliary SPI 3/4-wire interface serial port clock (SPC_Aux)</td></tr><tr><td>4</td><td>INT1</td><td colspan="3">Programmable interrupt in <eq>I^2C and SPI</eq></td></tr><tr><td>5</td><td><eq>Vdd_IO^{(2)}</eq></td><td colspan="3">Power supply for I/O pins</td></tr><tr><td>6</td><td>GND</td><td colspan="3">0 V supply</td></tr><tr><td>7</td><td>GND</td><td colspan="3">0 V supply</td></tr><tr><td>8</td><td><eq>Vdd^{(2)}</eq></td><td colspan="3">Power supply</td></tr><tr><td>9</td><td>INT2</td><td>Programmable interrupt 2 (INT2) / Data enable (DEN)</td><td>Programmable interrupt 2 (INT2) / Data enable (DEN) / <eq>I^2C master external synchronization signal (MDRDY)</eq></td><td>Programmable interrupt 2 (INT2) / Data enable (DEN)</td></tr><tr><td>10</td><td>OCS_Aux</td><td>Connect to Vdd_IO or leave unconnected<eq>^{(3)}</eq></td><td>Connect to Vdd_IO or leave unconnected<eq>^{(3)}</eq></td><td>Enable auxiliary SPI 3/4-wire interface</td></tr><tr><td>11</td><td>SDO_Aux</td><td>Connect to Vdd_IO or leave unconnected<eq>^{(3)}</eq></td><td>Connect to Vdd_IO or leave unconnected<eq>^{(3)}</eq></td><td>Auxiliary SPI 3-wire interface: leave unconnected<eq>^{(3)}</eq>Auxiliary SPI 4-wire interface: serial data output (SDO_Aux)</td></tr><tr><td>12</td><td><eq>CS^{(1)}</eq></td><td><eq>I^2C / MIPI I3C^® / SPI mode selection (1: SPI idle mode / I^2C / MIPI I3C^® communication enabled; 0: SPI communication mode / I^2C / MIPI I3C^® disabled)</eq></td><td><eq>I^2C / MIPI I3C^® / SPI mode selection (1: SPI idle mode / I^2C / MIPI I3C^® communication enabled; 0: SPI communication mode / I^2C / MIPI I3C^® disabled)</eq></td><td><eq>I^2C / MIPI I3C^® / SPI mode selection (1: SPI idle mode / I^2C / MIPI I3c^® communication enabled; 0: SPI communication mode / I^2C / MIPI I3C^® disabled)</eq></td></tr><tr><td>13</td><td><eq>SCL^{(1)}</eq></td><td><eq>I^2C / MIPI I3C^® serial clock (SCL) SPI serial port clock (SPC)</eq></td><td><eq>I^2C / MIPI I3C^® serial clock (SCL) SPI serial port clock (SPC)</eq></td><td><eq>I^2C / MIPI I3C^® serial clock (SCL) SPI serial port clock (SPC)</eq></td></tr><tr><td>14</td><td><eq>SDA^{(1)}</eq></td><td><eq>I^2C / MIPI I3C^® serial data (SDA) SPI serial data input (SDI) 3-wire interface serial data output (SDO)</eq></td><td><eq>I^2C / MIPI I3C^® serial data (SDA) SPI serial data input (SDI) 3-wire interface serial data output (SDO)</eq></td><td><eq>I^2C / MIPI I3C^® serial data (SDA) SPI serial data input (SDI) 3-wire interface serial data output (SDO)</eq></td></tr></table>


1. SPI 3/4-wire interface not available with the analog hub / Qvar functionality enabled. 



2. Recommended 100 nF filter capacitor. 



3. Leave pin electrically unconnected and soldered to PCB 


## Module specifications

## 4.1 Mechanical characteristics

@ Vdd = 1.8 V, T = 25 °C, unless otherwise noted. 


Table 3. Mechanical characteristics


<table><tr><td>Symbol</td><td>Parameter</td><td>Test conditions</td><td>Min.</td><td><eq>Typ.^{(1)}</eq></td><td>Max.</td><td>Unit</td></tr><tr><td rowspan="4">LA_FS</td><td rowspan="4">Linear acceleration measurement range</td><td></td><td></td><td>±2</td><td></td><td rowspan="4">g</td></tr><tr><td></td><td></td><td>±4</td><td></td></tr><tr><td></td><td></td><td>±8</td><td></td></tr><tr><td></td><td></td><td>±16</td><td></td></tr><tr><td rowspan="6">G_FS</td><td rowspan="6">Angular rate measurement range</td><td></td><td></td><td>±125</td><td></td><td rowspan="6">dps</td></tr><tr><td></td><td></td><td>±250</td><td></td></tr><tr><td></td><td></td><td>±500</td><td></td></tr><tr><td></td><td></td><td>±1000</td><td></td></tr><tr><td></td><td></td><td>±2000</td><td></td></tr><tr><td></td><td></td><td>±4000</td><td></td></tr><tr><td rowspan="4">LA_So</td><td rowspan="4">Linear acceleration sensitivity</td><td>FS = ±2 g</td><td></td><td>0.061</td><td></td><td rowspan="4">mg/LSB</td></tr><tr><td>FS = ±4 g</td><td></td><td>0.122</td><td></td></tr><tr><td>FS = ±8 g</td><td></td><td>0.244</td><td></td></tr><tr><td>FS = ±16 g</td><td></td><td>0.488</td><td></td></tr><tr><td rowspan="6">G_So</td><td rowspan="6"><eq>Angular\ rate\ sensitivity^{(2)}</eq></td><td>FS = ±125 dps</td><td></td><td>4.375</td><td></td><td rowspan="6">mdps/LSB</td></tr><tr><td>FS = ±250 dps</td><td></td><td>8.75</td><td></td></tr><tr><td>FS = ±500 dps</td><td></td><td>17.50</td><td></td></tr><tr><td>FS = ±1000 dps</td><td></td><td>35</td><td></td></tr><tr><td>FS = ±2000 dps</td><td></td><td>70</td><td></td></tr><tr><td>FS = ±4000 dps</td><td></td><td>140</td><td></td></tr><tr><td>G_So%</td><td><eq>Sensitivity\ tolerance^{(2)}</eq></td><td>at component level</td><td></td><td>±0.3</td><td></td><td>%</td></tr><tr><td>LA_SoDr</td><td>Linear acceleration sensitivity change vs. <eq>temperature^{(3)}</eq></td><td>from -40° to +85°</td><td></td><td>±0.01</td><td></td><td>%/°C</td></tr><tr><td>G_SoDr</td><td>Angular rate sensitivity change vs. <eq>temperature^{(3)}</eq></td><td>from -40° to +85°</td><td></td><td>±0.007</td><td></td><td>%/°C</td></tr><tr><td>LA_TyOff</td><td>Linear acceleration zero-g level offset <eq>accuracy^{(4)}</eq></td><td></td><td></td><td>±12</td><td></td><td>mg</td></tr><tr><td>G_TyOff</td><td>Angular rate zero-rate <eq>level^{(4)}</eq></td><td></td><td></td><td>±1</td><td></td><td>dps</td></tr><tr><td>LA_OffDr</td><td>Linear acceleration zero-g level change vs. <eq>temperature^{(3)}</eq></td><td></td><td></td><td>±0.07</td><td></td><td>mg/°C</td></tr><tr><td>G_OffDr</td><td>Angular rate typical zero-rate level change vs. <eq>temperature^{(3)}</eq></td><td></td><td></td><td>±0.006</td><td></td><td>dps/°C</td></tr><tr><td>Rn</td><td>Rate noise density in high-performance <eq>mode^{(5)}</eq></td><td></td><td></td><td>2.8</td><td></td><td>mdps/<eq>\sqrt{Hz}</eq></td></tr><tr><td>RnRMS</td><td>Gyroscope RMS noise in low-power <eq>mode^{(6)}</eq></td><td></td><td></td><td>60</td><td></td><td>mdps RMS</td></tr><tr><td rowspan="2">An</td><td>Acceleration noise density in high-performance <eq>mode^{(7)}</eq></td><td>FS = ±2 g - ±16 g</td><td></td><td>60</td><td></td><td rowspan="2">μg/<eq>\sqrt{Hz}</eq></td></tr><tr><td>Acceleration noise density in normal <eq>mode^{(8)(9)}</eq></td><td>FS = ±2 g - ±16 g</td><td></td><td>100</td><td></td></tr><tr><td rowspan="3">RMS</td><td rowspan="3">Accelerometer RMS noise in low-power mode</td><td>LPM1</td><td></td><td>2.3</td><td></td><td rowspan="3">mg RMS</td></tr><tr><td>LPM2</td><td></td><td>1.8</td><td></td></tr><tr><td>LPM3</td><td></td><td>1.2<eq>1.875^{(10)}</eq></td><td></td></tr><tr><td rowspan="12">LA_ODR</td><td rowspan="12">Linear acceleration output data rate</td><td rowspan="12"></td><td rowspan="12"></td><td></td><td rowspan="12"></td><td rowspan="21">Hz</td></tr><tr><td>7.5</td></tr><tr><td>15</td></tr><tr><td>30</td></tr><tr><td>60</td></tr><tr><td>120</td></tr><tr><td>240</td></tr><tr><td>480</td></tr><tr><td>960</td></tr><tr><td>1.92 k</td></tr><tr><td>3.84 k</td></tr><tr><td>7.68 k</td></tr><tr><td rowspan="11">G_ODR</td><td rowspan="9">Angular rate output data rate</td><td rowspan="9"></td><td rowspan="9"></td><td>7.5</td><td rowspan="9"></td></tr><tr><td>15</td></tr><tr><td>30</td></tr><tr><td>60</td></tr><tr><td>120</td></tr><tr><td>240</td></tr><tr><td>480</td></tr><tr><td>960</td></tr><tr><td>1.92 k</td></tr><tr><td rowspan="2">HAODR</td><td rowspan="2">ODR variation over temperature and supply range in high-accuracy <eq>mode^{(11)}</eq></td><td>Gyro on</td><td></td><td>±1</td><td rowspan="2">%</td></tr><tr><td>Gyro off</td><td></td><td>±3</td></tr><tr><td rowspan="3">Vst</td><td colspan="2">Linear acceleration self-test output change<eq>^{(12)(13)(14)}</eq></td><td></td><td>50</td><td>1700</td><td>mg</td></tr><tr><td colspan="2" rowspan="2">Angular rate self-test output change<eq>^{(15)(16)}</eq></td><td>FS = ±250 dps</td><td>20</td><td>80</td><td>dps</td></tr><tr><td>FS = ±2000 dps</td><td>150</td><td>700</td><td>dps</td></tr><tr><td>Top</td><td colspan="2">Operating temperature range</td><td></td><td>-40</td><td>+85</td><td>°C</td></tr></table>


1. Typical specifications are not guaranteed. 



2. Sensitivity tolerance for FS up to ±2000 dps. 



3. Measurements are performed in a uniform temperature setup and they are based on characterization data in a limited number of samples Not measured during final test for production. 



4. Value after calibration. 



5. Gyroscope rate noise density in high-performance mode is independent of the ODR and FS setting up to ±2000 dps. 



6. Gyroscope RMS noise in low-power mode is independent of the ODR and FS setting up to ±2000 dps. 



7. Accelerometer noise density in high-performance mode is independent of the selected ODR and FS. Valid when XL_DualC_EN = 0 in register CTRL8 (17h) . 



8. Accelerometer noise density in normal mode is independent of the ODR and FS setting. Valid when XL_DualC_EN = 0 in register CTRL8 (17h). 



9. Noise RMS related to BW = ODR/2. 



10. This ODR is available when the accelerometer is in low-power mode. 



11. Values specified by design. 



12. The sign of the linear acceleration self-test output change is defined by the ST_XL_[1:0] bits in a dedicated register for all axes. 



13. The linear acceleration self-test output change is defined with the device in stationary condition as the absolute value of: OUTPUT[LSb] (self-test enabled) - OUTPUT[LSb] (self-test disabled). 1LSb = 0.061 mg at ±2 g full scale. 



14. Accelerometer self-test limits are full-scale independent. 


15. The sign of the angular rate self-test output change is defined by the ST_G_[1:0] bits in a dedicated register for all axes. 

16. The angular rate self-test output change is defined with the device in stationary condition as the absolute value of: OUTPUT[LSb] (self-test enabled) - OUTPUT[LSb] (self-test disabled). 1LSb = 70 mdps at ±2000 dps full scale. 

## 4.2 Electrical characteristics

@ ${ \mathsf { V d d } } = 1 . 8 { \mathsf { V } } , { \mathsf { T } } = 2 5 ^ { \circ } { \mathsf { C } } ,$ unless otherwise noted. 


Table 4. Electrical characteristics


<table><tr><td>Symbol</td><td>Parameter</td><td>Test conditions</td><td>Min.</td><td><eq>Typ.^{(1)}</eq></td><td>Max.</td><td>Unit</td></tr><tr><td>Vdd</td><td>Supply voltage</td><td></td><td>1.71</td><td>1.8</td><td>3.6</td><td>V</td></tr><tr><td>Vdd_IO</td><td>Power supply for I/O</td><td></td><td>1.08</td><td></td><td>3.6</td><td>V</td></tr><tr><td>IddHP</td><td>Gyroscope and accelerometer current consumption in high-performance mode</td><td></td><td></td><td>0.65</td><td></td><td>mA</td></tr><tr><td>LA_IddHP</td><td>Accelerometer current consumption in high-performance mode</td><td></td><td></td><td>190</td><td></td><td>μA</td></tr><tr><td>LA_IddNM</td><td>Accelerometer current consumption in normal mode</td><td></td><td></td><td>100</td><td></td><td>μA</td></tr><tr><td>LA_IddLPM2</td><td>Accelerometer current consumption in low-power mode (LPM2)</td><td>ODR = 60 HzODR = 1.875 Hz</td><td></td><td>204.2</td><td></td><td>μA</td></tr><tr><td>LA_IddLPM1</td><td>Accelerometer current consumption in low-power mode (LPM1)</td><td>ODR = 60 HzODR = 1.875 Hz</td><td></td><td>174.0</td><td></td><td>μA</td></tr><tr><td>IddPD</td><td>Gyroscope and accelerometer current consumption during power-down</td><td></td><td></td><td>2.6</td><td></td><td>μA</td></tr><tr><td>Ton</td><td>Turn-on time - gyroscope</td><td></td><td></td><td>30</td><td></td><td>ms</td></tr><tr><td><eq>V_{IH}</eq></td><td>Digital high-level input voltage</td><td></td><td>0.7 * Vdd_IO</td><td></td><td></td><td>V</td></tr><tr><td><eq>V_{IL}</eq></td><td>Digital low-level input voltage</td><td></td><td></td><td></td><td>0.3 * Vdd_IO</td><td>V</td></tr><tr><td><eq>V_{OH}</eq></td><td>High-level output voltage</td><td><eq>I_{OH} = 4 mA^{(2)}</eq></td><td>Vdd_IO- 0.2</td><td></td><td></td><td>V</td></tr><tr><td><eq>V_{OL}</eq></td><td>Low-level output voltage</td><td><eq>I_{OL} = 4 mA^{(2)}</eq></td><td></td><td></td><td>0.2</td><td>V</td></tr><tr><td>Top</td><td>Operating temperature range</td><td></td><td>-40</td><td></td><td>+85</td><td>°C</td></tr></table>


1. Typical specifications are not guaranteed. 



2. 4 mA is the maximum driving capability, that is, the maximum DC current that can be sourced/sunk by the digital pin in order to guarantee the correct digital output voltage levels V and $V _ { O L }$ 



Table 5. Electrical parameters of Qvar (@Vdd = 1.8 V, T = 25 °C)


<table><tr><td>Parameter</td><td><eq>Typ.^{(1)}</eq></td><td>Unit</td></tr><tr><td>Power consumption</td><td><eq>15^{(2)}</eq></td><td>μA</td></tr><tr><td>Offset (shorted inputs)</td><td>3</td><td>mV</td></tr><tr><td>Noise (shorted inputs)</td><td>54</td><td>μV</td></tr><tr><td>Qvar gain</td><td>78</td><td>LSB/mV</td></tr><tr><td>CMRR</td><td>54</td><td>dB</td></tr><tr><td>Input impedance</td><td>Configurable (from 235 M to 2.4 G)</td><td>Ω</td></tr><tr><td>Input range</td><td>±460</td><td>mV</td></tr></table>


1. Vdd_IO = 1.8 V, Zin = 235 MOhm. Typical values are based on characterization and are not guaranteed. 



2. Extra power consumption when only the analog hub / Qvar function is enabled. In this condition the accelerometer must be set to high-performance mode or normal mode. 


## 4.3 Temperature sensor characteristics

@ Vdd = 1.8 V, ${ \mathsf { T } } = 2 5 { \mathsf { \Omega } } ^ { \circ } { \mathsf { C } }$ unless otherwise noted. 


Table 6. Temperature sensor characteristics


<table><tr><td>Symbol</td><td>Parameter</td><td>Test condition</td><td>Min.</td><td><eq>Typ.^{(1)}</eq></td><td>Max.</td><td>Unit</td></tr><tr><td><eq>TODR^{(2)}</eq></td><td>Temperature refresh rate</td><td></td><td></td><td>60</td><td></td><td>Hz</td></tr><tr><td>Toff</td><td><eq>Temperature\ offset^{(3)}</eq></td><td></td><td>-15</td><td></td><td>+15</td><td>°C</td></tr><tr><td>TSen</td><td>Temperature sensitivity</td><td></td><td></td><td>256</td><td></td><td>LSB/°C</td></tr><tr><td>TST</td><td>Temperature stabilization <eq>time^{(4)}</eq></td><td></td><td></td><td></td><td>500</td><td>μs</td></tr><tr><td>T_ADC_res</td><td>Temperature ADC resolution</td><td></td><td></td><td>16</td><td></td><td>bit</td></tr><tr><td>Top</td><td>Operating temperature range</td><td></td><td>-40</td><td></td><td>+85</td><td>°C</td></tr></table>


1. Typical specifications are not guaranteed 



2. When the accelerometer is in low-power mode and the gyroscope part is turned off, the TODR value is equal to the accelerometer ODR. 



3. The output of the temperature sensor is 0 LSB (typ.) at $2 5 ^ { \circ } C .$ 


4. Time from power ON to valid data based on characterization data. 

## 4.4

## Communication interface characteristics

## 4.4.1

## SPI - serial peripheral interface

Subject to general operating conditions for Vdd and Top. @ Vdd_ $\mathsf { I O } = 1 . 8 \mathsf { V } , \mathsf { T } = 2 5 ^ { \circ } \mathsf { C }$ unless otherwise noted. 


Table 7. SPI slave timing values


<table><tr><td rowspan="2">Symbol</td><td rowspan="2">Parameter</td><td colspan="3">Value(1)</td><td rowspan="2">Unit</td></tr><tr><td>Min</td><td>Typ</td><td>Max</td></tr><tr><td><eq>f_{c(SPC)}</eq></td><td>SPI clock frequency</td><td></td><td></td><td>10</td><td>MHz</td></tr><tr><td><eq>t_{c(SPC)}</eq></td><td>SPI clock period</td><td>100</td><td></td><td></td><td rowspan="11">ns</td></tr><tr><td><eq>t_{high(SPC)}</eq></td><td>SPI clock high</td><td>45</td><td></td><td></td></tr><tr><td><eq>t_{low(SPC)}</eq></td><td>SPI clock low</td><td>45</td><td></td><td></td></tr><tr><td rowspan="2"><eq>t_{su(CS)}</eq></td><td>CS setup time (mode 3)</td><td>5</td><td></td><td></td></tr><tr><td>CS setup time (mode 0)</td><td>20</td><td></td><td></td></tr><tr><td rowspan="2"><eq>t_{h(CS)}</eq></td><td>CS hold time (mode 3)</td><td>20</td><td></td><td></td></tr><tr><td>CS hold time (mode 0)</td><td>20</td><td></td><td></td></tr><tr><td><eq>t_{su(SI)}</eq></td><td>SDI input setup time</td><td>5</td><td></td><td></td></tr><tr><td><eq>t_{h(SI)}</eq></td><td>SDI input hold time</td><td>15</td><td></td><td></td></tr><tr><td><eq>t_{v(SO)}</eq></td><td>SDO valid output time</td><td></td><td>15</td><td>25</td></tr><tr><td><eq>t_{dis(SO)}</eq></td><td>SDO output disable time</td><td></td><td></td><td>50</td></tr><tr><td><eq>C_{load}</eq></td><td>Bus capacitance</td><td></td><td></td><td>100</td><td>pF</td></tr></table>


1. Values are evaluated at 10 MHz clock frequency for SPI with both 4 and 3 wires, based on characterization results, not tested in production 



Figure 7. SPI slave timing in mode 0


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/9478011c56a5085b28c8d0bc15424dc8e81e6cc741f11a53c54bd7fa4c2dbf9e.jpg)



Measurement points are done at 0.3·Vdd_IO and 0.7·Vdd_IO for both input and output ports.



Figure 8. SPI slave timing in mode 3


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/f8e8cd827ad165f168b0c131bb598d3a7dac7040f357c5398cfa7fb5c0bb525e.jpg)


## 4.4.2

## I²C - inter-IC control interface

Subject to general operating conditions for Vdd and Top. 


Table 8. I²C slave timing values


<table><tr><td rowspan="2">Symbol</td><td rowspan="2">Parameter</td><td colspan="2"><eq>I^{2}C fast mode^{(1)(2)}</eq></td><td colspan="2"><eq>I^{2}C fast mode plus^{(1)(2)}</eq></td><td rowspan="2">Unit</td></tr><tr><td>Min</td><td>Max</td><td>Min</td><td>Max</td></tr><tr><td><eq>f_{(SCL)}</eq></td><td>SCL clock frequency</td><td>0</td><td>400</td><td>0</td><td>1000</td><td>kHz</td></tr><tr><td><eq>t_{w(SCLL)}</eq></td><td>SCL clock low time</td><td>1.3</td><td></td><td>0.5</td><td></td><td rowspan="2">μs</td></tr><tr><td><eq>t_{w(SCLH)}</eq></td><td>SCL clock high time</td><td>0.6</td><td></td><td>0.26</td><td></td></tr><tr><td><eq>t_{su(SDA)}</eq></td><td>SDA setup time</td><td>100</td><td></td><td>50</td><td></td><td>ns</td></tr><tr><td><eq>t_{h(SDA)}</eq></td><td>SDA data hold time</td><td>0</td><td>0.9</td><td>0</td><td></td><td rowspan="7">μs</td></tr><tr><td><eq>t_{h(ST)}</eq></td><td>START/REPEATED START condition hold time</td><td>0.6</td><td></td><td>0.26</td><td></td></tr><tr><td><eq>t_{su(SR)}</eq></td><td>REPEATED START condition setup time</td><td>0.6</td><td></td><td>0.26</td><td></td></tr><tr><td><eq>t_{su(SP)}</eq></td><td>STOP condition setup time</td><td>0.6</td><td></td><td>0.26</td><td></td></tr><tr><td><eq>t_{w(SP:SR)}</eq></td><td>Bus free time between STOP and START condition</td><td>1.3</td><td></td><td>0.5</td><td></td></tr><tr><td></td><td>Data valid time</td><td></td><td>0.9</td><td></td><td>0.45</td></tr><tr><td></td><td>Data valid acknowledge time</td><td></td><td>0.9</td><td></td><td>0.45</td></tr><tr><td><eq>C_B</eq></td><td>Capacitive load for each bus line</td><td></td><td>400</td><td></td><td>550</td><td>pF</td></tr></table>


1. Data based on standard I²C protocol requirement, not tested in production. 



2. Data for I²C fast mode and I²C fast mode plus have been validated by characterization, not tested in production. 



Figure 9. I²C slave timing diagram


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/f811df886f4a2d226e7e5dcc74a16bedf0516345011d71809453473709db3137.jpg)



Note: Measurement points are done at 0.3·Vdd_IO and 0.7·Vdd_IO for both ports.


## 4.5

## Absolute maximum ratings

Stresses above those listed as “absolute maximum ratings” may cause permanent damage to the device. This is a stress rating only and functional operation of the device under these conditions is not implied. Exposure to maximum rating conditions for extended periods may affect device reliability. 


Table 9. Absolute maximum ratings


<table><tr><td>Symbol</td><td>Ratings</td><td>Maximum value</td><td>Unit</td></tr><tr><td>Vdd</td><td>Supply voltage</td><td>-0.3 to 4.8</td><td>V</td></tr><tr><td><eq>T_{STG}</eq></td><td>Storage temperature range</td><td>-40 to +125</td><td>°C</td></tr><tr><td>Sg</td><td>Acceleration g for 0.2 ms</td><td>20,000</td><td>g</td></tr><tr><td>ESD</td><td>Electrostatic discharge protection (HBM)</td><td>2</td><td>kV</td></tr><tr><td>Vin</td><td>Input voltage on any control pin(including CS, SCL/SPC, SDA/SDI/SDO, SDO/SA0)</td><td>-0.3 to Vdd_IO +0.3</td><td>V</td></tr></table>

Supply voltage on any pin should never exceed 4.8 V. 

![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/f727e76d690dc621bb0e518c9734ad4fbf9fc95f4a022eda0c26930d9dc251ec.jpg)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/7de30d88eb395b0bc8496415a971cc9fd8f08cafa318dacc66c6e0c9af0d8644.jpg)


This device is sensitive to mechanical shock, improper handling can cause permanent damage to the part. 

This device is sensitive to electrostatic discharge (ESD), improper handling can cause permanent damage to the part 

## 4.6

## Terminology

## 4.6.1 Sensitivity

Linear acceleration sensitivity can be determined, for example, by applying 1 g acceleration to the device. Because the sensor can measure DC accelerations, this can be done easily by pointing the selected axis towards the ground, noting the output value, rotating the sensor 180 degrees (pointing towards the sky) and noting the output value again. By doing so, ±1 g acceleration is applied to the sensor. Subtracting the larger output value from the smaller one, and dividing the result by 2, leads to the actual sensitivity of the sensor. This value changes very little over temperature and over time. The sensitivity tolerance describes the range of sensitivities of a large number of sensors (see Table 3). 

An angular rate gyroscope is a device that produces a positive-going digital output for counterclockwise rotation around the axis considered. Sensitivity describes the gain of the sensor and can be determined by applying a defined angular velocity to it. This value changes very little over temperature and time (see Table 3). 

## 4.6.2

## Zero-g and zero-rate level

Linear acceleration zero-g level offset (TyOff) describes the deviation of an actual output signal from the ideal output signal if no acceleration is present. A sensor in a steady state on a horizontal surface measures 0 g on both the X-axis and Y-axis, whereas the Z-axis measures 1 g. Ideally, the output is in the middle of the dynamic range of the sensor (content of OUT registers 00h, data expressed as two's complement number). A deviation from the ideal value in this case is called zero-g offset. 

Offset is to some extent a result of stress to the MEMS sensor and therefore the offset can slightly change after mounting the sensor onto a printed circuit board or exposing it to extensive mechanical stress. Offset changes little over temperature, see “Linear acceleration zero-g level change vs. temperature” in Table 3. The zero-g level tolerance (TyOff) describes the standard deviation of the range of zero-g levels of a group of sensors. 

Zero-rate level describes the actual output signal if there is no angular rate present. The zero-rate level of precise MEMS sensors is, to some extent, a result of stress to the sensor and therefore the zero-rate level can slightly change after mounting the sensor onto a printed circuit board or after exposing it to extensive mechanical stress. This value changes very little over temperature and time (see Table 3). 

## Digital interfaces

## 5.1 I²C/SPI interface

The registers embedded inside the LSM6DSV16X may be accessed through both the I²C and SPI serial interfaces. The latter may be software configured to operate either in 3-wire or 4-wire interface mode. The device is compatible with SPI modes 0 and 3. 

The serial interfaces are mapped to the same pins. To select/exploit the I²C interface, the CS line must be tied high (that is, connected to Vdd_IO). 


Table 10. Serial interface pin description


<table><tr><td>Pin name</td><td>Pin description</td></tr><tr><td>CS</td><td>Enables SPI<eq>I^{2}C/SPI</eq> mode selection(1: SPI idle mode / <eq>I^{2}C</eq> communication enabled;0: SPI communication mode / <eq>I^{2}C</eq> disabled)</td></tr><tr><td>SCL/SPC</td><td><eq>I^{2}C</eq> serial clock (SCL)SPI serial port clock (SPC)</td></tr><tr><td>SDA/SDI/SDO</td><td><eq>I^{2}C</eq> serial data (SDA)SPI serial data input (SDI)3-wire interface serial data output (SDO)</td></tr><tr><td>SDO/SA0</td><td>SPI serial data output (SDO)<eq>I^{2}C</eq> less significant bit of the device address</td></tr></table>

## 5.1.1 I²C serial interface

The LSM6DSV16X I²C is a bus slave. The I²C is employed to write the data to the registers, whose content can also be read back. 

The relevant I²C terminology is provided in the table below. 


Table 11. I²C terminology


<table><tr><td>Term</td><td>Description</td></tr><tr><td>Transmitter</td><td>The device that sends data to the bus</td></tr><tr><td>Receiver</td><td>The device that receives data from the bus</td></tr><tr><td>Master</td><td>The device that initiates a transfer, generates clock signals, and terminates a transfer</td></tr><tr><td>Slave</td><td>The device addressed by the master</td></tr></table>

There are two signals associated with the I²C bus: the serial clock line (SCL) and the serial data line (SDA). The latter is a bidirectional line used for sending and receiving the data to/from the interface. Both the lines must be connected to Vdd_IO through external pull-up resistors. When the bus is free, both the lines are high. The I²C interface is implemented with fast mode (400 kHz) I²C standards as well as with fast mode plus (1000 kHz). 

In order to disable the I²C block, I2C_I3C_disable = 1 must be written in IF_CFG (03h). 

## 5.1.2 I²C operation

The transaction on the bus is started through a start (ST) signal. A start condition is defined as a high to low transition on the data line while the SCL line is held high. After this has been transmitted by the master, the bus is considered busy. The next byte of data transmitted after the start condition contains the address of the slave in the first 7 bits and the eighth bit tells whether the master is receiving data from the slave or transmitting data to the slave. When an address is sent, each device in the system compares the first seven bits after a start condition with its address. If they match, the device considers itself addressed by the master. 

The slave address (SAD) associated to the LSM6DSV16X is 110101xb. The SDO/SA0 pin can be used to modify the less significant bit of the device address. If the SDO/SA0 pin is connected to the supply voltage, LSb is 1 (address 1101011b); else if the SDO/SA0 pin is connected to ground, the LSb value is 0 (address 1101010b). This solution permits to connect and address two different inertial modules to the same I²C bus 

Data transfer with acknowledge is mandatory. The transmitter must release the SDA line during the acknowledge pulse. The receiver must then pull the data line low so that it remains stable low during the high period of the acknowledge clock pulse. A receiver that has been addressed is obliged to generate an acknowledge after each byte of data received. 

The I²C embedded inside the LSM6DSV16X behaves like a slave device and the following protocol must be adhered to. After the start condition (ST) a slave address is sent, once a slave acknowledge (SAK) has been returned, an 8-bit subaddress (SUB) is transmitted. The increment of the address is configured by the CTRL3 (12h) (IF_INC). 

The slave address is completed with a read/write bit. If the bit is 1 (read), a repeated start (SR) condition must be issued after the two subaddress bytes; if the bit is 0 (write) the master transmits to the slave with direction unchanged. Table 12 explains how the SAD+read/write bit pattern is composed, listing all the possible configurations. 


Table 12. SAD+read/write patterns


<table><tr><td>Command</td><td>SAD[6:1]</td><td>SAD[0] = SA0</td><td>R/W</td><td>SAD+R/W</td></tr><tr><td>Read</td><td>110101</td><td>0</td><td>1</td><td>11010101 (D5h)</td></tr><tr><td>Write</td><td>110101</td><td>0</td><td>0</td><td>11010100 (D4h)</td></tr><tr><td>Read</td><td>110101</td><td>1</td><td>1</td><td>11010111 (D7h)</td></tr><tr><td>Write</td><td>110101</td><td>1</td><td>0</td><td>11010110 (D6h)</td></tr></table>


Table 13. Transfer when master is writing one byte to slave


<table><tr><td>Master</td><td>ST</td><td>SAD + W</td><td></td><td>SUB</td><td></td><td>DATA</td><td></td><td>SP</td></tr><tr><td>Slave</td><td></td><td></td><td>SAK</td><td></td><td>SAK</td><td></td><td>SAK</td><td></td></tr></table>


Table 14. Transfer when master is writing multiple bytes to slave


<table><tr><td>Master</td><td>ST</td><td>SAD + W</td><td></td><td>SUB</td><td></td><td>DATA</td><td></td><td>DATA</td><td></td><td>SP</td></tr><tr><td>Slave</td><td></td><td></td><td>SAK</td><td></td><td>SAK</td><td></td><td>SAK</td><td></td><td>SAK</td><td></td></tr></table>


Table 15. Transfer when master is receiving (reading) one byte of data from slave


<table><tr><td>Master</td><td>ST</td><td>SAD + W</td><td></td><td>SUB</td><td></td><td>SR</td><td>SAD + R</td><td></td><td></td><td>NMAK</td><td>SP</td></tr><tr><td>Slave</td><td></td><td></td><td>SAK</td><td></td><td>SAK</td><td></td><td></td><td>SAK</td><td>DATA</td><td></td><td></td></tr></table>


Table 16. Transfer when master is receiving (reading) multiple bytes of data from slave


<table><tr><td>Master</td><td>ST</td><td>SAD+W</td><td></td><td>SUB</td><td></td><td>SR</td><td>SAD+R</td><td></td><td></td><td>MAK</td><td></td><td>MAK</td><td></td><td>NMAK</td><td>SP</td></tr><tr><td>Slave</td><td></td><td></td><td>SAK</td><td></td><td>SAK</td><td></td><td></td><td>SAK</td><td>DATA</td><td></td><td>DATA</td><td></td><td>DATA</td><td></td><td></td></tr></table>

Data are transmitted in byte format (DATA). Each data transfer contains 8 bits. The number of bytes transferred per transfer is unlimited. Data is transferred with the most significant bit (MSb) first. If a slave receiver does not acknowledge the slave address (that is, it is not able to receive because it is performing some real-time function) the data line must be left high by the slave. The master can then abort the transfer. A low to high transition on the SDA line while the SCL line is high is defined as a stop condition. Each data transfer must be terminated by the generation of a stop (SP) condition. 

In the presented communication format, MAK is master acknowledge and NMAK is no master acknowledge. 

## 5.1.3

## SPI bus interface

The SPI on the LSM6DSV16X is a bus slave which allows writing and reading the registers of the device. 


Figure 10. Read and write protocol (in mode 3)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/8246cb68a336c395254f980fab0741582563abdaddd3b164773ae4c74733b3ff.jpg)


CS enables the serial port and it is controlled by the SPI master. It goes low at the start of the transmission and goes back high at the end. SPC is the serial port clock and it is controlled by the SPI master. It is stopped high when CS is high (no transmission). SDI and SDO are, respectively, the serial port data input and output. Those lines are driven at the falling edge of SPC and should be captured at the rising edge of SPC. 

Both the read register and write register commands are completed in 16 clock pulses or in multiples of 8 in case of multiple read/write bytes. Bit duration is the time between two falling edges of SPC. The first bit (bit 0) starts at the first falling edge of SPC after the falling edge of CS while the last bit (bit 15, bit 23, ...) starts at the last falling edge of SPC just before the rising edge of CS. 

bit 0: RW bit. When 0, the data DI(7:0) is written into the device. When 1, the data DO(7:0) from the device is read. In latter case, the chip drives SDO at the start of bit 8. 

bit 1-7: address AD(6:0). This is the address field of the indexed register. 

bit 8-15: data DI(7:0) (write mode). This is the data that is written into the device (MSb first). 

bit 8-15: data DO(7:0) (read mode). This is the data that is read from the device (MSb first). 

In multiple read/write commands further blocks of 8 clock periods are added. When the CTRL3 (12h) (IF_INC) bit is 0, the address used to read/write data remains the same for every block. When the CTRL3 (12h) (IF_INC) bit is 1, the address used to read/write data is increased at every block. 

The function and the behavior of SDI and SDO remain unchanged. 


Figure 11. SPI read protocol (in mode 3)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/c864ce2aacbfc3eb0bf3ad9757d94a369a3c7f00313ffa2ff2e19b91fa053aa8.jpg)


The SPI read command is performed with 16 clock pulses. A multiple byte read command is performed by adding blocks of 8 clock pulses to the previous one. 

bit 0: READ bit. The value is 1. 

bit 1-7: address AD(6:0). This is the address field of the indexed register. 

bit 8-15: data DO(7:0) (read mode). This is the data that is read from the device (MSb first). 

bit 16-...: data DO(...-8). Further data in multiple byte reads. 


Figure 12. Multiple byte SPI read protocol (2-byte example) (in mode 3)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/2e6124c50be502c37c5da2baa0069bd61d3086614bd49a5ecdfd12ca56e4bc87.jpg)


## 5.1.3.2 SPI write


Figure 13. SPI write protocol (in mode 3)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/f13ec1ea8f02cbc0c7c5cf4e7ad8a0982cbf05381ef89e46d6a3205ae5f2f800.jpg)


The SPI write command is performed with 16 clock pulses. A multiple byte write command is performed by adding blocks of 8 clock pulses to the previous one. 

bit 0: WRITE bit. The value is 0. 

bit 1 -7: address AD(6:0). This is the address field of the indexed register. 

bit 8-15: data DI(7:0) (write mode). This is the data that is written inside the device (MSb first). 

bit 16-... : data DI(...-8). Further data in multiple byte writes. 


Figure 14. Multiple byte SPI write protocol (2-byte example) (in mode 3)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/fd3e94ad088ba6ee9773a50d4aa439d9c5e94991754ba40cbfc5ea28bf426c3e.jpg)


## 5.1.3.3 SPI read in 3-wire mode

3-wire mode is entered by setting the IF_CFG (03h) (SIM) bit equal to 1 (SPI serial interface mode selection). 


Figure 15. SPI read protocol in 3-wire mode (in mode 3)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/65b0783c87646c97c461f64443d4b4f4496cac9cb63041776dcde536bf64f430.jpg)


The SPI read command is performed with 16 clock pulses: 

bit 0: READ bit. The value is 1. 

bit 1-7: address AD(6:0). This is the address field of the indexed register. 

bit 8-15: data DO(7:0) (read mode). This is the data that is read from the device (MSb first). 

A multiple read command is also available in 3-wire mode. 

## 5.2

## MIPI ${ \mathsf { I } } 3 { \mathsf { C } } ^ { \otimes }$ interface

## 5.2.1

## MIPI $\mathsf { I } 3 \mathsf { C } ^ { \otimes }$ slave interface

The LSM6DSV16X interface includes an MIPI I3C<sup>®</sup> SDR only slave interface (compliant with release 1.1 of the specification) with MIPI ${ \mathsf { I } } 3 { \mathsf { C } } ^ { \circledast }$ SDR embedded features: 

CCC command 

Direct CCC communication (SET and GET) 

Broadcast CCC communication 

Private communications 

Private read and write for single byte 

Multiple read and write 

In-band interrupt request 

Slave reset pattern 

Group address 

Full range Vdd_IO support 

Asynchronous modes 0 and 1 

Synchronous mode 

Error detection and recovery methods (S0-S6) 

In order to disable the MIPI ${ \mathsf { I } } 3 { \mathsf { C } } ^ { \circledast }$ block, I2C_I3C_disable = 1 must be written in $| | F \_ C | ^ { \mathsf { T } } \mathsf { G }$ (03h). 

## 5.2.2

## MIPI $\mathsf { I } 3 \mathsf { C } ^ { \otimes }$ CCC supported commands

The list of MIPI ${ \mathsf { I } } 3 \mathsf { C } ^ { \circledast }$ CCC commands supported by the device is detailed in the following table. 


Table 17. MIPI $\mathsf { I } 3 \mathsf { C } ^ { \otimes }$ CCC commands


<table><tr><td>Command</td><td>Command code</td><td>Default</td><td>Description</td></tr><tr><td>ENTDAA</td><td>0x07</td><td></td><td>DAA procedure</td></tr><tr><td>SETDASA</td><td>0x87</td><td></td><td>Assign dynamic address using static address 0x6B/0x6A depending on SDO pin</td></tr><tr><td>ENEC</td><td>0x80 / 0x00</td><td></td><td>Slave activity control (direct and broadcast)</td></tr><tr><td>DISEC</td><td>0x81/ 0x01</td><td></td><td>Slave activity control (direct and broadcast)</td></tr><tr><td>ENTAS0</td><td>0x82 / 0x02</td><td></td><td>Enter activity state (direct and broadcast)</td></tr><tr><td>SETXTIME</td><td>0x98 / 0x28</td><td></td><td>Timing information exchange</td></tr><tr><td>GETXTIME</td><td>0x99</td><td>0x070x000x050x92</td><td>Timing information exchange</td></tr><tr><td>RSTDAA</td><td>0x06</td><td></td><td>Reset the assigned dynamic address (broadcast only)</td></tr><tr><td>SETMWL</td><td>0x89 / 0x08</td><td></td><td>Define maximum write length during private write (direct and broadcast)</td></tr><tr><td>SETMRL</td><td>0x8A / 0x09</td><td></td><td>Define maximum read length during private read (direct and broadcast)</td></tr><tr><td>SETNEWDA</td><td>0x88</td><td></td><td>Change dynamic address</td></tr><tr><td>GETMWL</td><td>0x8B</td><td>0x000x08(2 byte)</td><td>Get maximum write length during private write</td></tr><tr><td>GETMRL</td><td>0x8C</td><td>0x000x100x09(3 byte)</td><td>Get maximum read length during private read</td></tr><tr><td rowspan="2">GETPID</td><td rowspan="2">0x8D</td><td>0x020x080x000x700x920x0B</td><td>SDO = 1</td></tr><tr><td>0x020x080x000x700x120x0B</td><td>SDO = 0</td></tr><tr><td>GETBCR</td><td>0x8E</td><td>0x07(1 byte)</td><td>Bus characteristics register</td></tr><tr><td>GETDCR</td><td>0x8F</td><td>0x44 default</td><td>MIPI I3C® device characteristics register</td></tr><tr><td>GETSTATUS</td><td>0x90</td><td>0x000x00(2 byte)</td><td>Status register</td></tr><tr><td>GETMXDS</td><td>0x94</td><td>0x080x60</td><td>Return max write and read speed</td></tr><tr><td>GETCAPS</td><td>0x95</td><td>0x000x110x180x00</td><td>Provide information about device capabilities and supported extended features</td></tr><tr><td>SETGRPA</td><td>0x9B</td><td></td><td>Group address assignment command</td></tr><tr><td>RSTGRPA</td><td>0x2C / 0x9C</td><td></td><td>Reset the group address</td></tr><tr><td>RSTACT</td><td>0x9A / 0x2A</td><td></td><td>Configure slave reset action</td></tr></table>

## 5.2.3 Overview of anti-spike filter management

The device acts as a standard I²C target as long as it has an I²C static address. The device is capable of detecting and disabling the I²C anti-spike filter after detecting the broadcast address (7'h7E/W). In order to guarantee proper behavior of the device, the I3C master must emit the first START, 7'h7E/W at open-drain speed using I²C fast mode plus reference timing. 

After detecting the broadcast address, the device can receive the I3C dynamic address following the I3C pushpull timing. If the device is not assigned a dynamic address, then the device continues to operate as an I²C device with no anti-spike filter. For the case in which the host decides to keep the device as I²C with anti-spike filter, there is a configuration required to keep the anti-spike filter active. This configuration is done by writing the ASF_CTRL bit to 1 in the IF_CFG (03h) register. This configuration forces the anti-spike filter to always be turned on instead of being managed by the communication on the bus. 

## Master I²C interface

If the LSM6DSV16X is configured in mode 2, a master I²C line is available. The master serial interface is mapped to the following dedicated pins. 


Table 18. Master I²C pin details


<table><tr><td>Pin name</td><td>Pin description</td></tr><tr><td>MSCL</td><td>I2C serial clock master</td></tr><tr><td>MSDA</td><td>I2C serial data master</td></tr><tr><td>MDRDY</td><td>I2C master external synchronization signal</td></tr></table>

## Auxiliary SPI interface

If the LSM6DSV16X is configured in mode 3, the auxiliary SPI is available. The auxiliary SPI interface is mapped to the following dedicated pins. 


Table 19. Auxiliary SPI pin details


<table><tr><td>Pin name</td><td>Pin description</td></tr><tr><td>OCS_Aux</td><td>Enables auxiliary SPI 3/4-wire</td></tr><tr><td>SDx/AH1/Qvar1</td><td>Auxiliary SPI 3/4-wire data input (SDI_Aux) and SPI 3-wire data output (SDO_Aux)</td></tr><tr><td>SCx/AH2/Qvar2</td><td>Auxiliary SPI 3/4-wire interface serial port clock</td></tr><tr><td>SDO_Aux</td><td>Auxiliary SPI 4-wire data output (SDO_Aux)</td></tr></table>

When the LSM6DSV16X is configured in mode 3, the auxiliary SPI can be connected to a camera module for OIS support. 

## Functionality

This section describes all the operating modes and power modes of the LSM6DSV16X. 

## Note:

Refer to the product application note for the details regarding operating/power mode configurations, settings, turn-on/off time and on-the-fly changes. 

## 6.1 Operating modes

In the LSM6DSV16X, the accelerometer and the gyroscope can be turned on/off independently of each other and are allowed to have different ODRs and power modes. 

The LSM6DSV16X has three operating modes available: 

Only accelerometer active and gyroscope in power-down 

Only gyroscope active and accelerometer in power-down 

Both accelerometer and gyroscope sensors active with independent ODR and power mode 

The accelerometer is activated from power-down by writing ODR_XL_[3:0] in CTRL1 (10h) while the gyroscope is activated from power-down by writing ODR_G_[3:0] in CTRL2 (11h). For combo mode, the ODRs are totally independent. 

## 6.2 Accelerometer power modes

In the LSM6DSV16X, the accelerometer can be configured in five different operating modes: power-down mode, low-power mode (1, 2, 3), normal mode, high-performance mode and high-accuracy ODR mode. 

The operating mode selected depends on the value of the OP_MODE_XL_[2:0] bits in CTRL1 (10h). 

If the value of the OP_MODE_XL_[2:0] bits is 000 (default), high-performance mode is valid for all ODRs (from 7.5 Hz up to 7.68 kHz). 

Normal mode is available for ODR values from 7.5 Hz to 1.92 kHz and it is enabled by setting the OP_MODE_XL_[2:0] bits to 111. Normal mode cannot be used in mode 3 connection mode. 

In high-performance mode and in normal mode the analog anti-aliasing filter is active. 

Low-power mode is available for lower ODRs (1.875 Hz, 15 Hz, 30 Hz, 60 Hz, 120 Hz, 240 Hz). The three low-power modes are enabled by setting OP_MODE_XL_[2:0] to 100 (LPM1), 101 (LPM2), 110 (LPM3). 

High-accuracy ODR mode is available for ODR values from 15 Hz up to 7.68 kHz and it is enabled by setting the OP_MODE_XL_[2:0] bits to 001. Refer to Section 6.5 High-accuracy ODR mode for more details. 

The embedded functions based on accelerometer data (free-fall, 6D/4D, tap/double-tap, wake-up, activity/ inactivity, stationary/motion, step counter, step detection, significant motion, tilt) and the FIFO batching functionality are supported in all modes. 

## 6.3

## Accelerometer dual-channel mode

The LSM6DSV16X accelerometer block has a dual-channel architecture able to work with two different full scales simultaneously. By default, the device operates in single-channel mode supporting FS scale values from ±2 g through ±16 g and different power modes, as described in Section 6.2 Accelerometer power modes. The block diagrams in the following figures show the configuration of acceleration data processing in the two different modes. 


Figure 16. Single-channel mode (XL_DualC_EN = 0)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/49e8cdf1e7e702716d307b6dfcfcd0085fdfd6830921e0c9f0cd7a70164166a7.jpg)



Figure 17. Dual-channel mode (XL_DualC_EN = 1)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/2a6746160e87ef593e37c2f1227b80cd7108dabf86df6d91bf80591bd3a6ad5a.jpg)


## 6.4

## Gyroscope power modes

In the LSM6DSV16X, the gyroscope can be configured in five different operating modes: power-down mode, sleep mode, low-power mode, high-performance mode and high-accuracy ODR mode. 

The operating mode selected depends on the value of the OP_MODE_G_[2:0] bits in CTRL2 (11h). 

If the value of the OP_MODE_G_[2:0] bits is 000 (default), high-performance mode is valid for all ODRs (from 7.5 Hz up to 7.68 kHz). 

Low-power mode is available for lower ODRs (7.5 Hz, 15 Hz, 30 Hz, 60 Hz, 120 Hz, 240 Hz) and it is enabled by setting the the OP_MODE_G_[2:0] bits to 101. 

High-accuracy ODR mode is available for ODR values from 15 Hz up to 7.68 kHz and it is enabled by setting the OP_MODE_G_[2:0] bits to 001. Refer to Section 6.5 High-accuracy ODR mode for more details. 

## 6.5 High-accuracy ODR mode

High-accuracy ODR (HAODR) mode can be enabled to reduce the part-to-part output data rate variation. It supports accelerometer only, gyroscope only, and combo (accelerometer and gyroscope) modes. When this mode is used for one sensor (accelerometer or gyroscope), the other sensor also has to be configured in high-accuracy ODR (HAODR) mode. 

The main high-accuracy ODR features are: 

Noise level is aligned with high-performance mode 

Power consumption increase of 20 μA (typical) vs. the corresponding high-performance mode configuration selected 

The UI channel bandwidth can be selected through the gyroscope LPF1 and accelerometer HPF/LPF2 filters. 

When HAODR mode is enabled, it is applied to the UI accelerometer, UI gyroscope, EIS gyroscope, and temperature. It is not applied to OIS accelerometer/gyroscope channels. 

## Note:

HAODR mode has to be enabled / disabled when the device is in power-down mode. 

When HAODR mode is enabled, two different sets of ODRs are supported based on the configuration of the HAODR_SEL_[1:0] bitfield in the HAODR_CFG (62h) register, as shown in the table below. 

## Note:

High-accuracy ODR mode is not compatible with the analog hub / Qvar functionality and the activity/inactivity functionality (motion/stationary can be used). 


Table 20. Accelerometer and gyroscope ODR selection in high-accuracy ODR mode


<table><tr><td>ODR_XL_[3:0] ODR_G_[3:0]</td><td>ODR [Hz] HAODR_SEL_[1:0] = 00</td><td>ODR [Hz] HAODR_SEL_[1:0] = 01</td><td>ODR [Hz] HAODR_SEL_[1:0] = 10</td></tr><tr><td>0000</td><td>Power-down</td><td>Power-down</td><td>Power-down</td></tr><tr><td>0001</td><td>Reserved</td><td>Reserved</td><td>Reserved</td></tr><tr><td>0010</td><td>Reserved</td><td>Reserved</td><td>Reserved</td></tr><tr><td>0011</td><td>15</td><td>15.625</td><td>12.5</td></tr><tr><td>0100</td><td>30</td><td>31.25</td><td>25</td></tr><tr><td>0101</td><td>60</td><td>62.5</td><td>50</td></tr><tr><td>0110</td><td>120</td><td>125</td><td>100</td></tr><tr><td>0111</td><td>240</td><td>250</td><td>200</td></tr><tr><td>1000</td><td>480</td><td>500</td><td>400</td></tr><tr><td>1001</td><td>960</td><td>1000</td><td>800</td></tr><tr><td>1010</td><td>1920</td><td>2000</td><td>1600</td></tr><tr><td>1011</td><td>3840</td><td>4000</td><td>3200</td></tr><tr><td>1100</td><td>7680</td><td>8000</td><td>6400</td></tr><tr><td>Others</td><td>Reserved</td><td>Reserved</td><td>Reserved</td></tr></table>

## 6.6

## ODR-triggered mode

When ODR-triggered mode is enabled, a reference signal must be provided to the INT2 pin, and the device then automatically aligns (in frequency and phase) the data generation to the edges of the reference signal. 

It supports accelerometer only, gyroscope only, and combo (accelerometer and gyroscope) modes. When both the accelerometer and gyroscope are enabled, the user must configure the same ODR on both the accelerometer and gyroscope. It is not possible to select different ODRs for the accelerometer and gyroscope; if different output data rate values are set, the ODR configured for the gyroscope data is also applied to the accelerometer data. 

The full-scale configurations are totally independent between the accelerometer and gyroscope and they can be set in any combination. 

Note: ODR-triggered mode has to be enabled / disabled when the device is in power-down mode. 

Note: When ODR-triggered mode is enabled, the 1100 configuration of the ODR_XL_[3:0] bits in register CTRL1 (10h) and the 1100 configuration of the ODR_G_[3:0] bits in register CTRL2 (11h) cannot be used. 

Note: ODR-triggered mode is not compatible with the analog hub / Qvar functionality nor the EIS functionality. 

## 6.7 Analog hub functionality

The LSM6DSV16X embeds an analog hub sensing functionality which is able to connect an analog input and convert it to a digital signal for embedded processing. 

In the LSM6DSV16X, the analog hub has a dedicated channel that can be activated by setting the AH_QVAR_EN bit to 1 in the CTRL7 (16h) register. 

The accelerometer sensor must be set in high-performance mode or in normal mode when the analog hub channel is enabled. 

The analog hub data-ready signal is represented by the AH_QVARDA bit of the STATUS_REG (1Eh) register. This signal can be driven to the INT2 pin by setting the INT2_DRDY_AH_QVAR bit to 1 in the CTRL7 (16h) register. 

Analog hub data are available as a 16-bit word in two’s complement in the AH_QVAR_OUT_L (3Ah) and AH_QVAR_OUT_H (3Bh) registers at a fixed rate of 240 Hz (typical). 

Analog signal data can be also processed by MLC/FSM logic. 

The analog hub functionality is available in mode 1 connection mode for the I²C interface only. The external analog lines have to be connected to pin 2 (SDx/AH1/Qvar1) and/or pin 3 (SCx/AH2/Qvar2), so the I²C-master interface (mode 2) and the auxiliary SPI (mode 3) are not available when the analog hub is used. 

The equivalent input impedance of the analog hub buffers can be selected by properly setting the AH_QVAR_C_ZIN_[1:0] bits in the CTRL7 (16h) register. 

## 6.8 Qvar functionality

The LSM6DSV16X embeds a Qvar sensor which is able to detect electric charge variations in the proximity of the external electrodes connected to the device. 

In the LSM6DSV16X, Qvar has a dedicated channel that can be activated by setting the AH_QVAR_EN bit to 1 in the CTRL7 (16h) register. 

The accelerometer sensor must be set in high-performance mode or in normal mode when the Qvar channel is enabled. 

The Qvar data-ready signal is represented by the AH_QVARDA bit of the STATUS_REG (1Eh) register. This signal can be driven to the INT2 pin by setting the INT2_DRDY_AH_QVAR bit to 1 in the CTRL7 (16h) register. 

Qvar data are available as a 16-bit word in two’s complement in the AH_QVAR_OUT_L (3Ah) and AH_QVAR_OUT_H (3Bh) registers at a fixed rate of 240 Hz (typical). 

Qvar data can also be processed by MLC/FSM logic. 

The Qvar functionality is available in mode 1 connection mode for the I²C interface only. The external electrodes have to be connected to pin 2 (SDx/AH1/Qvar1) and/or pin 3 (SCx/AH2/Qvar2), so the I²C-master interface (mode 2) and the auxiliary SPI (mode 3) are not available when Qvar is used. 

The equivalent input impedance of the Qvar buffers can be selected by properly setting the AH_QVAR_C_ZIN_[1:0] bits in the CTRL7 (16h) register. 

## Block diagram of filters


Figure 18. Block diagram of filters


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/f42d3659925601f9773a1f755fbfe92768497f366ea075298c70ab7878906bdb.jpg)


## 6.9.1

## Block diagrams of the accelerometer filters

In the LSM6DSV16X, the filtering chain for the accelerometer part is composed of the following: 

Digital filter (LPF1) 

Composite filter 

Details of the block diagram appear in the following figure. 


Figure 19. Accelerometer UI chain


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/5edf33c6d7453a4e1bb807ee376425ba531c39b37152670b3f552962fe43ec4b.jpg)



Figure 20. Accelerometer composite filter


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/958ab030222b336a859555aaf1a67508a0d01aab27f78e7dd009ae3230d663de.jpg)


1. The cutoff value of the LPF1 output is ODR/2 when the accelerometer is in high-performance mode, high-accuracy ODR mode, or normal mode. This value is equal to 2300 Hz when the accelerometer is in low-power mode 1 (2 mean), 912 Hz in low-power mode 2 (4 mean) or 431 Hz in low-power mode 3 (8 mean). 

Embedded functions include finite state machine, machine learning core, pedometer, step detector and step counter, significant motion detection, and tilt functions. 

The accelerometer filtering chain when mode 3 is enabled is illustrated in the following figure. 


Figure 21. Accelerometer chain with mode 3 enabled


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/abc142806f0d6176ac6bdfcb931ab8f324df620635b3855971c580ed1efe9069.jpg)


The accelerometer OIS chain is enabled by setting the OIS_XL_EN bit to 1 in the UI_CTRL1_OIS (70h) / SPI2_CTRL1_OIS (70h) register. 

The configuration of the accelerometer UI chain is not affected by enabling/disabling the accelerometer OIS chain, with one exception: accelerometer normal operating mode (OP_MODE_XL_[2:0] = 111 in the CTRL1 (10h) register) cannot be used when the accelerometer OIS chain is enabled. 

Accelerometer output values are available in the following registers with ODR at 7.68 kHz: 

UI_OUTX_L_A_OIS_DualC (34h) and UI_OUTX_H_A_OIS_DualC (35h) through UI_OUTZ_L_A_OIS_DualC (38h) and UI_OUTZ_H_A_OIS_DualC (39h) 

SPI2_OUTX_L_A_OIS (28h) and SPI2_OUTX_H_A_OIS (29h) through SPI2_OUTZ_L_A_OIS (2Ch) and SPI2_OUTZ_H_A_OIS (2Dh) 

When the accelerometer OIS is used, refer to the product application note for the power mode configuration and settings. 

## 6.9.2

## Block diagrams of the gyroscope filters

In the LSM6DSV16X, the gyroscope filtering chain depends on the mode configuration: 

Mode 1 (for user interface (UI) and electronic image stabilization (EIS) functionality through the primary interface) and mode 2 


Figure 22. Gyroscope digital chain - mode 1 (UI/EIS) and mode 2


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/a5afcf457bcb7983ada056e6569b47bf4bd58ee766729649b5d2d73e70f5c20e.jpg)


1. When the gyroscope OIS or EIS chain is enabled, the LPF1 filter is not available in the gyroscope UI chain. It is recommended to avoid using the LPF1 filter in the gyroscope UI chain when the gyroscope OIS or EIS is used. 

2. The LPF1 filter is available in high-performance mode only. If the gyroscope is configured in low-power mode, the LPF1 filter is bypassed. 

In this configuration, the gyroscope ODR is selectable from 7.5 Hz up to 7.68 kHz. A low-pass filter (LPF1) is available, for more details about the filter characteristics see Table 64. Gyroscope LPF1 + LPF2 bandwidth selection. 

The digital LPF2 filter's cutoff frequency depends on the selected gyroscope ODR, as indicated in the following table. 


Table 21. Gyroscope LPF2 bandwidth selection


<table><tr><td>Gyroscope ODR [Hz]</td><td>LPF2 cutoff [Hz]</td></tr><tr><td>7.5</td><td>3.4</td></tr><tr><td>15</td><td>6.6</td></tr><tr><td>30</td><td>13.0</td></tr><tr><td>60</td><td>24.6</td></tr><tr><td>120</td><td>49.4</td></tr><tr><td>240</td><td>96</td></tr><tr><td>480</td><td>187</td></tr><tr><td>960</td><td>342</td></tr><tr><td>1.92 kHz</td><td>491</td></tr><tr><td>3.84 kHz</td><td>528</td></tr><tr><td>7.68 kHz</td><td>537</td></tr></table>


Note: Data can be acquired from the output registers and FIFO over the primary I²C/MIPI I3C<sup>®</sup>/SPI interface. 


Mode 3 (for OIS functionality) 


Figure 23. Gyroscope digital chain - mode 3 (OIS)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/6f90187b97eeef1d93ac2268f18975e47445faaafe2c68b12e073f80f8b806f5.jpg)


1. When the gyroscope OIS or EIS chain is enabled, the LPF1 filter is not available in the gyroscope UI chain. 

2. It is recommended to avoid using the LPF1 filter in mode1/2 when the gyroscope OIS or EIS chain is used. 

3. When the gyroscope OIS is used, refer to the product application note for the power mode configuration and settings. 

The auxiliary interface needs to be enabled in UI_CTRL1_OIS (70h) / SPI2_CTRL1_OIS (70h). 

In mode 3 configuration, there are two paths: 

The chain for user interface (UI) where the ODR is selectable from 7.5 Hz up to 7.68 kHz 

The chain for OIS where the ODR is at 7.68 kHz and the LPF1 is available. The LPF1 configuration depends on the setting of the LPF1_G_OIS_BW_[1:0] bits in register UI_CTRL2_OIS (71h) / SPI2_CTRL2_OIS (71h); for more details about the filter characteristics see UI_CTRL2_OIS (71h). Gyroscope output values are in registers 22h to 27h if read from the Auxi_SPI or in registers 2Eh to 33h if read from the primary interface with the selected full scale FS_G_OIS_[1:0] bits in UI_CTRL2_OIS (71h) / SPI2_CTRL2_OIS (71h)). 

## Enhanced EIS

The LSM6DSV16X offers advanced design flexibility for EIS applications: enhanced EIS functionality has a dedicated channel and processing with independent filtering. 

Enhanced EIS main features: 

Enhanced EIS channel gyroscope data can be read over the primary interfaces through I²C / MIPI I3C<sup>®</sup> / SPI. 

EIS data are available in free-run mode in the output registers (UI_OUTX_L_G_OIS_EIS (2Eh) and UI_OUTX_H_G_OIS_EIS (2Fh) through UI_OUTZ_L_G_OIS_EIS (32h) and UI_OUTZ_H_G_OIS_EIS (33h)) by setting the G_EIS_ON_G_OIS_OUT_REG bit to 1 in the CTRL_EIS (6Bh) register or in FIFO (by setting the G_EIS_FIFO_EN bit to 1 in the FIFO_CTRL4 (0Ah) register) with dedicated TAG and timestamp configurable using FIFO_CTRL4 (0Ah). 

Enhanced EIS option is compatible with mode 3 selection. When EIS data-out are read from the output registers (setting G_EIS_ON_G_OIS_OUT_REG bit), data from the gyroscope OIS chain can be only read from the auxiliary SPI interface. 


Figure 24. LSM6DSV16X supports UI, enhanced EIS, and OIS processing simultaneously


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/10cabbd15e14c154b581b209947bf866c50fdadd1bbc3b76c50c8a96da843f73.jpg)



Figure 25. Gyroscope enhanced EIS and UI block diagram


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/42222bf386802397dad086d7fa08ab1b3b74c822351d3b8502834f64af3a1051.jpg)


When enhanced EIS mode is activated through the ODR_EIS_[1:0] bits in the CTRL_EIS (6Bh) register: 

Gyroscope UI can be configured only in power-down mode, high-performance mode, or high-accuracy ODR mode. 

Gyroscope EIS full scale can be selected by using the FS_G_EIS_[2:0] bits in the CTRL_EIS (6Bh) register. 

Gyroscope EIS data rate selectable at 1.92 kHz or 960 Hz configurable through the ODR_G_EIS_[1:0] bits in the CTRL_EIS (6Bh) register. 

LPF_EIS low-pass filter (refer to Figure 25) bandwidth selection can be configured through the LPF_G_EIS_BW bit in the CTRL_EIS (6Bh) register. 

## 6.11 OIS

This section describes OIS functionality. There is a dedicated gyroscope and accelerometer DSP for OIS. The device also supports self-test functionality on the OIS side. 

## 6.11.1 Enabling OIS functionality and connection schemes

There are two different ways in order to enable and configure OIS functionality: 

Auxiliary SPI full control: Enabling and configuration done from the auxiliary SPI 

Primary interface full control: Enabling and configuration done from the primary interface 

The configurations that allow selecting these two different options are done using the OIS_CTRL_FROM_UI bit in the FUNC_CFG_ACCESS (01h) register as described in the following table. 


Table 22. OIS configurations


<table><tr><td>OIS_CTRL_FROM_UI</td><td>OIS configuration option</td></tr><tr><td>0</td><td>Auxiliary SPI full control</td></tr><tr><td>1</td><td>Primary interface full control</td></tr></table>

## 6.11.1.1

## Auxiliary SPI full control

This is the default condition of the device. The camera module is completely independent from the application processor as shown in Figure 26. 

The auxiliary SPI can configure OIS functionality through SPI2_INT_OIS (6Fh), SPI2_CTRL1_OIS (70h), SPI2_CTRL2_OIS (71h), SPI2_CTRL3_OIS (72h). 

Reading from the auxiliary SPI is enabled only when the SPI2_READ_EN bit in the SPI2_CTRL1_OIS (70h) register is set to 1. 

The primary interface can access the OIS control registers (UI_INT_OIS (6Fh), UI_CTRL1_OIS (70h), UI_CTRL2_OIS (71h), UI_CTRL3_OIS (72h)) in read mode. 

![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/63fa71be020cafe44e17852ef6f51c7dc84090d606a48160af3236ae9805f4f0.jpg)



Figure 26. Auxiliary SPI full contro


## 6.11.1.2

## Primary interface full control

This option allows the application processor to configure all OIS functionalities from the primary interface. This option allows using embedded OIS data for both the main and front camera, connecting them to the application processor (eventually adding a context hub) as shown in Figure 27: the AP can also do some processing on the data before sending them to the cameras. 

In order to place the device in this mode, the OIS_CTRL_FROM_UI bit in the FUNC_CFG_ACCESS (01h) register must be set to 1 from the primary interface. 


Figure 27. OIS Primary interface full control


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/2a29dbfe7402dfe574b45339e690818a7a018894fd2eea3fb7fbccb7c14c92ff.jpg)



(a)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/9b493b14b4225ca8efbbe7d90abc8ffa341e4d7409c3d521f6b68b0fc0be9d7d.jpg)



(b)


Then, the AP can configure OIS functionalities through UI_INT_OIS (6Fh), UI_CTRL1_OIS (70h), UI_CTRL2_OIS (71h), UI_CTRL3_OIS (72h). 

Reading from the auxiliary SPI can be enabled by setting the SPI2_ READ_EN bit in the UI_CTRL1_OIS (70h) register to 1 in order to directly read OIS data (as shown in Figure 27 (b)). The auxiliary SPI can access the SPI2_INT_OIS (6Fh), SPI2_CTRL1_OIS (70h), SPI2_CTRL2_OIS (71h), and SPI2_CTRL3_OIS (72h) registers in read-only mode. 

The OIS_CTRL_FROM_UI bit is reset by the software reset procedure. 

## 6.12 FIFO

The presence of a FIFO allows consistent power saving for the system since the host processor does not need continuously poll data from the sensor, but It can wake up only when needed and burst the significant data out from the FIFO. 

The LSM6DSV16X embeds 1.5 KB of data in FIFO (up to 4.5 KB with the compression feature enabled) to store the following data: 

Gyroscope 

Accelerometer 

External sensors (up to 4) 

Step counter 

Timestamp 

Temperature 

MLC features and filters 

SFLP output data (quaternion, gyroscope bias, gravity vector) 

Writing data in the FIFO can be configured to be triggered by the: 

Accelerometer / gyroscope data-ready signa 

Sensor hub data-ready signal 

Step detection signal 

The applications have maximum flexibility in choosing the rate of batching for physical sensors with FIFOdedicated configurations: accelerometer, gyroscope and temperature sensor batch rates can be selected by the user. External sensor writing in FIFO can be triggered by the accelerometer data-ready signal or by an external sensor interrupt. The step counter can be stored in FIFO with associated timestamp each time a step is detected. It is possible to select decimation for timestamp batching in FIFO with a factor of 1, 8, or 32. 

The reconstruction of a FIFO stream is a simple task thanks to the FIFO_DATA_OUT_TAG byte that allows recognizing the meaning of a word in FIFO. 

FIFO allows correct reconstruction of the timestamp information for each sensor stored in FIFO. If a change in the ODR or BDR (batch data rate) configuration is performed, the application can correctly reconstruct the timestamp and know exactly when the change was applied without disabling FIFO batching. FIFO stores information of the new configuration and timestamp in which the change was applied in the device. 

Finally, FIFO embeds a compression algorithm that the user can enable in order to have up to 4.5 KB data stored in FIFO and take advantage of interface communication length for FIFO flushing and communication power consumption. 

The programmable FIFO watermark threshold can be set using the WTM[7:0] bits in the FIFO_CTRL1 (07h) register. To monitor the FIFO status, dedicated registers (FIFO_STATUS1 (1Bh), FIFO_STATUS2 (1Ch)) can be read to detect FIFO overrun events, FIFO full status, FIFO empty status, FIFO watermark status and the number of unread samples stored in the FIFO. To generate dedicated interrupts on the INT1 and INT2 pins of these status events, the configuration can be set in INT1_CTRL (0Dh) and INT2_CTRL (0Eh). 

The FIFO buffer can be configured according to seven different modes: 

Bypass mode 

FIFO mode 

Continuous mode 

Continuous-to-FIFO mode 

ContinuousWTM-to-full mode 

Bypass-to-continuous mode 

Bypass-to-FIFO mode 

Each mode is selected by the FIFO_MODE_[2:0] bits in the FIFO_CTRL4 (0Ah) register. 

## 6.12.1 Bypass mode

In bypass mode (FIFO_CTRL4 (0Ah)(FIFO_MODE_[2:0] = 000), the FIFO is not operational and it remains empty. Bypass mode is also used to reset the FIFO when in FIFO mode. 

## 6.12.2

## FIFO mode

In FIFO mode (FIFO_CTRL4 (0Ah)(FIFO_MODE_[2:0] = 001) data from the output channels are stored in the FIFO until it is full. 

To reset FIFO content, bypass mode should be selected by writing FIFO_CTRL4 (0Ah)(FIFO_MODE_[2:0]) to 000. After this reset command, it is possible to restart FIFO mode by writing FIFO_CTRL4 (0Ah) (FIFO_MODE_[2:0]) to 001. 

The FIFO buffer memorizes up to 4.5 KB of data (with compression enabled) but the depth of the FIFO can be resized by setting the WTM[7:0] bits in FIFO_CTRL1 (07h). If the STOP_ON_WTM bit in FIFO_CTRL2 (08h) is set to 1, FIFO depth is limited up to the WTM[7:0] bits in the FIFO_CTRL1 (07h) register. 

## 6.12.3 Continuous mode

Continuous mode (FIFO_CTRL4 (0Ah)(FIFO_MODE_[2:0] = 110) provides a continuous FIFO update: as new data arrives, the older data is discarded. 

A FIFO threshold flag FIFO_STATUS2 (1Ch)(FIFO_WTM_IA) is asserted when the number of unread samples in FIFO is greater than or equal to FIFO_CTRL1 (07h) (WTM[7:0]). 

It is possible to route the FIFO_WTM_IA flag to the INT1 pin by writing in register INT1_CTRL (0Dh) (INT1_FIFO_TH) = 1 or to the INT2 pin by writing in register INT2_CTRL (0Eh)(INT2_FIFO_TH) = 1. 

A full-flag interrupt can be enabled, INT1_CTRL (0Dh)(INT1_FIFO_FULL) = 1 or INT2_CTRL (0Eh) 

(INT2_FIFO_FULL) = 1, in order to indicate FIFO saturation and eventually read its content all at once. 

If an overrun occurs, at least one of the oldest samples in FIFO has been overwritten and the FIFO_OVR_IA flag in FIFO_STATUS2 (1Ch) is asserted. 

In order to empty the FIFO before it is full, it is also possible to pull from FIFO the number of unread samples available in FIFO_STATUS1 (1Bh) and FIFO_STATUS2 (1Ch)(DIFF_FIFO_[8:0]). 

## 6.12.4

## Continuous-to-FIFO mode

In continuous-to-FIFO mode (FIFO_CTRL4 (0Ah)(FIFO_MODE_[2:0] = 011), FIFO behavior changes according to the trigger event detected in one of the following interrupt events: 

Single tap 

Double tap 

Wake-up 

Free-fall 

D6D 

When the selected trigger bit is equal to 1, FIFO operates in FIFO mode. 

When the selected trigger bit is equal to 0, FIFO operates in continuous mode. 

## 6.12.5

## ContinuousWTM-to-full mode

In continuousWTM-to-full mode (FIFO_CTRL4 (0Ah)(FIFO_MODE_[2:0] = 010), FIFO behavior changes according to the trigger event detected in one of the following interrupt events: 

Single tap 

Double tap 

Wake-up 

Free-fall 

D6D 

When the selected trigger bit is equal to 0, FIFO operates in continuous mode with the FIFO size limited to the FIFO watermark level (defined by the WTM[7:0] bits in the FIFO_CTRL1 (07h) register). 

When the selected trigger bit is equal to 1, FIFO continues to store data until it is full. 

## 6.12.6 Bypass-to-continuous mode

In bypass-to-continuous mode (FIFO_CTRL4 (0Ah)(FIFO_MODE_[2:0] = 100), data measurement storage inside FIFO operates in Continuous mode when selected triggers are equal to 1, otherwise FIFO content is reset (bypass mode). 

FIFO behavior changes according to the trigger event detected in one of the following interrupt events: 

Single tap 

Double tap 

Wake-up 

Free-fall 

D6D 

## 6.12.7 Bypass-to-FIFO mode

In bypass-to-FIFO mode (FIFO_CTRL4 (0Ah)(FIFO_MODE_[2:0] = 111), data measurement storage inside FIFO operates in FIFO mode when selected triggers are equal to 1, otherwise FIFO content is reset (bypass mode). FIFO behavior changes according to the trigger event detected in one of the following interrupt events: 

Single tap 

Double tap 

Wake-up 

Free-fall 

D6D 

## 6.12.8

## FIFO reading procedure

The data stored in FIFO are accessible from dedicated registers and each FIFO word is composed of 7 bytes: one tag byte (FIFO_DATA_OUT_TAG (78h), in order to identify the sensor, and 6 bytes of fixed data (FIFO_DATA_OUT registers from (79h) to (7Eh)). 

The DIFF_FIFO_[8:0] field in the FIFO_STATUS1 (1Bh) and FIFO_STATUS2 (1Ch) registers contains the number of words (1 byte TAG + 6 bytes DATA) collected in FIFO. 

In addition, it is possible to configure a counter of the batch events of accelerometer or gyroscope sensors. The flag COUNTER_BDR_IA in FIFO_STATUS2 (1Ch) alerts that the counter reaches a selectable threshold (CNT_BDR_TH_[9:0] field in COUNTER_BDR_REG1 (0Bh) and COUNTER_BDR_REG2 (0Ch)). This allows triggering the reading of FIFO with the desired latency of one single sensor. The sensor is selectable using the TRIG_COUNTER_BDR_[1:0] bits in COUNTER_BDR_REG1 (0Bh). As for the other FIFO status events, the flag COUNTER_BDR_IA can be routed on the INT1 or INT2 pins by asserting the corresponding bits (INT1_CNT_BDR of INT1_CTRL (0Dh) and INT2_CNT_BDR of INT2_CTRL (0Eh)). 

In order to maximize the amount of accelerometer and gyroscope data in FIFO, the user can enable the compression algorithm by setting to 1 both the FIFO_COMPR_EN bit in EMB_FUNC_EN_B (05h) (embedded functions registers bank) and the FIFO_COMPR_RT_EN bit in FIFO_CTRL2 (08h). When compression is enabled, it is also possible to force writing noncompressed data at a selectable rate using the UNCOMPR_RATE_[1:0] field in FIFO_CTRL2 (08h). 

Meta information about accelerometer and gyroscope sensor configuration changes can be managed by enabling the ODR_CHG_EN bit in FIFO_CTRL2 (08h). 

## Application hints

## 7.1 LSM6DSV16X electrical connections in mode 1


Figure 28. LSM6DSV16X electrical connections in mode 1


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/fc4e63b824d989ef4a5341067161222b1b8b34df40d01d7b2cb32ce4e6a15baf.jpg)


1. Leave pin electrically unconnected and soldered to $P C B .$ 

The device core is supplied through the Vdd line. Power supply decoupling capacitors (C1, ${ \mathsf { C } } 2 = 1 0 0$ nF ceramic) should be placed as near as possible to the supply pin of the device (common design practice). 

The functionality of the device and the measured acceleration/angular rate data is selectable and accessible through the SPI/I²C/MIPI ${ \mathsf { I } } 3 { \mathsf { C } } ^ { \circledast }$ interface. 

The functions, the threshold, and the timing of the two interrupt pins for each sensor can be completely programmed by the user through the SPI/I²C/MIPI ${ \mathsf { I } } 3 { \mathsf { C } } ^ { \circledast }$ interface. 


Figure 29. Qvar external connections to pin 2, 3 (Qvar input)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/824128326137df19724c9f7affa15c6bca4038bd9a8b5cf33f8bcd185f44117c.jpg)



(1) ST ESDALCL5-1BM2 is referenced as an ST catalog product but similar features of other ESD diodes also can be used


Note: 

Figure 29 provides an example of a test circuit. For a specific application, refer to the related application note. 

## 7.2

## LSM6DSV16X electrical connections in mode 2

## Figure 30. LSM6DSV16X electrical connections in mode 2

![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/91d46ede488046cb784043ea2057b4f75f9ac2a8977c93f985e0e5470b5f04a3.jpg)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/5b647d5da7a949b627801cb7211da3aaa28ea1f9bbc5ab53aa0807560b3bbf4a.jpg)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/b3666c52e5689a2f5d4a0550952459d32482a081bbd0c4e29b2147c3610281dd.jpg)


## 1. Leave pin electrically unconnected and soldered to $P C B .$

The device core is supplied through the Vdd line. Power supply decoupling capacitors (C1, C2 = 100 nF ceramic) should be placed as near as possible to the supply pin of the device (common design practice). 

The functionality of the device and the measured acceleration/angular rate data is selectable and accessible through the $\mathsf { S P } | / | ^ { 2 } \mathsf { C / M I P } | \mathsf { \Omega } | 3 \mathsf { C } ^ { \otimes }$ primary interface. 

The functions, the threshold, and the timing of the two interrupt pins for each sensor can be completely programmed by the user through the SPI/I²C/MIPI ${ \mathsf { I } } 3 { \mathsf { C } } ^ { \circledast }$ primary interface. 

## 7.3

## LSM6DSV16X electrical connections in mode 3


Figure 31. LSM6DSV16X electrical connections in mode 3 (auxiliary 3/4-wire SPI)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/99aafae695f0aae29b712f1dbd4efee4e200ae90fac9ed07fb576a354c1f9408.jpg)


When mode 3 is used, the pull-up on pins 10 and 11 can be enabled or disabled (refer to Table 23. Internal pin status). To avoid leakage current, it is not recommended to leave the SPI lines floating (or when the OIS system is off). 

The device core is supplied through the Vdd line. Power supply decoupling capacitors $( \mathsf C 1 , \mathsf C 2 = 1 0 0$ nF ceramic) should be placed as near as possible to the supply pin of the device (common design practice). 

The functionality of the device is selectable and accessible through the SPI/I²C/MIPI ${ \mathsf { I } } 3 { \mathsf { C } } ^ { \circledast }$ primary interface. 

Measured acceleration/angular rate data is selectable and accessible through the SPI/I²C/MIPI ${ \mathsf { I } } 3 { \mathsf { C } } ^ { \circledast }$ primary interface and auxiliary SPI. 

The functions, the threshold, and the timing of the two interrupt pins for each sensor can be completely programmed by the user through the $\mathsf { S P } | / | ^ { 2 } \mathsf { C / M } | \mathsf { P } | \mathsf { \ B C } ^ { \otimes }$ interface. 

Note: When mode 3 is used, refer to the product application note for the power mode configuration and settings. 

<table><tr><td>pin#</td><td>Name</td><td>Mode 1 function</td><td>Mode 2 function</td><td>Mode 3 function</td><td>Pin status mode 1</td><td>Pin status mode 2</td><td>Pin status mode <eq>{3}^{\left( 1\right) }</eq></td></tr><tr><td rowspan="2">1</td><td>SDO</td><td>SPI 4-wire interface serial data output (SDO)</td><td>SPI 4-wire interface serial data output (SDO)</td><td>SPI 4-wire interface serial data output (SDO)</td><td rowspan="2">Default: input without pull-up Pull-up is enabled if bit SDO_PU_EN = 1 in register PIN_CTRL (02h).</td><td rowspan="2">Default: input without pull-up Pull-up is enabled if bit SDO_PU_EN = 1 in register PIN_CTRL (02h).</td><td rowspan="2">Default: input without pull-up Pull-up is enabled if bit SDO_PU_EN = 1 in register PIN_CTRL (02h).</td></tr><tr><td>SA0</td><td><eq>{\mathrm{I}}^{ \circ }\mathrm{C}</eq> least significant bit of the device address (SAO) MIPI I3C® least significant bit of the static address (SAO)</td><td><eq>{\mathrm{I}}^{ \circ }\mathrm{C}</eq> least significant bit of the device address (SAO) MIPI I3C® least significant bit of the static address (SAO)</td><td><eq>{\mathrm{I}}^{ \circ }\mathrm{C}</eq> least significant bit of the device address (SAO) MIPI I3C® least significant bit of the static address (SAO)</td></tr><tr><td>2</td><td>SDx/AH1/Qvar1</td><td>Connect to Vdd_IO or GND if the analog hub and/or Qvar are disabled. Connect to the analog input or Qvar electrode 1 if the Qvar function is enabled.(2)</td><td><eq>{\mathrm{I}}^{ \circ }\mathrm{C}</eq> serial data master (MSDA)</td><td>Auxiliary SPI 3/4-wire interface serial data input (SDI_Aux) and SPI 3- wire serial data output (SDO_Aux)</td><td>Default: input without pull-up Pull-up is enabled if bit SHUB_PU_EN = 1 in register IF_CFG (03h).</td><td>Default: input without pull-up Pull-up is enabled if bit SHUB_PU_EN = 1 in register IF_CFG (03h).</td><td>Default: input without pull-up Pull-up is enabled if bit SHUB_PU_EN = 1 in register IF_CFG (03h).</td></tr><tr><td>3</td><td>SCx/AH2/Qvar2</td><td>Connect to Vdd_IO or GND if the analog hub and/or Qvar are disabled. Connect to the analog input or Qvar electrode 2 if the Qvar function is enabled.(2)</td><td><eq>{\mathrm{I}}^{ \circ }\mathrm{C}</eq> serial clock master (MSCL)</td><td>Auxiliary SPI 3/4-wire interface serial port clock (SPC_Aux)</td><td>Default: input without pull-up Pull-up is enabled if bit SHUB_PU_EN = 1 in register IF_CFG (03h).</td><td>Default: input without pull-up Pull-up is enabled if bit SHUB_PU_EN = 1 in register IF_CFG (03h).</td><td>Default: input without pull-up Pull-up is enabled if bit SHUB_PU_EN = 1 in register IF_CFG (03h)</td></tr><tr><td>4</td><td>INT1</td><td>Programmable interrupt 1</td><td>Programmable interrupt 1</td><td>Programmable interrupt 1</td><td>Default: output forced to ground</td><td>Default: output forced to ground</td><td>Default: output forced to ground</td></tr><tr><td>5</td><td>Vdd_IO</td><td>Power supply for I/O pins</td><td>Power supply for I/O pins</td><td>Power supply for I/O pins</td><td></td><td></td><td></td></tr><tr><td>6</td><td>GND</td><td>0 V supply</td><td>0 V supply</td><td>0 V supply</td><td></td><td></td><td></td></tr><tr><td>7</td><td>GND</td><td>0 V supply</td><td>0 V supply</td><td>0 V supply</td><td></td><td></td><td></td></tr><tr><td>8</td><td>Vdd</td><td>Power supply</td><td>Power supply</td><td>Power supply</td><td></td><td></td><td></td></tr><tr><td>9</td><td>INT2</td><td>Programmable interrupt 2 (INT2) / Data enabled (DEN) / I²C master external synchronization signal (MDRDY)</td><td>Programmable interrupt 2 (INT2) / Data enabled (DEN)</td><td>Programmable interrupt 2 (INT2) / Data enabled (DEN)</td><td>Default: output forced to ground</td><td>Default: output forced to ground</td><td>Default: output forced to ground</td></tr><tr><td>10</td><td>OCS_Aux</td><td>Connect to Vdd_IO or leave unconnected</td><td>Connect to Vdd_IO or leave unconnected</td><td>Auxiliary SPI 3/4-wire interface enabled</td><td>Default: input with pull-up Pull-up is disabled if bit OIS_PU_DIS = 1 in register PIN_CTRL (02h).</td><td>Default: input with pull-up Pull-up is disabled if bit OIS_PU_DIS = 1 in register PIN_CTRL (02h).</td><td>Default: input without pull-up (regardless of the value of bit OIS_PU_DIS in register PIN_CTRL (02h))</td></tr><tr><td>11</td><td>SDO_Aux</td><td>Connect to Vdd_IO or leave unconnected</td><td>Connect to Vdd_IO or leave unconnected</td><td>Auxiliary SPI 3- wire interface: leave unconnected / Auxiliary SPI 4-wire interface: serial data output (SDO_Aux)</td><td>Default: input with pull-up Pull-up is disabled if bit OIS_PU_DIS = 1 in register PIN_CTRL (02h).</td><td>Default: input with pull-up Pull-up is disabled if bit OIS_PU_DIS = 1 in register PIN_CTRL (02h).</td><td>Default: input without pull-up Pull-up is enabled if bit SIM_OIS = 1 (Aux_SPI 3-wire) in reg 70h and bit OIS_PU_DIS = 0 in register PIN_CTRL (02h).</td></tr><tr><td>12</td><td>CS</td><td><eq>{\mathrm{I}}^{ \circ }\mathrm{C}/\mathrm{{SPI}}</eq> mode selection (1: SPI idle mode / I²C communication enabled; 0: SPI communication mode / I²C disabled)</td><td><eq>{\mathrm{I}}^{ \circ }\mathrm{C}/\mathrm{{SPI}}</eq> mode selection (1: SPI idle mode / I²C communication enabled; 0: SPI communication mode / I²C disabled)</td><td><eq>{\mathrm{I}}^{ \circ }\mathrm{C}/\mathrm{{SPI}}</eq> mode selection (1: SPI idle mode / I²C communication enabled; 0: SPI communication mode / I²C disabled)</td><td>Default: input with pull-up Pull-up is disabled if bit I2C_I3C_disable = 1 in register IF_CFG (03h).</td><td>Default: input with pull-up Pull-up is disabled if bit I2C_I3C_disable = 1 in register IF_CFG (03h).</td><td>Default: input with pull-up Pull-up is disabled if bit I2C_I3C_disable = 1 in register IF_CFG (03h).</td></tr><tr><td>pin#</td><td>Name</td><td>Mode 1 function</td><td>Mode 2 function</td><td>Mode 3 function</td><td>Pin status mode 1</td><td>Pin status mode 2</td><td>Pin status mode 3 (1)</td></tr><tr><td>13</td><td>SCL</td><td>I2C/MIPI I3C® serial clock (SCL) / SPI serial port clock (SPC)</td><td>I2C/MIPI I3C® serial clock (SCL) / SPI serial port clock (SPC)</td><td>I2C/MIPI I3C® serial clock (SCL) / SPI serial port clock (SPC)</td><td>Default: input without pull-up</td><td>Default: input without pull-up</td><td>Default: input without pull-up</td></tr><tr><td>14</td><td>SDA</td><td>I2C/MIPI I3C® serial data (SDA) / SPI serial data input (SDI) / 3-wire interface serial data output (SDO)</td><td>I2C/MIPI I3C® serial data (SDA) / SPI serial data input (SDI) / 3-wire interface serial data output (SDO)</td><td>I2C/MIPI I3C® serial data (SDA) / SPI serial data input (SDI) / 3-wire interface serial data output (SDO)</td><td>Default: input without pull-upPull-up is enabled if bit SDA_PU_EN = 1 in register IF_CFG (03h).</td><td>Default: input without pull-upPull-up is enabled if bit SDA_PU_EN = 1 in register IF_CFG (03h).</td><td>Default: input without pull-upPull-up is enabled if bit SDA_PU_EN = 1 in register IF_CFG (03h).</td></tr></table>


1. Mode 3 is enabled when the OIS_XL_EN bit or the OIS_G_EN bit in the UI_CTRL1_OIS (70h) / SPI2_CTRL1_OIS (70h) registers is set to 1. 



2. The analog hub and Qvar functions are enabled by setting the AH_QVAR_EN bit to 1 in CTRL7 (16h) 


Internal pull-up value is from 30 kΩ to 50 kΩ, depending on Vdd_IO. 

![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/bd18b8b48bdd5e68be52f041fc8650fe0c5bf51134cdc377fd67e333cb6883c9.jpg)


## Register mapping

The table given below provides a list of the 8/16-bit registers embedded in the device and the corresponding addresses. 

All these registers are accessible from the primary SPI/I²C/MIPI I3C<sup>®</sup> interface only. 


Table 24. Registers address map


<table><tr><td rowspan="2">Name</td><td rowspan="2">Type</td><td colspan="2">Register address</td><td rowspan="2">Default</td><td rowspan="2">Comment</td></tr><tr><td>Hex</td><td>Binary</td></tr><tr><td>FUNC_CFG_ACCESS</td><td>R/W</td><td>01</td><td>00000001</td><td>00000000</td><td></td></tr><tr><td>PIN_CTRL</td><td>R/W</td><td>02</td><td>00000010</td><td>00100011</td><td></td></tr><tr><td>IF_CFG</td><td>R/W</td><td>03</td><td>00000011</td><td>00000000</td><td></td></tr><tr><td>RESERVED</td><td>-</td><td>04-05</td><td></td><td></td><td></td></tr><tr><td>ODR_TRIG_CFG</td><td>R/W</td><td>06</td><td>00000110</td><td>00000000</td><td></td></tr><tr><td>FIFO_CTRL1</td><td>R/W</td><td>07</td><td>00000111</td><td>00000000</td><td></td></tr><tr><td>FIFO_CTRL2</td><td>R/W</td><td>08</td><td>00001000</td><td>00000000</td><td></td></tr><tr><td>FIFO_CTRL3</td><td>R/W</td><td>09</td><td>00001001</td><td>00000000</td><td></td></tr><tr><td>FIFO_CTRL4</td><td>R/W</td><td>0A</td><td>00001010</td><td>00000000</td><td></td></tr><tr><td>COUNTER_BDR_REG1</td><td>R/W</td><td>0B</td><td>00001011</td><td>00000000</td><td></td></tr><tr><td>COUNTER_BDR_REG2</td><td>R/W</td><td>0C</td><td>00001100</td><td>00000000</td><td></td></tr><tr><td>INT1_CTRL</td><td>R/W</td><td>0D</td><td>00001101</td><td>00000000</td><td></td></tr><tr><td>INT2_CTRL</td><td>R/W</td><td>0E</td><td>00001110</td><td>00000000</td><td></td></tr><tr><td>WHO_AM_I</td><td>R</td><td>0F</td><td>00001111</td><td>01110000</td><td>R (SPI2)</td></tr><tr><td>CTRL1</td><td>R/W</td><td>10</td><td>00010000</td><td>00000000</td><td>R (SPI2)</td></tr><tr><td>CTRL2</td><td>R/W</td><td>11</td><td>00010001</td><td>00000000</td><td>R (SPI2)</td></tr><tr><td>CTRL3</td><td>R/W</td><td>12</td><td>00010010</td><td>01000100</td><td>R (SPI2)</td></tr><tr><td>CTRL4</td><td>R/W</td><td>13</td><td>00010011</td><td>00000000</td><td>R (SPI2)</td></tr><tr><td>CTRL5</td><td>R/W</td><td>14</td><td>00010100</td><td>00000000</td><td>R (SPI2)</td></tr><tr><td>CTRL6</td><td>R/W</td><td>15</td><td>00010101</td><td>00000000</td><td>R (SPI2)</td></tr><tr><td>CTRL7</td><td>R/W</td><td>16</td><td>00010110</td><td>00000000</td><td>R (SPI2)</td></tr><tr><td>CTRL8</td><td>R/W</td><td>17</td><td>0001 0111</td><td>00000000</td><td>R (SPI2)</td></tr><tr><td>CTRL9</td><td>R/W</td><td>18</td><td>00011000</td><td>00000000</td><td>R (SPI2)</td></tr><tr><td>CTRL10</td><td>R/W</td><td>19</td><td>00011001</td><td>00000000</td><td>R (SPI2)</td></tr><tr><td>CTRL_STATUS</td><td>R</td><td>1A</td><td>00011010</td><td>output</td><td></td></tr><tr><td>FIFO_STATUS1</td><td>R</td><td>1B</td><td>00011011</td><td>output</td><td></td></tr><tr><td>FIFO_STATUS2</td><td>R</td><td>1C</td><td>00011100</td><td>output</td><td></td></tr><tr><td>ALL_INT_SRC</td><td>R</td><td>1D</td><td>00011101</td><td>output</td><td></td></tr><tr><td>STATUS_REG</td><td>R</td><td>1E</td><td>00011110</td><td>output</td><td></td></tr><tr><td>RESERVED</td><td>-</td><td>1F</td><td></td><td></td><td></td></tr><tr><td>OUT_TEMP_L</td><td>R</td><td>20</td><td>00100000</td><td>output</td><td></td></tr><tr><td>OUT_TEMP_H</td><td>R</td><td>21</td><td>00100001</td><td>output</td><td></td></tr><tr><td>OUTX_L_G</td><td>R</td><td>22</td><td>00100010</td><td>output</td><td></td></tr><tr><td>OUTX_H_G</td><td>R</td><td>23</td><td>00100011</td><td>output</td><td></td></tr><tr><td>OUTY_L_G</td><td>R</td><td>24</td><td>00100100</td><td>output</td><td></td></tr><tr><td>OUTY_H_G</td><td>R</td><td>25</td><td>00100101</td><td>output</td><td></td></tr><tr><td>OUTZ_L_G</td><td>R</td><td>26</td><td>00100110</td><td>output</td><td></td></tr><tr><td>OUTZ_H_G</td><td>R</td><td>27</td><td>00100111</td><td>output</td><td></td></tr><tr><td>OUTX_L_A</td><td>R</td><td>28</td><td>00101000</td><td>output</td><td></td></tr><tr><td>OUTX_H_A</td><td>R</td><td>29</td><td>00101001</td><td>output</td><td></td></tr><tr><td>OUTY_L_A</td><td>R</td><td>2A</td><td>00101010</td><td>output</td><td></td></tr><tr><td>OUTY_H_A</td><td>R</td><td>2B</td><td>00101011</td><td>output</td><td></td></tr><tr><td>OUTZ_L_A</td><td>R</td><td>2C</td><td>00101100</td><td>output</td><td></td></tr><tr><td>OUTZ_H_A</td><td>R</td><td>2D</td><td>00101101</td><td>output</td><td></td></tr><tr><td>UI_OUTX_L_G_OIS_EIS</td><td>R</td><td>2E</td><td>00101110</td><td>output</td><td></td></tr><tr><td>UI_OUTX_H_G_OIS_EIS</td><td>R</td><td>2F</td><td>00101111</td><td>output</td><td></td></tr><tr><td>UI_OUTY_L_G_OIS_EIS</td><td>R</td><td>30</td><td>00110000</td><td>output</td><td></td></tr><tr><td>UI_OUTY_H_G_OIS_EIS</td><td>R</td><td>31</td><td>00110001</td><td>output</td><td></td></tr><tr><td>UI_OUTZ_L_G_OIS_EIS</td><td>R</td><td>32</td><td>00110010</td><td>output</td><td></td></tr><tr><td>UI_OUTZ_H_G_OIS_EIS</td><td>R</td><td>33</td><td>00110011</td><td>output</td><td></td></tr><tr><td>UI_OUTX_L_A_OIS_DualC</td><td>R</td><td>34</td><td>00110100</td><td>output</td><td></td></tr><tr><td>UI_OUTX_H_A_OIS_DualC</td><td>R</td><td>35</td><td>00110101</td><td>output</td><td></td></tr><tr><td>UI_OUTY_L_A_OIS_DualC</td><td>R</td><td>36</td><td>00110110</td><td>output</td><td></td></tr><tr><td>UI_OUTY_H_A_OIS_DualC</td><td>R</td><td>37</td><td>00110111</td><td>output</td><td></td></tr><tr><td>UI_OUTZ_L_A_OIS_DualC</td><td>R</td><td>38</td><td>00111000</td><td>output</td><td></td></tr><tr><td>UI_OUTZ_H_A_OIS_DualC</td><td>R</td><td>39</td><td>00111001</td><td>output</td><td></td></tr><tr><td>AH_QVAR_OUT_L</td><td>R</td><td>3A</td><td>00111010</td><td>output</td><td></td></tr><tr><td>AH_QVAR_OUT_H</td><td>R</td><td>3B</td><td>00111011</td><td>output</td><td></td></tr><tr><td>RESERVED</td><td>-</td><td>3C-3F</td><td></td><td></td><td></td></tr><tr><td>TIMESTAMP0</td><td>R</td><td>40</td><td>01000000</td><td>output</td><td>R (SPI2)</td></tr><tr><td>TIMESTAMP1</td><td>R</td><td>41</td><td>01000001</td><td>output</td><td>R (SPI2)</td></tr><tr><td>TIMESTAMP2</td><td>R</td><td>42</td><td>01000010</td><td>output</td><td>R (SPI2)</td></tr><tr><td>TIMESTAMP3</td><td>R</td><td>43</td><td>01000011</td><td>output</td><td>R (SPI2)</td></tr><tr><td>UI_STATUS_REG_OIS</td><td>R</td><td>44</td><td>01000100</td><td>output</td><td></td></tr><tr><td>WAKE_UP_SRC</td><td>R</td><td>45</td><td>01000101</td><td>output</td><td></td></tr><tr><td>TAP_SRC</td><td>R</td><td>46</td><td>01000110</td><td>output</td><td></td></tr><tr><td>D6D_SRC</td><td>R</td><td>47</td><td>01000111</td><td>output</td><td></td></tr><tr><td>STATUS_MASTER_MAINPAGE</td><td>R</td><td>48</td><td>01001000</td><td>output</td><td></td></tr><tr><td>EMB_FUNC_STATUS_MAINPAGE</td><td>R</td><td>49</td><td>01001001</td><td>output</td><td></td></tr><tr><td>FSM_STATUS_MAINPAGE</td><td>R</td><td>4A</td><td>01001010</td><td>output</td><td></td></tr><tr><td>MLC_STATUS_MAINPAGE</td><td>R</td><td>4B</td><td>01001011</td><td>output</td><td></td></tr><tr><td>RESERVED</td><td>-</td><td>4C-4E</td><td></td><td></td><td></td></tr><tr><td>INTERNAL_FREQ_FINE</td><td>R</td><td>4F</td><td>01001111</td><td>output</td><td></td></tr><tr><td>FUNCTIONS_ENABLE</td><td>RW</td><td>50</td><td>01010000</td><td>00000000</td><td></td></tr><tr><td>DEN</td><td>R/W</td><td>51</td><td>01010001</td><td>00001110</td><td></td></tr><tr><td>INACTIVITY_DUR</td><td>R/W</td><td>54</td><td>01010100</td><td>00000100</td><td></td></tr><tr><td>INACTIVITY_THS</td><td>R/W</td><td>55</td><td>01010101</td><td>00000000</td><td></td></tr><tr><td>TAP_CFG0</td><td>R/W</td><td>56</td><td>01010110</td><td>00000000</td><td></td></tr><tr><td>TAP_CFG1</td><td>R/W</td><td>57</td><td>01010111</td><td>00000000</td><td></td></tr><tr><td>TAP_CFG2</td><td>R/W</td><td>58</td><td>01011000</td><td>00000000</td><td></td></tr><tr><td>TAP_THS_6D</td><td>R/W</td><td>59</td><td>01011001</td><td>00000000</td><td></td></tr><tr><td>TAP_DUR</td><td>R/W</td><td>5A</td><td>01011010</td><td>00000000</td><td></td></tr><tr><td>WAKE_UP_THS</td><td>R/W</td><td>5B</td><td>01011011</td><td>00000000</td><td></td></tr><tr><td>WAKE_UP_DUR</td><td>R/W</td><td>5C</td><td>01011100</td><td>00000000</td><td></td></tr><tr><td>FREE_FALL</td><td>R/W</td><td>5D</td><td>01011101</td><td>00000000</td><td></td></tr><tr><td>MD1_CFG</td><td>R/W</td><td>5E</td><td>01011110</td><td>00000000</td><td></td></tr><tr><td>MD2_CFG</td><td>R/W</td><td>5F</td><td>01011111</td><td>00000000</td><td></td></tr><tr><td>RESERVED</td><td>-</td><td>60-61</td><td></td><td></td><td></td></tr><tr><td>HAODR_CFG</td><td>R/W</td><td>62</td><td>01100010</td><td>00000000</td><td></td></tr><tr><td>EMB_FUNC_CFG</td><td>R/W</td><td>63</td><td>01100011</td><td>00000000</td><td></td></tr><tr><td>UI_HANDSHAKE_CTRL</td><td>R/W</td><td>64</td><td>01100100</td><td>00000000</td><td></td></tr><tr><td>UI_SPI2_SHARED_0</td><td>R/W</td><td>65</td><td>01100101</td><td>00000000</td><td></td></tr><tr><td>UI_SPI2_SHARED_1</td><td>R/W</td><td>66</td><td>01100110</td><td>00000000</td><td></td></tr><tr><td>UI_SPI2_SHARED_2</td><td>R/W</td><td>67</td><td>01100111</td><td>00000000</td><td></td></tr><tr><td>UI_SPI2_SHARED_3</td><td>R/W</td><td>68</td><td>01101000</td><td>00000000</td><td></td></tr><tr><td>UI_SPI2_SHARED_4</td><td>R/W</td><td>69</td><td>01101001</td><td>00000000</td><td></td></tr><tr><td>UI_SPI2_SHARED_5</td><td>R/W</td><td>6A</td><td>01101010</td><td>00000000</td><td></td></tr><tr><td>CTRL_EIS</td><td>R/W</td><td>6B</td><td>01101011</td><td>00000000</td><td></td></tr><tr><td>RESERVED</td><td>-</td><td>6C - 6E</td><td></td><td></td><td></td></tr><tr><td>UI_INT_OIS</td><td>R (SPI2 full-control mode)R/W (primary IF full-control mode)</td><td>6F</td><td>01101111</td><td>00000000</td><td></td></tr><tr><td>UI_CTRL1_OIS</td><td>R (SPI2 full-control mode)R/W (primary IF full-control mode)</td><td>70</td><td>01110000</td><td>00000000</td><td></td></tr><tr><td>UI_CTRL2_OIS</td><td>R (SPI2 full-control mode)R/W (primary IF full-control mode)</td><td>71</td><td>01110001</td><td>00000000</td><td></td></tr><tr><td>UI_CTRL3_OIS</td><td>R (SPI2 full-control mode)R/W (primary IF full-control mode)</td><td>72</td><td>01110010</td><td>00000000</td><td></td></tr><tr><td>X_OFS_USR</td><td>R/W</td><td>73</td><td>01110011</td><td>00000000</td><td></td></tr><tr><td>Y_OFS_USR</td><td>R/W</td><td>74</td><td>01110100</td><td>00000000</td><td></td></tr><tr><td>Z_OFS_USR</td><td>R/W</td><td>75</td><td>01110101</td><td>00000000</td><td></td></tr><tr><td>RESERVED</td><td>-</td><td>76-77</td><td></td><td></td><td></td></tr><tr><td>FIFO_DATA_OUT_TAG</td><td>R</td><td>78</td><td>01111000</td><td>output</td><td></td></tr><tr><td>FIFO_DATA_OUT_X_L</td><td>R</td><td>79</td><td>01111001</td><td>output</td><td></td></tr><tr><td>FIFO_DATA_OUT_X_H</td><td>R</td><td>7A</td><td>01111010</td><td>output</td><td></td></tr><tr><td>FIFO_DATA_OUT_Y_L</td><td>R</td><td>7B</td><td>01111011</td><td>output</td><td></td></tr><tr><td>FIFO_DATA_OUT_Y_H</td><td>R</td><td>7C</td><td>01111100</td><td>output</td><td></td></tr><tr><td>FIFO_DATA_OUT_Z_L</td><td>R</td><td>7D</td><td>01111101</td><td>output</td><td></td></tr><tr><td>FIFO_DATA_OUT_Z_H</td><td>R</td><td>7E</td><td>01111110</td><td>output</td><td></td></tr></table>

Reserved registers must not be changed. Writing to those registers may cause permanent damage to the device. The content of the registers that are loaded at boot should not be changed. They contain the factory calibration values. Their content is automatically restored when the device is powered up. 

## Register description

The device contains a set of registers which are used to control its behavior and to retrieve linear acceleration, angular rate, temperature, analog hub and Qvar data. The register addresses, made up of 7 bits, are used to identify them and to write the data through the serial interface. 

## 9.1 FUNC_CFG_ACCESS (01h)

Enable embedded functions register (R/W) 


Table 25. FUNC_CFG_ACCESS register


<table><tr><td>EMB_FUNC_REG_ACCESS</td><td>SHUB_REG_ACCESS</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>FSM_WR_CTRL_EN</td><td>SW_POR</td><td>SPI2_RESET</td><td>OIS_CTRL_FROM_UI</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 26. FUNC_CFG_ACCESS register description


<table><tr><td>EMB_FUNC_REG_ACCESS</td><td>Enables access to the embedded functions configuration registers. (1)Default value: 0</td></tr><tr><td>SHUB_REG_ACCESS</td><td>Enables access to the sensor hub (<eq>I^{2}C</eq> master) configuration registers. (2)Default value: 0</td></tr><tr><td>FSM_WR_CTRL_EN</td><td>Enables the control of the CTRL registers to FSM (FSM can change some configurations of the device autonomously). Default value: 0(0: disabled; 1: enabled)</td></tr><tr><td>SW_POR</td><td>Global reset of the device. Default value: 0</td></tr><tr><td>SPI2_RESET</td><td>Resets the control registers of SPI2 from the primary interface. This bit must be set to 1 and then back to 0 (this bit is not automatically cleared). Default value: 0</td></tr><tr><td>OIS_CTRL_FROM_UI</td><td>Enables the full control of OIS configurations from the primary interface. Default value: 0(0: OIS chain full control from primary interface disabled;1: OIS chain full control from primary interface enabled)</td></tr></table>


1. Details concerning the embedded functions configuration registers are available in Section 12 Embedded functions register mapping and Section 13 Embedded functions register description. 



2. Details concerning the sensor hub registers are available in Section 16 Sensor hub register mapping and Section 17 Sensor hub register description. 


## 9.2

## PIN_CTRL (02h)

SDO, OCS_Aux, SDO_Aux pins pull-up register (R/W). This register is not reset during the software reset procedure (see bit 0 of the CTRL3 (12h) register). 


Table 27. PIN_CTRL register


<table><tr><td>OIS_PU_DIS</td><td>SDO_PU_EN</td><td>IBHR_POR_EN</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>1^{(2)}</eq></td><td><eq>1^{(2)}</eq></td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



2. This bit must be set to 1 for the correct operation of the device. 



Table 28. PIN_CTRL register description


<table><tr><td>OIS_PU_DIS</td><td>Disables pull-up on both OCS_Aux and SDO_Aux pins (for mode 1 and mode 2). For further details about the configuration of the pull-up resistors in mode 3, refer toTable 23. Default value: 0(0: OCS_Aux and SDO_Aux pins with pull-up;1: OCS_Aux and SDO_Aux pins pull-up disconnected)</td></tr><tr><td>SDO_PU_EN</td><td>Enables pull-up on SDO pin. For details, refer toTable 23. Default value: 0(0: SDO pin pull-up disconnected; 1: SDO pin with pull-up)</td></tr><tr><td>IBHR_POR_EN</td><td>Selects the action the device performs after &quot;reset whole chip&quot; I3C pattern. Default value: 1(0: configuration reset (SW reset + dynamic address reset);(1: global reset (POR reset))</td></tr></table>

## IF_CFG (03h)

Interface configuration register (R/W). This register is not reset during the software reset procedure (see bit 0 of the CTRL3 (12h) register). 


Table 29. IF_CFG register


<table><tr><td>SDA_PU_EN</td><td>SHUB_PU_EN</td><td>ASF_CTRL</td><td>H_LACTIVE</td><td>PP_OD</td><td>SIM</td><td>0(1)</td><td>I2C_I3C_disable</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 30. IF_CFG register description


<table><tr><td>SDA_PU_EN</td><td>Enables pull-up on SDA pin. Default value: 0(0: SDA pin pull-up disconnected;1: SDA pin with pull-up)</td></tr><tr><td>SHUB_PU_EN</td><td>Enables master I2C pull-up. Default value: 0(0: internal pull-up on auxiliary I2C line disabled;1: internal pull-up on auxiliary I2C line enabled)</td></tr><tr><td>ASF_CTRL</td><td>Enables anti-spike filters. Default value: 0(0: anti-spike filters are managed by the protocol and turned off after the broadcast address;1: anti-spike filters on SCL and SDA lines are always enabled)</td></tr><tr><td>H_LACTIVE</td><td>Interrupt activation level. Default value: 0(0: interrupt output pins active high;1: interrupt output pins active low)</td></tr><tr><td>PP_OD</td><td>Push-pull/open-drain selection on INT1 and INT2 pins. Default value: 0(0: push-pull mode;1: open-drain mode)</td></tr><tr><td>SIM</td><td>SPI serial interface mode selection. Default value: 0(0: 4-wire interface;1: 3-wire interface)</td></tr><tr><td>I2C_I3C_disable</td><td>Disables I2C and MIPI I3C® interfaces. Default value: 0(0: SPI, I2C and MIPI I3C® interfaces enabled;1: I2C and MIPI I3C® interfaces disabled)</td></tr></table>

## ODR_TRIG_CFG (06h)

ODR-triggered mode configuration register (R/W) 


Table 31. ODR_TRIG_CFG register


<table><tr><td>ODR_TRIG_NODR_7</td><td>ODR_TRIG_NODR_6</td><td>ODR_TRIG_NODR_5</td><td>ODR_TRIG_NODR_4</td><td>ODR_TRIG_NODR_3</td><td>ODR_TRIG_NODR_2</td><td>ODR_TRIG_NODR_1</td><td>ODR_TRIG_NODR_0</td></tr></table>


Table 32. ODR_TRIG_CFG register description


<table><tr><td>ODR_TRIG_NODR_[7:0]</td><td>When ODR-triggered mode is set, these bits are used to define the number of data generated in the reference period. Allowed values for ODR_TRIG_NODR_[7:0] are 0 (default) and values in the range from 4 to 255.</td></tr></table>

## FIFO_CTRL1 (07h)

FIFO control register 1 (R/W) 


Table 33. FIFO_CTRL1 register


<table><tr><td>WTM_7</td><td>WTM_6</td><td>WTM_5</td><td>WTM_4</td><td>WTM_3</td><td>WTM_2</td><td>WTM_1</td><td>WTM_0</td></tr></table>


Table 34. FIFO_CTRL1 register description


<table><tr><td>WTM_[7:0]</td><td>FIFO watermark threshold: 1 LSB = TAG (1 byte) + 1 sensor (6 bytes) written in FIFO. Watermark flag rises when the number of bytes written in the FIFO is greater than or equal to the threshold level.</td></tr></table>

## FIFO_CTRL2 (08h)

FIFO control register 2 (R/W) 


Table 35. FIFO_CTRL2 register


<table><tr><td>STOP_ON_WTM</td><td>FIFO_COMPR_RT_EN</td><td><eq>0^{(1)}</eq></td><td>ODR_CHG_EN</td><td><eq>0^{(1)}</eq></td><td>UNCOMPR_RATE_1</td><td>UNCOMPR_RATE_0</td><td>XL_DualC_BATCH_FROM_FSM</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 36. FIFO_CTRL2 register description


<table><tr><td>STOP_ON_WTM</td><td>Sensing chain FIFO stop values memorization at threshold level. Default value: 0(0: FIFO depth is not limited;1: FIFO depth is limited to threshold level, defined inFIFO_CTRL1 (07h))</td></tr><tr><td>FIFO_COMPR_RT_EN(1)</td><td>Enables/disables compression algorithm runtime. Default value: 0(0: FIFO compression algorithm disabled;1: FIFO compression algorithm enabled)</td></tr><tr><td>ODR_CHG_EN</td><td>Enables ODR CHANGE virtual sensor to be batched in FIFO. Default value: 0(0: ODR CHANGE virtual sensor not batched in FIFO;1: ODR CHANGE virtual sensor batched in FIFO)Note: Refer to the product application note for the details regarding operating/power mode configurations, settings, turn-on/off time and on-the-fly changes.</td></tr><tr><td>UNCOMPR_RATE_[1:0]</td><td>This field configures the compression algorithm to write uncompressed data at each rate.(0: uncompressed data writing is not forced (default);1: uncompressed data every 8 batch data rate;2: uncompressed data every 16 batch data rate;3: uncompressed data every 32 batch data rate)</td></tr><tr><td>XL_DualC_BATCH_FROM_FSM</td><td>When dual-channel mode is enabled, this bit enables FSM-triggered batching in FIFO of accelerometer channel 2. Default value: 0(0: disabled; 1: enabled)</td></tr></table>


1. This bit is activated if the FIFO_COMPR_EN bit of EMB_FUNC_EN_B (05h) is set to 1. 


## FIFO_CTRL3 (09h)

FIFO control register 3 (R/W) 


Table 37. FIFO_CTRL3 register


<table><tr><td>BDR_GY_3</td><td>BDR_GY_2</td><td>BDR_GY_1</td><td>BDR_GY_0</td><td>BDR_XL_3</td><td>BDR_XL_2</td><td>BDR_XL_1</td><td>BDR_XL_0</td></tr></table>

## Table 38. FIFO_CTRL3 register description

<table><tr><td>BDR_GY_[3:0]</td><td>Selects batch data rate (write frequency in FIFO) for gyroscope data.(0000: gyroscope not batched in FIFO (default);0001: 1.875 Hz;0010: 7.5 Hz;0011: 15 Hz;0100: 30 Hz;0101: 60 Hz;0110: 120 Hz;0111: 240 Hz;1000: 480 Hz;1001: 960 Hz;1010: 1.92 kHz;1011: 3.84 kHz;1100: 7.68 kHz1101-1111: reserved)</td></tr><tr><td>BDR_XL_[3:0]</td><td>Selects batch data rate (write frequency in FIFO) for accelerometer data.(0000: accelerometer not batched in FIFO (default);0001: 1.875 Hz;0010: 7.5 Hz;0011: 15 Hz;0100: 30 Hz;0101: 60 Hz;0110: 120 Hz;0111: 240 Hz;1000: 480 Hz;1001 : 960 Hz;1010: 1.92 kHz;1011: 3.84 kHz;1100: 7.68 kHz1101-1111: reserved)</td></tr></table>

## FIFO_CTRL4 (0Ah)

## FIFO control register 4 (R/W)


Table 39. FIFO_CTRL4 register


<table><tr><td>DEC_TS_BATCH_1</td><td>DEC_TS_BATCH_0</td><td>ODR_TBATCH_1</td><td>ODR_TBATCH_0</td><td>G_EIS_FIFO_EN</td><td>FIFO_MODE_2</td><td>FIFO_MODE_1</td><td>FIFO_MODE_0</td></tr></table>


Table 40. FIFO_CTRL4 register description


<table><tr><td>DEC_TS_BATCH_[1:0]</td><td>Selects decimation for timestamp batching in FIFO. Write rate is the maximum rate between the accelerometer and gyroscope BDR divided by decimation decoder.(00: timestamp not batched in FIFO (default);01: decimation 1: max(BDR_XL[Hz],BDR_GY[Hz]) [Hz];10: decimation 8: max(BDR_XL[Hz],BDR_GY[Hz])/8 [Hz];11: decimation 32: max(BDR_XL[Hz],BDR_GY[Hz])/32 [Hz])</td></tr><tr><td>ODR_T_BATCH_[1:0]</td><td>Selects batch data rate (write frequency in FIFO) for temperature data(00: temperature not batched in FIFO (default);01: 1.875 Hz;10: 15 Hz;11: 60 Hz)</td></tr><tr><td>G_EIS_FIFO_EN</td><td>Enables FIFO batching of enhanced EIS gyroscope output values. Default value: 0(0: disabled; 1: enabled)</td></tr><tr><td>FIFO_MODE_[2:0]</td><td>FIFO mode selection(000: bypass mode: FIFO disabled (default);001: FIFO mode: stops collecting data when FIFO is full;010: continuousWTM-to-full mode: continuous mode with FIFO watermark size until trigger is deasserted, then data are stored in FIFO until the buffer is full;011: continuous-to-FIFO mode: continuous mode until trigger is deasserted, then FIFO mode;100: bypass-to-continuous mode: bypass mode until trigger is deasserted, then continuous mode;101: reserved;110: continuous mode: if the FIFO is full, the new sample overwrites the older one;111: bypass-to-FIFO mode: bypass mode until trigger is deasserted, then FIFO mode.)</td></tr></table>

## COUNTER_BDR_REG1 (0Bh)

Counter batch data rate register 1 (R/W) 


Table 41. COUNTER_BDR_REG1 register


<table><tr><td><eq>0^{(1)}</eq></td><td>TRIG_COUNTER_BDR_1</td><td>TRIG_COUNTER_BDR_0</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>CNT_BDR_TH_9</td><td>CNT_BDR_TH_8</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 42. COUNTER_BDR_REG1 register description


<table><tr><td>TRIG_COUNTER_BDR_[1:0]</td><td>Selects the trigger for the internal counter of batch events between the accelerometer, gyroscope and EIS gyroscope.(00: accelerometer batch event;01: gyroscope batch event;10 – 11: gyroscope EIS batch event)</td></tr><tr><td>CNT_BDR_TH_[9:8]</td><td>In conjunction with CNT_BDR_TH_[7:0] in COUNTER_BDR_REG2 (0Ch), sets the threshold for the internal counter of batch events. When this counter reaches the threshold, the counter is reset and the COUNTER_BDR_IA flag in FIFO_STATUS2 (1Ch) is set to 1.</td></tr></table>

## COUNTER_BDR_REG2 (0Ch)

Counter batch data rate register 2 (R/W) 


Table 43. COUNTER_BDR_REG2 register


<table><tr><td>CNT_BDR_TH_7</td><td>CNT_BDR_TH_6</td><td>CNT_BDR_TH_5</td><td>CNT_BDR_TH_4</td><td>CNT_BDR_TH_3</td><td>CNT_BDR_TH_2</td><td>CNT_BDR_TH_1</td><td>CNT_BDR_TH_0</td></tr></table>

## Table 44. COUNTER_BDR_REG2 register description

<table><tr><td>CNT_BDR_TH_[7:0]</td><td>In conjunction with CNT_BDR_TH_[9:8] in COUNTER_BDR_REG1 (0Bh), sets the threshold for the internal counter of batch events. When this counter reaches the threshold, the counter is reset and the COUNTER_BDR_IA flag in FIFO_STATUS2 (1Ch) is set to 1.</td></tr></table>

## INT1_CTRL (0Dh)

INT1 pin control register (R/W) 

Each bit in this register enables a signal to be carried over INT1 when the MIPI ${ \mathsf { I } } 3 { \mathsf { C } } ^ { \circledast }$ dynamic address is not assigned (I²C or SPI is used). Some bits can be also used to trigger an IBI (in-band interrupt) when the MIPI ${ \mathsf { I } } 3 { \mathsf { C } } ^ { \circledast }$ interface is used. The output of the pin is the OR combination of the signals selected here and in MD1_CFG (5Eh). 


Table 45. INT1_CTRL register


<table><tr><td><eq>0^{(1)}</eq></td><td>INT1_CNT_BDR</td><td>INT1_FIFO_FULL</td><td>INT1_FIFO_OVR</td><td>INT1_FIFO_TH</td><td><eq>0^{(1)}</eq></td><td>INT1_DRDY_G</td><td>INT1_DRDY_XL</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 46. INT1_CTRL register description


<table><tr><td>INT1_CNT_BDR</td><td>Enables COUNTER_BDR_IA interrupt on INT1 pin. Default value: 0</td></tr><tr><td>INT1_FIFO_FULL</td><td>Enables FIFO full flag interrupt on INT1 pin. It can be also used to trigger an IBI when the MIPI I3C® interface is used. Default value: 0</td></tr><tr><td>INT1_FIFO_OVR</td><td>Enables FIFO overrun interrupt on INT1 pin. It can be also used to trigger an IBI when the MIPI I3C® interface is used. Default value: 0</td></tr><tr><td>INT1_FIFO_TH</td><td>Enables FIFO threshold interrupt on INT1 pin. It can be also used to trigger an IBI when the MIPI I3C® interface is used. Default value: 0</td></tr><tr><td>INT1_DRDY_G</td><td>Enables gyroscope data-ready interrupt on INT1 pin. It can be also used to trigger an IBI when the MIPI I3C® interface is used. Default value: 0</td></tr><tr><td>INT1_DRDY_XL</td><td>Enables accelerometer data-ready interrupt on INT1 pin. It can be also used to trigger an IBI when the MIPI I3C® interface is used. Default value: 0</td></tr></table>

## INT2_CTRL (0Eh)

## INT2 pin control register (R/W)

Each bit in this register enables a signal to be carried over INT2 when the MIPI I3C<sup>®</sup> dynamic address is not assigned (I²C or SPI is used). Some bits can be also used to trigger an IBI when the MIPI I3C<sup>®</sup> interface is used. The output of the pin is the OR combination of the signals selected here and in MD2_CFG (5Fh). 


Table 47. INT2_CTRL register


<table><tr><td>INT2_EMB_FUNC_ENDOP</td><td>INT2_CNT_BDR</td><td>INT2_FIFO_FULL</td><td>INT2_FIFO_OVR</td><td>INT2_FIFO_TH</td><td>INT2_DRDY_G_EIS</td><td>INT2_DRDY_G</td><td>INT2_DRDY_XL</td></tr></table>


Table 48. INT2_CTRL register description


<table><tr><td>INT2_EMB_FUNC_ENDOP</td><td>Enables routing the embedded functions end of operations signal to the INT2 pin. Default value: 0</td></tr><tr><td>INT2_CNT_BDR</td><td>Enables COUNTER_BDR_IA interrupt on INT2. Default value: 0</td></tr><tr><td>INT2_FIFO_FULL</td><td>Enables FIFO full flag interrupt on INT2 pin. Default value: 0</td></tr><tr><td>INT2_FIFO_OVR</td><td>Enables FIFO overrun interrupt on INT2 pin. Default value: 0</td></tr><tr><td>INT2_FIFO_TH</td><td>Enables FIFO threshold interrupt on INT2 pin. Default value: 0</td></tr><tr><td>INT2_DRDY_G_EIS</td><td>Enables gyroscope EIS data-ready interrupt on INT2 pin. Default value: 0</td></tr><tr><td>INT2_DRDY_G</td><td>Gyroscope data-ready interrupt on INT2 pin. Default value: 0</td></tr><tr><td>INT2_DRDY_XL</td><td>Accelerometer data-ready interrupt on INT2 pin. Default value: 0</td></tr></table>

## 9.13 WHO_AM_I (0Fh)

WHO_AM_I register (R). This is a read-only register. Its value is fixed at 70h. 


Table 49. WhoAmI register


<table><tr><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

## CTRL1 (10h)

Accelerometer control register 1 (R/W) 


Table 50. CTRL1 register


<table><tr><td><eq>0^{(1)}</eq></td><td>OP_MODE_XL_2</td><td>OP_MODE_XL_1</td><td>OP_MODE_XL_0</td><td>ODR_XL_3</td><td>ODR_XL_2</td><td>ODR_XL_1</td><td>ODR_XL_0</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 51. CTRL1 register description


<table><tr><td>OP_MODE_XL_[2:0]</td><td>Accelerometer operating mode selection.(000: high-performance mode (default);001: high-accuracy ODR mode;010: reserved;011: ODR-triggered mode;100: low-power mode 1 (2 mean);101: low-power mode 2 (4 mean);110: low-power mode 3 (8 mean);111: normal mode)</td></tr><tr><td>ODR_XL_[3:0]</td><td>Accelerometer ODR selection (see Table 52)</td></tr></table>


Table 52. Accelerometer ODR selection


<table><tr><td>ODR_XL_3</td><td>ODR_XL_2</td><td>ODR_XL_1</td><td>ODR_XL_0</td><td>ODR selection [Hz]</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>Power-down (default)</td></tr><tr><td>0</td><td>0</td><td>0</td><td>1</td><td>1.875 Hz (low-power mode)</td></tr><tr><td>0</td><td>0</td><td>1</td><td>0</td><td>7.5 Hz (high-performance, normal mode)</td></tr><tr><td>0</td><td>0</td><td>1</td><td>1</td><td>15 Hz (low-power, high-performance, normal mode)</td></tr><tr><td>0</td><td>1</td><td>0</td><td>0</td><td>30 Hz (low-power, high-performance, normal mode)</td></tr><tr><td>0</td><td>1</td><td>0</td><td>1</td><td>60 Hz (low-power, high-performance, normal mode)</td></tr><tr><td>0</td><td>1</td><td>1</td><td>0</td><td>120 Hz (low-power, high-performance, normal mode)</td></tr><tr><td>0</td><td>1</td><td>1</td><td>1</td><td>240 Hz (low-power, high-performance, normal mode)</td></tr><tr><td>1</td><td>0</td><td>0</td><td>0</td><td>480 Hz (high-performance, normal mode)</td></tr><tr><td>1</td><td>0</td><td>0</td><td>1</td><td>960 Hz (high-performance, normal mode)</td></tr><tr><td>1</td><td>0</td><td>1</td><td>0</td><td>1.92 kHz (high-performance, normal mode)</td></tr><tr><td>1</td><td>0</td><td>1</td><td>1</td><td>3.84 kHz (high-performance mode)</td></tr><tr><td>1</td><td>1</td><td>0</td><td>0</td><td>7.68 kHz (high-performance mode)</td></tr><tr><td colspan="4">Others</td><td>Reserved</td></tr></table>

## CTRL2 (11h)

Gyroscope control register 2 (R/W) 


Table 53. CTRL2 register


<table><tr><td><eq>0^{(1)}</eq></td><td>OP_MODE_G_2</td><td>OP_MODE_G_1</td><td>OP_MODE_G_0</td><td>ODR_G_3</td><td>ODR_G_2</td><td>ODR_G_1</td><td>ODR_G_0</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 54. CTRL2 register description


<table><tr><td>OP_MODE_G_[2:0]</td><td>Gyroscope operating mode selection.(000: high-performance mode (default);001: high-accuracy ODR mode;010: reserved;011: ODR-triggered mode;100: sleep mode;101: low-power mode;110-111: reserved)</td></tr><tr><td>ODR_G_[3:0]</td><td>Gyroscope output data rate selection.(See Table 55)</td></tr></table>


Table 55. Gyroscope ODR selection


<table><tr><td>ODR_G_3</td><td>ODR_G_2</td><td>ODR_G_1</td><td>ODR_G_0</td><td>ODR [Hz]</td></tr><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>Power-down (default)</td></tr><tr><td>0</td><td>0</td><td>1</td><td>0</td><td>7.5 Hz (low-power, high-performance mode)</td></tr><tr><td>0</td><td>0</td><td>1</td><td>1</td><td>15 Hz (low-power, high-performance mode)</td></tr><tr><td>0</td><td>1</td><td>0</td><td>0</td><td>30 Hz (low-power, high-performance mode)</td></tr><tr><td>0</td><td>1</td><td>0</td><td>1</td><td>60 Hz (low-power, high-performance mode)</td></tr><tr><td>0</td><td>1</td><td>1</td><td>0</td><td>120 Hz (low-power, high-performance mode)</td></tr><tr><td>0</td><td>1</td><td>1</td><td>1</td><td>240 Hz (low-power, high-performance mode)</td></tr><tr><td>1</td><td>0</td><td>0</td><td>0</td><td>480 Hz (high-performance mode)</td></tr><tr><td>1</td><td>0</td><td>0</td><td>1</td><td>960 Hz (high-performance mode)</td></tr><tr><td>1</td><td>0</td><td>1</td><td>0</td><td>1.92 kHz (high-performance mode)</td></tr><tr><td>1</td><td>0</td><td>1</td><td>1</td><td>3.84 kHz (high-performance mode)</td></tr><tr><td>1</td><td>1</td><td>0</td><td>0</td><td>7.68 kHz (high-performance mode)</td></tr><tr><td colspan="4">Others</td><td>Reserved</td></tr></table>

## CTRL3 (12h)

Control register 3 (R/W) 


Table 56. CTRL3 register


<table><tr><td>BOOT</td><td>BDU</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>IF_INC</td><td><eq>0^{(1)}</eq></td><td>SW_RESET</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 57. CTRL3 register description


<table><tr><td>BOOT</td><td>Reboots memory content. This bit is automatically cleared. Default value: 0(0: normal mode; 1: reboot memory content)</td></tr><tr><td>BDU</td><td>Block data update. Default value: 1(0: continuous update;1: output registers are not updated until LSB and MSB have been read)</td></tr><tr><td>IF_INC</td><td>Register address automatically incremented during a multiple byte access with a serial interface (I2C, MIPI I3C, or SPI). Default value: 1(0: disabled; 1: enabled)</td></tr><tr><td>SW_RESET</td><td>Software reset, resets all control registers to their default value. This bit is automatically cleared. Default value: 0(0: normal mode; 1: reset device)</td></tr></table>

## CTRL4 (13h)

Control register 4 (R/W) 


Table 58. CTRL4 register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>INT2_on_INT1</td><td>DRDY_MASK</td><td>INT2_DRDY_TEMP</td><td>DRDY_PULSED</td><td>INT2_IN_LH</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 59. CTRL4 register description


<table><tr><td>INT2_on_INT1</td><td>Enables routing the embedded functions interrupt signals to the INT1 pin. Default value: 0The corresponding bits in the INT2 control registers need to be enabled.These interrupts are in OR with those enabled on the INT1 pin.They are not fed to the INT2 pin.The movable interrupts are:- INT2_DRDY_G_EIS and INT2_EMB_FUNC_ENDOP, enabled through INT2_CTRL (0Eh)- INT2_TIMESTAMP enabled through MD2_CFG (5Fh)- INT2_DRDY_TEMP enabled through CTRL4 (13h)- INT2_DRDY_AH_QVAR enabled through Section 9.20</td></tr><tr><td>DRDY_MASK</td><td>Enables / masks data-ready signal. Default value: 0(0: disabled;1: masks DRDY signals (both accelerometer and gyroscope) until filter settling ends (accelerometer and gyroscope independently masked))Note: Refer to the product application note for the details regarding operating/power mode configurations, settings, turn-on/off time and on-the-fly changes.</td></tr><tr><td>INT2_DRDY_TEMP</td><td>Enables temperature sensor data-ready interrupt on the INT2 pin. It can be also used to trigger an IBI when the MIPI I3C® interface is used and INT2_ON_INT1 = 1 in CTRL4_C (13h). Default value: 0(0: disabled; 1: enabled)</td></tr><tr><td>DRDY_PULSED</td><td>Enables pulsed data-ready mode. Default value: 0(0: data-ready latched mode (returns to 0 only after the higher part of the associated output register has been read);1: data-ready pulsed mode (the data-ready pulses are 65 μs long))</td></tr><tr><td>INT2_IN_LH</td><td>Set to 1 in order to change the polarity of the INT2 pin input trigger for DEN or embedded functions. Default value: 0(0: trigger for DEN and embedded functions pin is active low;1: trigger for DEN and embedded functions pin is active high)</td></tr></table>

## CTRL5 (14h)

Control register 5 (R/W) 


Table 60. CTRL5 register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>BUS_ACT_SEL_1</td><td>BUS_ACT_SEL_0</td><td>INT_EN_I3C</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 61. CTRL5 register description


<table><tr><td>BUS_ACT_SEL_[1:0]</td><td>Bus available time selection for IBI (in-band interrupt):00: 2 μs;01: 50 μs (default);10: 1 ms;11: 25 ms)</td></tr><tr><td>INT_EN_I3C</td><td>Enables INT pin when I3C is enabled. Default value: 0(0: disabled; 1: enabled)</td></tr></table>

## CTRL6 (15h)

Control register 6 (R/W) 


Table 62. CTRL6 register


<table><tr><td><eq>0^{(1)}</eq></td><td>LPF1_G_BW_2</td><td>LPF1_G_BW_1</td><td>LPF1_G_BW_0</td><td>FS_G_3</td><td>FS_G_2</td><td>FS_G_1</td><td>FS_G_0</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 63. CTRL6 register description


<table><tr><td>LPF1_G_BW_[2:0]</td><td>Gyroscope low-pass filter (LPF1) bandwidth selectionTable 64 shows the selectable bandwidth values (available if OIS and/or EIS are disabled).</td></tr><tr><td>FS_G_[3:0]</td><td>Gyroscope UI chain full-scale selection:(0000: ±125 dps (default);0001: ±250 dps;0010: ±500 dps;0011: ±1000 dps;0100: ±2000 dps;<eq>1100</eq>: <eq>\pm 4000</eq> <eq>\text{dps}^{(1)}</eq>Others: reserved)</td></tr></table>


1. When FS = ±4000 dps is selected, the gyroscope OIS chain must be disabled (OIS_G_EN bit of UI_CTRL1_OIS (70h) / SPI2_CTRL1_OIS (70h) must be set to 0). 



Table 64. Gyroscope LPF1 + LPF2 bandwidth selection


<table><tr><td>LPF1_G_BW_[2:0]</td><td>60 Hz</td><td>120 Hz</td><td>240 Hz</td><td>480 Hz</td><td>960 Hz</td><td>1.92 kHz</td><td>3.84 kHz</td><td>7.68 kHz</td></tr><tr><td>000</td><td>24.6</td><td>49.4</td><td>96</td><td>175</td><td>241</td><td>273</td><td>280</td><td>281</td></tr><tr><td>001</td><td>24.6</td><td>49.4</td><td>96</td><td>157</td><td>195</td><td>210</td><td>213</td><td>213</td></tr><tr><td>010</td><td>24.6</td><td>49.4</td><td>96</td><td>131</td><td>149</td><td>155</td><td>156</td><td>156</td></tr><tr><td>011</td><td>24.6</td><td>49.4</td><td>96</td><td>188</td><td>310</td><td>387</td><td>403</td><td>407</td></tr><tr><td>100</td><td>24.6</td><td>49.4</td><td>78.4</td><td>94</td><td>100</td><td>101</td><td>102</td><td>102</td></tr><tr><td>101</td><td>24.6</td><td>42.6</td><td>53</td><td>56.7</td><td>57.9</td><td>58.2</td><td>58.3</td><td>58</td></tr><tr><td>110</td><td>18.0</td><td>24.2</td><td>27.3</td><td>28.4</td><td>28.7</td><td>28.8</td><td>28.8</td><td>28.8</td></tr><tr><td>111</td><td>12.1</td><td>13.6</td><td>14.2</td><td>14.3</td><td>14.4</td><td>14.4</td><td>14.4</td><td>14.4</td></tr></table>

## 9.20

## CTRL7 (16h)

Control register 7 (R/W) 


Table 65. CTRL7 register


<table><tr><td>AH_QVAR_EN</td><td>INT2_DRDY_AH_QVAR</td><td>AH_QVAR_C_ZIN_1</td><td>AH_QVAR_C_ZIN_0</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>LPF1_G_EN</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 66. CTRL7 register description


<table><tr><td>AH_QVAR_EN</td><td>Enables the analog hub and Qvar chain. When this bit is set to 1, the analog hub and Qvar buffers are connected to the SDx/AH1/Qvar1 and SCx/AH2/Qvar2 pins. Before setting this bit to 1, the accelerometer and gyroscope sensors have to be configured in power-down mode. Default value: 0(0: disabled; 1: enabled)</td></tr><tr><td>INT2_DRDY_AH_QVAR</td><td>Analog hub and Qvar data-ready interrupt on the INT2 pin. Default value: 0(0: disabled; 1: enabled)</td></tr><tr><td>AH_QVAR_C_ZIN_[1:0]</td><td>Configures the equivalent input impedance of the analog hub and Qvar buffers.(00: 2.4 GΩ (default);01: 730 MΩ;10: 300 MΩ;11: 235 MΩ)</td></tr><tr><td>LPF1_G_EN</td><td>Enables the gyroscope digital LPF1 filter. If the OIS chain is disabled, the bandwidth can be selected through LPF1_G_BW_[2:0] in CTRL6 (15h)</td></tr></table>

## CTRL8 (17h)

Control register 8 (R/W) 


Table 67. CTRL8 register


<table><tr><td>HP_LPF2_XL_BW_2</td><td>HP_LPF2_XL_BW_1</td><td>HP_LPF2_XL_BW_0</td><td><eq>0^{(1)}</eq></td><td>XL_DualC_EN</td><td><eq>0^{(1)}</eq></td><td>FS_XL_1</td><td>FS_XL_0</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 68. CTRL8 register description


<table><tr><td>HP_LPF2_XL_BW_[2:0]</td><td>Accelerometer LPF2 and HP filter configuration and cutoff setting. Refer to Table 69.</td></tr><tr><td>XL_DualC_EN</td><td>Enables dual-channel mode. When this bit is set to 1, data with the maximum full scale are sent to the output registers at addresses 34h to 39h. The UI processing chain is used. Default value: 0(0: disabled; 1: enabled)</td></tr><tr><td>FS_XL_[1:0]</td><td>Accelerometer full-scale selection:(00: ±2 g;01: ±4 g;10: ±8 g;11: ±16 g)</td></tr></table>


Table 69. Accelerometer bandwidth configurations


<table><tr><td>Filter type</td><td>HP_SLOPE_XL_EN</td><td>LPF2_XL_EN</td><td>HP_LPF2_XL_BW_[2:0]</td><td>Bandwidth</td></tr><tr><td rowspan="9">Low pass</td><td rowspan="9">0</td><td>0</td><td>-</td><td><eq>ODR/2^{(1)}</eq></td></tr><tr><td rowspan="8">1</td><td>000</td><td>ODR/4</td></tr><tr><td>001</td><td>ODR/10</td></tr><tr><td>010</td><td>ODR/20</td></tr><tr><td>011</td><td>ODR/45</td></tr><tr><td>100</td><td>ODR/100</td></tr><tr><td>101</td><td>ODR/200</td></tr><tr><td>110</td><td>ODR/400</td></tr><tr><td>111</td><td>ODR/800</td></tr><tr><td rowspan="8">High pass</td><td rowspan="8">1</td><td rowspan="8">-</td><td>000</td><td>SLOPE (ODR/4)</td></tr><tr><td>001</td><td>ODR/10</td></tr><tr><td>010</td><td>ODR/20</td></tr><tr><td>011</td><td>ODR/45</td></tr><tr><td>100</td><td>ODR/100</td></tr><tr><td>101</td><td>ODR/200</td></tr><tr><td>110</td><td>ODR/400</td></tr><tr><td>I11</td><td>ODR/800</td></tr></table>


1. This value is ODR/2 when the accelerometer is in high-performance mode, high-accuracy ODR mode and normal mode. It is equal to 2300 Hz when the accelerometer is in low-power mode 1 (2 mean), 912 Hz in low-power mode 2 (4 mean) and 431 Hz in low-power mode 3 (8 mean). 


## CTRL9 (18h)

Control register 9 (R/W) 


Table 70. CTRL9 register


<table><tr><td><eq>0^{(1)}</eq></td><td>HP_REF_MODE_XL</td><td>XL_FASTSET TL_MODE</td><td>HP_SLOPE_XL_EN</td><td>LPF2_XL_EN</td><td><eq>0^{(1)}</eq></td><td>USR_OFF_W</td><td>USR_OFF_ON_OUT</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 71. CTRL9 register description


<table><tr><td>HP_REF_MODE_XL</td><td>Enables accelerometer high-pass filter reference mode (valid for high-pass path - HP_SLOPE_XL_EN bit must be 1). Default value: 0(0: disabled, 1: enabled)<eq>^{(1)}</eq></td></tr><tr><td>XL_FASTSETTL_MODE</td><td>Enables accelerometer LPF2 and HPF fast-settling mode. The filter sets the first sample after writing this bit. Active only during device exit from power-down mode. Default value: 0(0: disabled, 1: enabled)</td></tr><tr><td>HP_SLOPE_XL_EN</td><td>Accelerometer slope filter / high-pass filter selection. Refer to Figure 32. Default value: 0(0: low-pass filter path selected;1: high-pass filter path selected)</td></tr><tr><td>LPF2_XL_EN</td><td>Accelerometer high-resolution selection. Refer to Figure 32. Default value: 0(0: output from first stage digital filtering selected;1: output from LPF2 second filtering stage selected)</td></tr><tr><td>USR_OFF_W</td><td>Weight of XL user offset bits of registers X_OFS_USR (73h), Y_OFS_USR (74h), Z_OFS_USR (75h). Default value: 0(0: <eq>2^{-10}</eq> g/LSB;1: <eq>2^{-6}</eq> g/LSB)</td></tr><tr><td>USR_OFF_ON_OUT</td><td>Enables accelerometer user offset correction block; it is valid for the low-pass path. Refer to Figure 32. Default value: 0(0: accelerometer user offset correction block bypassed;1: accelerometer user offset correction block enabled)</td></tr></table>


1. When enabled, the first output data has to be discarded. 



Figure 32. Accelerometer block diagram


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/fb8e3c99a35091aa4d4290d0b6cba660ebb613b777d41b8192770466e85a951b.jpg)



1. The cutoff value of the LPF1 output is ODR/2 when the accelerometer is in high-performance mode, high-accuracy ODR mode or normal mode. This value is equal to 2300 Hz when the accelerometer is in low-power mode 1 (2 mean), 912 Hz in low-power mode 2 (4 mean) or 431 Hz in low-power mode 3 (8 mean).


CTRL10 (19h) 

Control register 10 (R/W) 


Table 72. CTRL10 register


<table><tr><td><eq>0^{(1)}</eq></td><td>EMB_FUNC_DEBUG</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>ST_G_1</td><td>ST_G_0</td><td>ST_XL_1</td><td>ST_XL_0</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 73. CTRL10 register description


<table><tr><td>EMB_FUNC_DEBUG</td><td>Enables debug mode for the embedded functions.(0: disabled; 1: enabled)</td></tr><tr><td>ST_G_[1:0]</td><td>Gyroscope self-test selection(00: normal mode (default);01: positive sign self-test;10: negative sign self-test;11: reserved)</td></tr><tr><td>ST_XL_[1:0]</td><td>Accelerometer self-test selection(00: normal mode (default);01: positive sign self-test;10: negative sign self-test;11: reserved)</td></tr></table>

## 9.24 CTRL_STATUS (1Ah)

(R) 


Table 74. CTRL_STATUS register


<table><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>FSM_WR_CTRL_STATUS</td><td>-</td><td>0</td></tr></table>


Table 75. CTRL_STATUS register description


<table><tr><td>FSM_WR_CTRL_STATUS</td><td>This flag indicates the current controller of the device configuration registers. This flag must be used as an acknowledge flag when the value of the FSM_WR_CTRL_EN bit in the FUNC_CFG_ACCESS (01h) register is changed. Default value: 0(0: all registers and configurations are writable from the standard interface;1: some registers and configurations are under FSM control and are in read-only mode from the standard interface).</td></tr></table>

## FIFO_STATUS1 (1Bh)

FIFO status register 1 (R) 


Table 76. FIFO_STATUS1 register


<table><tr><td>DIFF_FIFO_7</td><td>DIFF_FIFO_6</td><td>DIFF_FIFO_5</td><td>DIFF_FIFO_4</td><td>DIFF_FIFO_3</td><td>DIFF_FIFO_2</td><td>DIFF_FIFO_1</td><td>DIFF_FIFO_0</td></tr></table>


Table 77. FIFO_STATUS1 register description


<table><tr><td>DIFF_FIFO_[7:0]</td><td>Number of unread sensor data (TAG + 6 bytes) stored in FIFOIn conjunction with DIFF_FIFO_8 inFIFO_STATUS2(1Ch).</td></tr></table>

## FIFO_STATUS2 (1Ch)

FIFO status register 2 (R) 


Table 78. FIFO_STATUS2 register


<table><tr><td>FIFO_WTM_IA</td><td>FIFO_OVR_IA</td><td>FIFO_FULL_IA</td><td>COUNTER_BDR_IA</td><td>FIFO_OVR_LATCHED</td><td>0</td><td>0</td><td>DIFF_FIFO_8</td></tr></table>


Table 79. FIFO_STATUS2 register description


<table><tr><td>FIFO_WTM_IA</td><td>FIFO watermark status. Default value: 0(0: FIFO filling is lower than WTM;1: FIFO filling is equal to or greater than WTM)Watermark is set through bits WTM[7:0] inFIFO_CTRL2 (08h) andFIFO_CTRL1 (07h).</td></tr><tr><td>FIFO_OVR_IA</td><td>FIFO overrun status. Default value: 0(0: FIFO is not completely filled; 1: FIFO is completely filled)</td></tr><tr><td>FIFO_FULL_IA</td><td>Smart FIFO full status. Default value: 0(0: FIFO is not full; 1: FIFO will be full at the next ODR)</td></tr><tr><td>COUNTER_BDR_IA</td><td>Counter BDR reaches the CNT_BDR_TH_[10:0] threshold set inCOUNTER_BDR_REG1 (0Bh) andCOUNTER_BDR_REG2 (0Ch). Default value: 0This bit is reset when these registers are read.</td></tr><tr><td>FIFO_OVR_LATCHED</td><td>Latched FIFO overrun status. Default value: 0This bit is reset when this register is read.</td></tr><tr><td>DIFF_FIFO_8</td><td>Number of unread sensor data (TAG + 6 bytes) stored in FIFO. Default value: 00In conjunction with DIFF_FIFO[7:0] inFIFO_STATUS1 (1Bh)</td></tr></table>

## ALL_INT_SRC (1Dh)

Source register for all interrupts (R) 


Table 80. ALL_INT_SRC register


<table><tr><td>EMB_FUNC_IA</td><td>SHUB_IA</td><td>SLEEP_CHANGE_IA</td><td>D6D_IA</td><td>0</td><td>TAP_IA</td><td>WU_IA</td><td>FF_IA</td></tr></table>


Table 81. ALL_INT_SRC register description


<table><tr><td>EMB_FUNC_IA</td><td>Embedded functions interrupt status. Default value: 0(0: embedded functions event not detected;1: embedded functions event detected)</td></tr><tr><td>SHUB_IA</td><td>Sensor hub (I2C master) interrupt status. Default value: 0(0: sensor hub interrupt not generated;1: sensor hub interrupt generated)</td></tr><tr><td>SLEEP_CHANGE_IA</td><td>Detects change event in activity/inactivity status. Default value: 0(0: change status not detected; 1: change status detected)</td></tr><tr><td>D6D_IA</td><td>Interrupt active for change in position of portrait, landscape, face-up, face-down. Default value: 0(0: change in position not detected; 1: change in position detected)</td></tr><tr><td>TAP_IA</td><td>Single or double-tap event detection status depending on SINGLE_DOUBLE_TAP_bit value (see WAKE_UP_THS (5Bh) register). Default value: 0(0: tap event not detected; 1: tap event detected)</td></tr><tr><td>WU_IA</td><td>Wake-up event status. Default value: 0(0: event not detected, 1: event detected)</td></tr><tr><td>FF_IA</td><td>Free-fall event status. Default value: 0(0: event not detected, 1: event detected)</td></tr></table>

## STATUS_REG (1Eh)

The STATUS_REG register is read by the primary interface SPI/I²C & MIPI ${ \mathsf { I } } 3 { \mathsf { C } } ^ { \circledast } \left( { \mathsf { R } } \right)$ 


Table 82. STATUS_REG register


<table><tr><td>TIMESTAMP_ENDCOUNT</td><td>0</td><td>OIS_DRDY</td><td>GDA_EIS</td><td>AH_QVARDA</td><td>TDA</td><td>GDA</td><td>XLDA</td></tr></table>

## Table 83. STATUS_REG register description

<table><tr><td>TIMESTAMP_ENDCOUNT</td><td>Alerts timestamp overflow within 5.6 ms</td></tr><tr><td>OIS_DRDY</td><td>Accelerometer OIS or gyroscope OIS new output data available. Default value: 0(0: no set of data (accelerometer or gyroscope) available on OIS chain;1: a new set of data (accelerometer or gyroscope) is available on OIS chain)</td></tr><tr><td>GDA_EIS</td><td>Enhanced EIS gyroscope new data available. Default value: 0(0: no set of data available at gyroscope output;1: a new set of data is available at gyroscope output)</td></tr><tr><td>AH_QVARDA</td><td>Analog hub or Qvar new data available. Default value: 0(0: no set of data available at the analog hub or Qvar data output;1: a new set of data is available at the analog hub or Qvar data output)</td></tr><tr><td>TDA</td><td>Temperature new data available. Default: 0(0: no set of data is available at temperature sensor output;1: a new set of data is available at temperature sensor output)</td></tr><tr><td>GDA</td><td>Gyroscope new data available. Default value: 0(0: no set of data available at gyroscope output;1: a new set of data is available at gyroscope output)</td></tr><tr><td>XLDA</td><td>Accelerometer new data available. Default value: 0(0: no set of data available at accelerometer output;1: a new set of data is available at accelerometer output)</td></tr></table>

## OUT_TEMP_L (20h), OUT_TEMP_H (21h)

Temperature data output register (R). L and H registers together express a 16-bit word in two’s complement. 


Table 84. OUT_TEMP_L register


<table><tr><td>Temp7</td><td>Temp6</td><td>Temp5</td><td>Temp4</td><td>Temp3</td><td>Temp2</td><td>Temp1</td><td>Temp0</td></tr></table>


Table 85. OUT_TEMP_H register


<table><tr><td>Temp15</td><td>Temp14</td><td>Temp13</td><td>Temp12</td><td>Temp11</td><td>Temp10</td><td>Temp9</td><td>Temp8</td></tr></table>


Table 86. OUT_TEMP register description


<table><tr><td>Temp[15:0]</td><td>Temperature sensor output dataThe value is expressed in two&#x27;s complement.</td></tr></table>

## OUTX_L_G (22h) and OUTX_H_G (23h)

Angular rate sensor pitch axis (X) angular rate output register (R). The value is expressed as a 16-bit word in two’s complement. 

Data are according to the full-scale (CTRL6 (15h)) and ODR settings (CTRL2 (11h)) of the gyroscope user interface. 


Table 87. OUTX_L_G register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 88. OUTX_H_G register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>

## Table 89. OUTX_G register description

<table><tr><td>D[15:0]</td><td>Gyroscope UI chain pitch axis (X) angular rate output value</td></tr></table>

## OUTY_L_G (24h) and OUTY_H_G (25h)

Angular rate sensor roll axis (Y) angular rate output register (R). The value is expressed as a 16-bit word in two’s complement. 

Data are according to the full-scale (CTRL6 (15h)) and ODR settings (CTRL2 (11h)) of the gyroscope user interface. 


Table 90. OUTY_L_G register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 91. OUTY_H_G register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>


Table 92. OUTY_G register description


<table><tr><td>D[15:0]</td><td>Gyroscope UI chain roll axis (Y) angular rate output value</td></tr></table>

## OUTZ_L_G (26h) and OUTZ_H_G (27h)

Angular rate sensor yaw axis (Z) angular rate output register (R). The value is expressed as a 16-bit word in two’s complement. 

Data are according to the full-scale (CTRL6 (15h)) and ODR settings (CTRL2 (11h)) of the gyroscope user interface. 


Table 93. OUTZ_L_G register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 94. OUTZ_H_G register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>

## Table 95. OUTZ_H_G register description

<table><tr><td>D[15:0]</td><td>Gyroscope UI chain yaw axis (Z) angular rate output value</td></tr></table>

## OUTX_L_A (28h) and OUTX_H_A (29h)

Linear acceleration sensor X-axis output register (R). The value is expressed as a 16-bit word in two’s complement. 

Data are according to the full-scale (CTRL8 (17h)) and ODR settings (CTRL1 (10h)) of the accelerometer user interface. 


Table 96. OUTX_L_A register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 97. OUTX_H_A register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>

## Table 98. OUTX_A register description

<table><tr><td>D[15:0]</td><td>Accelerometer UI chain X-axis linear acceleration output value</td></tr></table>

## OUTY_L_A (2Ah) and OUTY_H_A (2Bh)

Linear acceleration sensor Y-axis output register (R). The value is expressed as a 16-bit word in two’s complement. 

Data are according to the full-scale (CTRL8 (17h)) and ODR settings (CTRL1 (10h)) of the accelerometer user interface. 


Table 99. OUTY_L_A register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 100. OUTY_H_A register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>

## Table 101. OUTY_A register description

<table><tr><td>D[15:0]</td><td>Accelerometer UI chain Y-axis linear acceleration output value</td></tr></table>

## OUTZ_L_A (2Ch) and OUTZ_H_A (2Dh)

Linear acceleration sensor Z-axis output register (R). The value is expressed as a 16-bit word in two’s complement. 

Data are according to the full-scale (CTRL8 (17h)) and ODR settings (CTRL1 (10h)) of the accelerometer user interface. 


Table 102. OUTZ_L_A register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 103. OUTZ_H_A register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>


Table 104. OUTZ_A register description


<table><tr><td>D[15:0]</td><td>Accelerometer UI chain Z-axis linear acceleration output value</td></tr></table>

## UI_OUTX_L_G_OIS_EIS (2Eh) and UI_OUTX_H_G_OIS_EIS (2Fh)

Angular rate sensor pitch axis (X) angular rate output register (R). The value is expressed as a 16-bit word in two’s complement. 

Data are according to the gyroscope full-scale and ODR settings of the OIS gyroscope or the EIS gyroscope channel. 


Table 105. UI_OUTX_L_G_OIS_EIS register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 106. UI_OUTX_H_G_OIS_EIS register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>

## Table 107. UI_OUTX_G_OIS_EIS register description

<table><tr><td>D[15:0]</td><td>Gyroscope pitch axis OIS/EIS output expressed in two&#x27;s complement</td></tr></table>

## UI_OUTY_L_G_OIS_EIS (30h) and UI_OUTY_H_G_OIS_EIS (31h)

Angular rate sensor roll axis (Y) angular rate output register (R). The value is expressed as a 16-bit word in two’s complement. 

Data are according to the gyroscope full-scale and ODR settings of the OIS gyroscope or the EIS gyroscope channel. 


Table 108. UI_OUTY_L_G_OIS_EIS register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 109. UI_OUTY_H_G_OIS_EIS register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>


Table 110. UI_OUTY_G_OIS_EIS register description


<table><tr><td>D[15:0]</td><td>Gyroscope roll axis OIS/EIS output expressed in two&#x27;s complement</td></tr></table>

## UI_OUTZ_L_G_OIS_EIS (32h) and UI_OUTZ_H_G_OIS_EIS (33h)

Angular rate sensor yaw axis (Z) angular rate output register (R). The value is expressed as a 16-bit word in two’s complement. 

Data are according to the gyroscope full-scale and ODR settings of the OIS gyroscope or the EIS gyroscope channel. 


Table 111. UI_OUTZ_L_G_OIS_EIS register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 112. UI_OUTZ_H_G_OIS_EIS register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>


Table 113. UI_OUTZ_G_OIS_EIS register description


<table><tr><td>D[15:0]</td><td>Gyroscope yaw axis OIS/EIS output expressed in two&#x27;s complement</td></tr></table>

## UI_OUTX_L_A_OIS_DualC (34h) and UI_OUTX_H_A_OIS_DualC (35h)

Linear acceleration sensor X-axis output register (R). The value is expressed as a 16-bit word in two’s complement. 

Data are according to the accelerometer full-scale and ODR settings of the OIS accelerometer or according to the accelerometer dual-channel mode configuration. 


Table 114. UI_OUTX_L_A_OIS_DualC register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 115. UI_OUTX_H_A_OIS_DualC register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>


Table 116. UI_OUTX_A_OIS_DualC register description


<table><tr><td>D[15:0]</td><td>Accelerometer X-axis OIS/DualC output expressed in two&#x27;s complement</td></tr></table>

## UI_OUTY_L_A_OIS_DualC (36h) and UI_OUTY_H_A_OIS_DualC (37h)

Linear acceleration sensor Y-axis output register (R). The value is expressed as a 16-bit word in two’s complement. 

Data are according to the accelerometer full-scale and ODR settings of the OIS accelerometer or according to the accelerometer dual-channel mode configuration. 


Table 117. UI_OUTY_L_A_OIS_DualC register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 118. UI_OUTY_H_A_OIS_DualC register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>

## Table 119. UI_OUTY_A_OIS_DualC register description

<table><tr><td>D[15:0]</td><td>Accelerometer Y-axis OIS/DualC output expressed in two&#x27;s complement</td></tr></table>

## UI_OUTZ_L_A_OIS_DualC (38h) and UI_OUTZ_H_A_OIS_DualC (39h)

Linear acceleration sensor Z-axis output register (R). The value is expressed as a 16-bit word in two’s complement. 

Data are according to the accelerometer full-scale and ODR settings of the OIS accelerometer or according to the accelerometer dual-channel mode configuration. 


Table 120. UI_OUTZ_L_A_OIS_DualC register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 121. UI_OUTZ_H_A_OIS_DualC register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>


Table 122. UI_OUTZ_A_OIS_DualC register description


<table><tr><td>D[15:0]</td><td>Accelerometer Z-axis OIS/DualC output expressed in two&#x27;s complement</td></tr></table>

## AH_QVAR_OUT_L (3Ah) and AH_QVAR_OUT_H (3Bh)

Analog hub and Qvar data output register (R). L and H registers together express a 16-bit word in two’s complement. 


Table 123. AH_QVAR_OUT_L register


<table><tr><td>AH_Qvar_7</td><td>AH_Qvar_6</td><td>AH_Qvar_5</td><td>AH_Qvar_4</td><td>AH_Qvar_3</td><td>AH_Qvar_2</td><td>AH_Qvar_1</td><td>AH_Qvar_0</td></tr></table>


Table 124. AH_QVAR_OUT_H register


<table><tr><td>AH_Qvar_15</td><td>AH_Qvar_14</td><td>AH_Qvar_13</td><td>AH_Qvar_12</td><td>AH_Qvar_11</td><td>AH_Qvar_10</td><td>AH_Qvar_9</td><td>AH_Qvar_8</td></tr></table>


Table 125. AH_QVAR_OUT register description


<table><tr><td>AH_Qvar_[15:0]</td><td>When the analog hub or Qvar is enabled (by setting the AH_QVAR_EN bit to 1 in CTRL7 (16h)), these registers contain the analog hub or the Qvar sensor output data.Data are expressed in two&#x27;s complement.</td></tr></table>

TIMESTAMP0 (40h), TIMESTAMP1 (41h), TIMESTAMP2 (42h), and TIMESTAMP3 (43h) 

Timestamp first data output register (R). The value is expressed as a 32-bit word and the bit resolution is 21.75 µs (typical). 


Table 126. TIMESTAMP output registers


<table><tr><td>D31</td><td>D30</td><td>D29</td><td>D28</td><td>D27</td><td>D26</td><td>D25</td><td>D24</td></tr><tr><td colspan="8"></td></tr><tr><td>D23</td><td>D22</td><td>D21</td><td>D20</td><td>D19</td><td>D18</td><td>D17</td><td>D16</td></tr><tr><td colspan="8"></td></tr><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr><tr><td colspan="8"></td></tr><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 127. TIMESTAMP output register description


<table><tr><td>D[31:0]</td><td>Timestamp output registers: 1LSB = 21.75 μs (typical)</td></tr></table>

## UI_STATUS_REG_OIS (44h)


Table 128. UI_STATUS_REG_OIS register


<table><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>GYRO_SETTLING</td><td>GDA_OIS</td><td>XLDA_OIS</td></tr></table>

## Table 129. UI_STATUS_REG_OIS register description

<table><tr><td>GYRO_SETTLING</td><td>High when the gyroscope output is in the settling phase</td></tr><tr><td>GDA_OIS</td><td>Gyroscope OIS data available (reset when one of the high parts of the output data is read).Default value: 0(0: no set of data available at gyroscope OIS output;1: a new set of data is available at gyroscope output)</td></tr><tr><td>XLDA_OIS</td><td>Accelerometer OIS data available (reset when one of the high parts of the output data is read).Default value: 0(0: no set of data available at gyroscope OIS output;1: a new set of data is available at gyroscope output)</td></tr></table>

## WAKE_UP_SRC (45h)

Wake-up interrupt source register (R) 


Table 130. WAKE_UP_SRC register


<table><tr><td>0</td><td>SLEEP_CHANGE_IA</td><td>FF_IA</td><td>SLEEP_STATE</td><td>WU_IA</td><td>X_WU</td><td>Y_WU</td><td>Z_WU</td></tr></table>

## Table 131. WAKE_UP_SRC register description

<table><tr><td>SLEEP_CHANGE_IA</td><td>Detects change event in activity/inactivity status. Default value: 0(0: change status not detected; 1: change status detected)</td></tr><tr><td>FF_IA</td><td>Free-fall event detection status. Default: 0(0: free-fall event not detected; 1: free-fall event detected)</td></tr><tr><td>SLEEP_STATE</td><td>Sleep status bit. Default value: 0(0: Activity status; 1: Inactivity status)</td></tr><tr><td>WU_IA</td><td>Wake-up event detection status. Default value: 0(0: wake-up event not detected; 1: wake-up event detected.)</td></tr><tr><td>X_WU</td><td>Wake-up event detection status on X-axis. Default value: 0(0: wake-up event on X-axis not detected; 1: wake-up event on X-axis detected)</td></tr><tr><td>Y_WU</td><td>Wake-up event detection status on Y-axis. Default value: 0(0: wake-up event on Y-axis not detected; 1: wake-up event on Y-axis detected)</td></tr><tr><td>Z_WU</td><td>Wake-up event detection status on Z-axis. Default value: 0(0: wake-up event on Z-axis not detected; 1: wake-up event on Z-axis detected)</td></tr></table>

## TAP_SRC (46h)

Tap source register (R) 


Table 132. TAP_SRC register


<table><tr><td>0</td><td>TAP_IA</td><td>SINGLE_TAP</td><td>DOUBLE_TAP</td><td>TAP_SIGN</td><td>X_TAP</td><td>Y_TAP</td><td>Z_TAP</td></tr></table>


Table 133. TAP_SRC register description


<table><tr><td>TAP_IA</td><td>Tap event detection status. Default: 0(0: tap event not detected; 1: tap event detected)</td></tr><tr><td>SINGLE_TAP</td><td>Single-tap event status. Default value: 0(0: single tap event not detected; 1: single tap event detected)</td></tr><tr><td>DOUBLE_TAP</td><td>Double-tap event detection status. Default value: 0(0: double-tap event not detected; 1: double-tap event detected.)</td></tr><tr><td>TAP_SIGN</td><td>Sign of acceleration detected by tap event. Default: 0(0: positive sign of acceleration detected by tap event;1: negative sign of acceleration detected by tap event)</td></tr><tr><td>X_TAP</td><td>Tap event detection status on X-axis. Default value: 0(0: tap event on X-axis not detected; 1: tap event on X-axis detected)</td></tr><tr><td>Y_TAP</td><td>Tap event detection status on Y-axis. Default value: 0(0: tap event on Y-axis not detected; 1: tap event on Y-axis detected)</td></tr><tr><td>Z_TAP</td><td>Tap event detection status on Z-axis. Default value: 0(0: tap event on Z-axis not detected; 1: tap event on Z-axis detected)</td></tr></table>

## D6D_SRC (47h)

Portrait, landscape, face-up and face-down source register (R) 


Table 134. D6D_SRC register


<table><tr><td>0</td><td>D6D_IA</td><td>ZH</td><td>ZL</td><td>YH</td><td>YL</td><td>XH</td><td>XL</td></tr></table>


Table 135. D6D_SRC register description


<table><tr><td>D6D_IA</td><td>Interrupt active for change position portrait, landscape, face-up, face-down. Default value: 0(0: change position not detected; 1: change position detected)</td></tr><tr><td>ZH</td><td>Z-axis high event (over threshold). Default value: 0(0: event not detected; 1: event (over threshold) detected)</td></tr><tr><td>ZL</td><td>Z-axis low event (under threshold). Default value: 0(0: event not detected; 1: event (under threshold) detected)</td></tr><tr><td>YH</td><td>Y-axis high event (over threshold). Default value: 0(0: event not detected; 1: event (over-threshold) detected)</td></tr><tr><td>YL</td><td>Y-axis low event (under threshold). Default value: 0(0: event not detected; 1: event (under threshold) detected)</td></tr><tr><td>XH</td><td>X-axis high event (over threshold). Default value: 0(0: event not detected; 1: event (over threshold) detected)</td></tr><tr><td>XL</td><td>X-axis low event (under threshold). Default value: 0(0: event not detected; 1: event (under threshold) detected)</td></tr></table>

## STATUS_MASTER_MAINPAGE (48h)

Sensor hub source register (R) 


Table 136. STATUS_MASTER_MAINPAGE register


<table><tr><td>WR_ONCE_DONE</td><td>SLAVE3_NACK</td><td>SLAVE2_NACK</td><td>SLAVE1_NACK</td><td>SLAVE0_NACK</td><td>0</td><td>0</td><td>SENS_HUB_ENDOP</td></tr></table>


Table 137. STATUS_MASTER_MAINPAGE register description


<table><tr><td>WR_ONCE_DONE</td><td>When the bit WRITE_ONCE in MASTER_CONFIG (14h) is configured as 1, this bit is set to 1 when the write operation on slave 0 has been performed and completed. Default value: 0</td></tr><tr><td>SLAVE3_NACK</td><td>This bit is set to 1 if Not acknowledge occurs on slave 3 communication. Default value: 0</td></tr><tr><td>SLAVE2_NACK</td><td>This bit is set to 1 if Not acknowledge occurs on slave 2 communication. Default value: 0</td></tr><tr><td>SLAVE1_NACK</td><td>This bit is set to 1 if Not acknowledge occurs on slave 1 communication. Default value: 0</td></tr><tr><td>SLAVE0_NACK</td><td>This bit is set to 1 if Not acknowledge occurs on slave 0 communication. Default value: 0</td></tr><tr><td>SENS_HUB_ENDOP</td><td>Sensor hub communication status. Default value: 0(0: sensor hub communication not concluded;1: sensor hub communication concluded)</td></tr></table>

## EMB_FUNC_STATUS_MAINPAGE (49h)

Embedded function status register (R) 


Table 138. EMB_FUNC_STATUS_MAINPAGE register


<table><tr><td>IS_FSM_LC</td><td>0</td><td>IS_SIGMOT</td><td>IS_TILT</td><td>IS_STEP_DET</td><td>0</td><td>0</td><td>0</td></tr></table>


Table 139. EMB_FUNC_STATUS_MAINPAGE register description


<table><tr><td>IS_FSM_LC</td><td>Interrupt status bit for FSM long counter timeout interrupt event.(1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_SIGMOT</td><td>Interrupt status bit for significant motion detection(1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_TILT</td><td>Interrupt status bit for tilt detection(1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_STEP_DET</td><td>Interrupt status bit for step detection(1: interrupt detected; 0: no interrupt)</td></tr></table>

## FSM_STATUS_MAINPAGE (4Ah)

Finite state machine status register (R) 


Table 140. FSM_STATUS_MAINPAGE register


<table><tr><td>IS_FSM8</td><td>IS_FSM7</td><td>IS_FSM6</td><td>IS_FSM5</td><td>IS_FSM4</td><td>IS_FSM3</td><td>IS_FSM2</td><td>IS_FSM1</td></tr></table>


Table 141. FSM_STATUS_MAINPAGE register description


<table><tr><td>IS_FSM8</td><td>Interrupt status bit for FSM8 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM7</td><td>Interrupt status bit for FSM7 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM6</td><td>Interrupt status bit for FSM6 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM5</td><td>Interrupt status bit for FSM5 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM4</td><td>Interrupt status bit for FSM4 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM3</td><td>Interrupt status bit for FSM3 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM2</td><td>Interrupt status bit for FSM2 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM1</td><td>Interrupt status bit for FSM1 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr></table>

## MLC_STATUS_MAINPAGE (4Bh)

Machine learning core status register (R) 


Table 142. MLC_STATUS _MAINPAGE register


<table><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>IS_MLC4</td><td>IS_MLC3</td><td>IS_MLC2</td><td>IS_MLC1</td></tr></table>


Table 143. MLC_STATUS_MAINPAGE register description


<table><tr><td>IS_MLC4</td><td>Interrupt status bit for MLC4 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_MLC3</td><td>Interrupt status bit for MLC3 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_MLC2</td><td>Interrupt status bit for MLC2 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_MLC1</td><td>Interrupt status bit for MLC1 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr></table>

## INTERNAL_FREQ_FINE (4Fh)

Internal frequency register (R) 


Table 144. INTERNAL_FREQ_FINE register


<table><tr><td>FREQ_FINE_7</td><td>FREQ_FINE_6</td><td>FREQ_FINE_5</td><td>FREQ_FINE_4</td><td>FREQ_FINE_3</td><td>FREQ_FINE_2</td><td>FREQ_FINE_1</td><td>FREQ_FINE_0</td></tr></table>


Table 145. INTERNAL_FREQ_FINE register description


<table><tr><td>FREQ_FINE_[7:0]</td><td>Difference in percentage of the effective ODR (and timestamp rate) with respect to the typical.Step: 0.13%. 8-bit format, two&#x27;s complement.</td></tr></table>

The actual timestamp resolution and the actual output data rate can be calculated using the following formulas: 

$$
t _ {a c t u a l} [ s ] = \frac {1}{4 6 0 8 0 \cdot (1 + 0 . 0 0 1 3 \cdot F R E Q \_ F I N E)}
$$

$$
O D R _ {a c t u a l} [ H z ] = \frac {7 6 8 0 \cdot (1 + 0 . 0 0 1 3 \cdot F R E Q \_ F I N E)}{O D R _ {c o e f f}}
$$


Table 146. ${ \tt O D R } _ { \tt c o e f f }$ values


<table><tr><td>Selected ODR [Hz]</td><td>ODRcoeff</td></tr><tr><td>7.5</td><td>1024</td></tr><tr><td>15</td><td>512</td></tr><tr><td>30</td><td>256</td></tr><tr><td>60</td><td>128</td></tr><tr><td>120</td><td>64</td></tr><tr><td>240</td><td>32</td></tr><tr><td>480</td><td>16</td></tr><tr><td>960</td><td>8</td></tr><tr><td>1.92 kHz</td><td>4</td></tr><tr><td>3.84 kHz</td><td>2</td></tr><tr><td>7.68 kHz</td><td>1</td></tr></table>

## FUNCTIONS_ENABLE (50h)

Enable interrupt functions register (R/W) 


Table 147. FUNCTIONS_ENABLE register


<table><tr><td>INTERRUPTS_ENABLE</td><td>TIMESTAMP_EN</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>DIS_RST_LIR_ALL_INT</td><td><eq>0^{(1)}</eq></td><td>INACT_EN_1</td><td>INACT_EN_0</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 148. FUNCTIONS_ENABLE register description


<table><tr><td>INTERRUPTS_ENABLE</td><td>Enables basic interrupts (6D/4D, free-fall, wake-up, tap, activity/inactivity). Default value: 0(0: interrupt disabled; 1: interrupt enabled)</td></tr><tr><td>TIMESTAMP_EN</td><td>Enables timestamp counter. The counter is readable in TIMESTAMP0 (40h), TIMESTAMP1 (41h), TIMESTAMP2 (42h), and TIMESTAMP3 (43h). Default value: 0(0: disabled; 1: enabled)</td></tr><tr><td>DIS_RST_LIR_ALL_INT</td><td>When this bit is set to 1, reading the ALL_INT_SRC (1Dh) register does not reset the latched interrupt signals. This can be useful in order to not reset some status flags before reading the corresponding status register. Default value: 0(0: disabled; 1: enabled)</td></tr><tr><td>INACT_EN_[1:0]</td><td>Enables activity/inactivity (sleep) function. Default value: 00(00: stationary/motion-only interrupts generated, accelerometer and gyroscope configuration do not change;01: sets accelerometer to low-power mode 1 with accelerometer ODR selected through the XL_INACT_ODR_[1:0] bits of the INACTIVITY_DUR (54h) register, gyroscope configuration does not change;10: sets accelerometer to low-power mode 1 with accelerometer ODR selected through the XL_INACT_ODR_[1:0] bits of the INACTIVITY_DUR (54h) register, gyroscope in sleep mode;11: sets accelerometer to low-power mode 1 with accelerometer ODR selected through the XL_INACT_ODR_[1:0] bits of the INACTIVITY_DUR (54h) register, gyroscope in power-down mode)</td></tr></table>

## DEN (51h)

DEN configuration register (R/W) 


Table 149. DEN register


<table><tr><td><eq>0^{(1)}</eq></td><td>LVL1_EN</td><td>LVL2_EN</td><td>DEN_XL_EN</td><td>DEN_X</td><td>DEN_Y</td><td>DEN_Z</td><td>DEN_XL_G</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 150. DEN register description


<table><tr><td>LVL1_EN</td><td>Enables DEN data level-sensitive trigger. Refer to Table 151.</td></tr><tr><td>LVL2_EN</td><td>Enables DEN level-sensitive latched. Refer to Table 151.</td></tr><tr><td>DEN_XL_EN</td><td>Extends DEN functionality to accelerometer sensor. Default value: 0(0: disabled; 1: enabled)</td></tr><tr><td>DEN_X</td><td>DEN value stored in LSB of X-axis. Default value: 1(0: DEN not stored in X-axis LSB; 1: DEN stored in X-axis LSB)</td></tr><tr><td>DEN_Y</td><td>DEN value stored in LSB of Y-axis. Default value: 1(0: DEN not stored in Y-axis LSB; 1: DEN stored in Y-axis LSB)</td></tr><tr><td>DEN_Z</td><td>DEN value stored in LSB of Z-axis. Default value: 1(0: DEN not stored in Z-axis LSB; 1: DEN stored in Z-axis LSB)</td></tr><tr><td>DEN_XL_G</td><td>DEN stamping sensor selection. Default value: 0(0: DEN pin info stamped in the gyroscope axis selected by bits DEN_X, DEN_Y, DEN_Z;1: DEN pin info stamped in the accelerometer axis selected by bits DEN_X, DEN_Y, DEN_Z)</td></tr></table>


Table 151. Trigger mode selection


<table><tr><td>LVL1_EN, LVL2_EN</td><td>Trigger mode</td></tr><tr><td>10</td><td>Level-sensitive trigger mode is selected</td></tr><tr><td>11</td><td>Level-sensitive latched mode is selected</td></tr></table>

## INACTIVITY_DUR (54h)

Activity/inactivity configuration register (R/W) 


Table 152. INACTIVITY_DUR register


<table><tr><td>SLEEP_STATUS_ON_INT</td><td>WU_INACT_THS_W_2</td><td>WU_INACT_THS_W_1</td><td>WU_INACT_THS_W_0</td><td>XL_INACT_ODR_1</td><td>XL_INACT_ODR_0</td><td>INACT_DUR_1</td><td>INACT_DUR_0</td></tr></table>

## Table 153. INACTIVITY_DUR register description

<table><tr><td>SLEEP_STATUS_ON_INT</td><td>Activity/inactivity interrupt mode configuration.If the INT1_SLEEP_CHANGE or INT2_SLEEP_CHANGE bit is enabled, drives the sleep status or sleep change on the INT pin. Default value: 0(0: sleep change notification on INT pin;1: sleep status reported on INT pin)</td></tr><tr><td>WU_INACT_THS_W_[2:0]</td><td>Weight of 1 LSB of wake-up (WU_THS) and activity/inactivity (INACT_THS) threshold.(000: 7.8125 mg/LSB (default);001: 15.625 mg/LSB;010: 31.25 mg/LSB;011: 62.5 mg/LSB;100: 125 mg/LSB;101 - 110 - 111: 250 mg/LSB)</td></tr><tr><td>XL_INACT_ODR_[1:0]</td><td>Selects the ODR_XL target during inactivity.(00: 1.875 Hz;01: 15 Hz (default);10: 30 Hz;11: 60 Hz)</td></tr><tr><td>INACT_DUR_[1:0]</td><td>Duration in the transition from stationary to motion (from inactivity to activity).(00: transition to motion (activity) immediately at first overthreshold event (default);01: transition to motion (activity) after two consecutive overthreshold events;10: transition to motion (activity) after three consecutive overthreshold events;11: transition to motion (activity) after four consecutive overthreshold events)</td></tr></table>

## INACTIVITY_THS (55h)

Activity/inactivity threshold setting register (R/W) 


Table 154. INACTIVITY_THS register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>INACT_THS_5</td><td>INACT_THS_4</td><td>INACT_THS_3</td><td>INACT_THS_2</td><td>INACT_THS_1</td><td>INACT_THS_0</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 


## Table 155. INACTIVITY_THS register description

<table><tr><td>INACT_THS_[5:0]</td><td>Activity/inactivity threshold. The resolution of the threshold depends on the value of WU_INACT_THS_W_[2:0] in the INACTIVITY_DUR (54h) register. Default value: 000000</td></tr></table>

## TAP_CFG0 (56h)

Tap configuration register 0 (R/W) 


Table 156. TAP_CFG0 register


<table><tr><td><eq>0^{(1)}</eq></td><td>LOW_PASS_ON_6D</td><td>HW_FUNC_MASK_XL_SETTL</td><td>SLOPE_FDS</td><td>TAP_X_EN</td><td>TAP_Y_EN</td><td>TAP_Z_EN</td><td>LIR</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 157. TAP_CFG0 register description


<table><tr><td>LOW_PASS_ON_6D</td><td>LPF2 filter on 6D function selection. Refer to Figure 32. Default value: 0(0: ODR/2 low-pass filtered data sent to 6D interrupt function;1: LPF2 output data sent to 6D interrupt function)</td></tr><tr><td>HW_FUNC_MASK_XL_SETTL</td><td>Enables masking the execution trigger of the basic interrupt functions (6D/4D, free-fall, wake-up, tap, activity/inactivity) when accelerometer data are settling. Default value: 0(0: disabled; 1: enabled)Note: Refer to the product application note for the details regarding operating/power mode configurations, settings, turn-on/off time and on-the-fly changes.</td></tr><tr><td>SLOPE_FDS</td><td>HPF or slope filter selection on wake-up and activity/inactivity functions. Refer to Figure 32. Default value: 0(0: slope filter applied; 1: HPF applied)</td></tr><tr><td>TAP_X_EN</td><td>Enables X direction in tap recognition. Default value: 0(0: X direction disabled; 1: X direction enabled)</td></tr><tr><td>TAP_Y_EN</td><td>Enables Y direction in tap recognition. Default value: 0(0: Y direction disabled; 1: Y direction enabled)</td></tr><tr><td>TAP_Z_EN</td><td>Enables Z direction in tap recognition. Default value: 0(0: Z direction disabled; 1: Z direction enabled)</td></tr><tr><td>LIR</td><td>Latched interrupt. Default value: 0(0: interrupt request not latched; 1: interrupt request latched)</td></tr></table>

## TAP_CFG1 (57h)

Tap configuration register 1 (R/W) 


Table 158. TAP_CFG1 register


<table><tr><td>TAP_PRIORITY_2</td><td>TAP_PRIORITY_1</td><td>TAP_PRIORITY_0</td><td>TAP_THS_X_4</td><td>TAP_THS_X_3</td><td>TAP_THS_X_2</td><td>TAP_THS_X_1</td><td>TAP_THS_X_0</td></tr></table>


Table 159. TAP_CFG1 register description


<table><tr><td>TAP_PRIORITY_[2:0]</td><td>Selection of axis priority for tap detection (see Table 160)</td></tr><tr><td>TAP_THS_X_[4:0]</td><td>X-axis tap recognition threshold. Default value: 01 LSB = FS_XL / (<eq>2^{5}</eq>)</td></tr></table>


Table 160. TAP priority decoding


<table><tr><td>TAP_PRIORITY_[2:0]</td><td>Max. priority</td><td>Mid. priority</td><td>Min. priority</td></tr><tr><td>000</td><td>X</td><td>Y</td><td>Z</td></tr><tr><td>001</td><td>Y</td><td>X</td><td>Z</td></tr><tr><td>010</td><td>X</td><td>Z</td><td>Y</td></tr><tr><td>011</td><td>Z</td><td>Y</td><td>X</td></tr><tr><td>100</td><td>X</td><td>Y</td><td>Z</td></tr><tr><td>101</td><td>Y</td><td>Z</td><td>X</td></tr><tr><td>110</td><td>Z</td><td>X</td><td>Y</td></tr><tr><td>111</td><td>Z</td><td>Y</td><td>X</td></tr></table>

## TAP_CFG2 (58h)

Tap configuration register 2 (R/W) 


Table 161. TAP_CFG2 register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>TAP_THS_Y_4</td><td>TAP_THS_Y_3</td><td>TAP_THS_Y_2</td><td>TAP_THS_Y_1</td><td>TAP_THS_Y_0</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 162. TAP_CFG2 register description


<table><tr><td>TAP_THS_Y_[4:0]</td><td>Y-axis tap recognition threshold. Default value: 01 LSB = FS_XL / (25)</td></tr></table>

## TAP_THS_6D (59h)

Portrait/landscape position and tap function threshold register (R/W) 


Table 163. TAP_THS_6D register


<table><tr><td>D4D_EN</td><td>SIXD_THS_1</td><td>SIXD_THS_0</td><td>TAP_THS_Z_4</td><td>TAP_THS_Z_3</td><td>TAP_THS_Z_2</td><td>TAP_THS_Z_1</td><td>TAP_THS_Z_0</td></tr></table>


Table 164. TAP_THS_6D register description


<table><tr><td>D4D_EN</td><td>Enables 4D orientation detection. Z-axis position detection is disabled. Default value: 0(0: disabled; 1: enabled)</td></tr><tr><td>SIXD_THS_[1:0]</td><td>Threshold for 4D/6D function. Default value: 00For details, refer to Table 165.</td></tr><tr><td>TAP_THS_Z_[4:0]</td><td>Z-axis recognition threshold. Default value: 01 LSB = FS_XL / (25)</td></tr></table>


Table 165. Threshold for D4D/D6D function


<table><tr><td>SIXD_THS_[1:0]</td><td>Threshold value</td></tr><tr><td>00</td><td>80 degrees</td></tr><tr><td>01</td><td>70 degrees</td></tr><tr><td>10</td><td>60 degrees</td></tr><tr><td>11</td><td>50 degrees</td></tr></table>

## TAP_DUR (5Ah)

Tap recognition function setting register (R/W) 


Table 166. TAP_DUR register


<table><tr><td>DUR_3</td><td>DUR_2</td><td>DUR_1</td><td>DUR_0</td><td>QUIET_1</td><td>QUIET_0</td><td>SHOCK_1</td><td>SHOCK_0</td></tr></table>


Table 167. TAP_DUR register description


<table><tr><td>DUR_[3:0]</td><td>Duration of maximum time gap for double-tap recognition. Default: 0000When double-tap recognition is enabled, this register expresses the maximum time between two consecutive detected taps to determine a double-tap event. The default value of these bits is 0000b which corresponds to 16/ODR_XL time. If the DUR_[3:0] bits are set to a different value, 1LSB corresponds to 32/ODR_XL time.</td></tr><tr><td>QUIET_[1:0]</td><td>Expected quiet time after a tap detection. Default value: 00Quiet time is the time after the first detected tap in which there must not be any overthreshold event. The default value of these bits is 00b which corresponds to 2/ODR_XL time. If the QUIET_[1:0] bits are set to a different value, 1LSB corresponds to 4/ODR_XL time.</td></tr><tr><td>SHOCK_[1:0]</td><td>Maximum duration of overthreshold event. Default value: 00Maximum duration is the maximum time of an overthreshold signal detection to be recognized as a tap event. The default value of these bits is 00b which corresponds to 4/ODR_XL time. If the SHOCK_[1:0] bits are set to a different value, 1LSB corresponds to 8/ODR_XL time.</td></tr></table>

## WAKE_UP_THS (5Bh)

Single/double-tap selection and wake-up configuration (R/W) 


Table 168. WAKE_UP_THS register


<table><tr><td>SINGLE_DOUBLE_TAP</td><td>USR_OFF_ON_WU</td><td>WK_THS_5</td><td>WK_THS_4</td><td>WK_THS_3</td><td>WK_THS_2</td><td>WK_THS_1</td><td>WK_THS_0</td></tr></table>


Table 169. WAKE_UP_THS register description


<table><tr><td>SINGLE_DOUBLE_TAP</td><td>Enables single/double-tap event. Default value: 0(0: only single-tap event enabled;1: both single and double-tap events enabled)</td></tr><tr><td>USR_OFF_ON_WU</td><td>Drives the low-pass filtered data with user offset correction (instead of high-pass filtered data) to the wake-up and the activity/inactivity functions. Refer to Figure 32. Default value: 0</td></tr><tr><td>WK_THS_[5:0]</td><td>Wake-up threshold. The resolution of the threshold depends on the value of WU_INACT_THS_W_[2:0] in the INACTIVITY_DUR (54h) register. Default value: 000000</td></tr></table>

## WAKE_UP_DUR (5Ch)

Free-fall, wake-up, and sleep mode functions duration setting register (R/W) 


Table 170. WAKE_UP_DUR register


<table><tr><td>FF_DUR_5</td><td>WAKE_DUR_1</td><td>WAKE_DUR_0</td><td><eq>0^{(1)}</eq></td><td>SLEEP_DUR_3</td><td>SLEEP_DUR_2</td><td>SLEEP_DUR_1</td><td>SLEEP_DUR_0</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 171. WAKE_UP_DUR register description


<table><tr><td>FF_DUR_5</td><td>Free-fall duration event. Default: 0For the complete configuration of the free-fall duration, refer to FF_DUR_[4:0] in the FREE_FALL (5Dh) configuration.1 LSB = 1/ODR_XL time</td></tr><tr><td>WAKE_DUR_[1:0]</td><td>Wake-up duration event. Default: 001 LSB = 1/ODR_XL time</td></tr><tr><td>SLEEP_DUR_[3:0]</td><td>Duration to go in sleep mode. Default value: 0000 (this corresponds to 16 ODR)1 LSB = 512/ODR_XL time</td></tr></table>

## FREE_FALL (5Dh)

Free-fall function duration setting register (R/W) 


Table 172. FREE_FALL register


<table><tr><td>FF_DUR_4</td><td>FF_DUR_3</td><td>FF_DUR_2</td><td>FF_DUR_1</td><td>FF_DUR_0</td><td>FF_THS_2</td><td>FF_THS_1</td><td>FF_THS_0</td></tr></table>


Table 173. FREE_FALL register description


<table><tr><td>FF_DUR_[4:0]</td><td>Free-fall duration event. Default: 00000For the complete configuration of the free-fall duration, refer to FF_DUR_5 in the WAKE_UP_DUR (5Ch) configuration.</td></tr><tr><td>FF_THS_[2:0]</td><td>Free-fall threshold setting. Default: 000For details refer to Table 174.</td></tr></table>


Table 174. Threshold for free-fall function


<table><tr><td>FF_THS_[2:0]</td><td>Threshold value</td></tr><tr><td>000</td><td>156 mg</td></tr><tr><td>001</td><td>219 mg</td></tr><tr><td>010</td><td>250 mg</td></tr><tr><td>011</td><td>312 mg</td></tr><tr><td>100</td><td>344 mg</td></tr><tr><td>101</td><td>406 mg</td></tr><tr><td>110</td><td>469 mg</td></tr><tr><td>111</td><td>500 mg</td></tr></table>

## MD1_CFG (5Eh)

Functions routing to INT1 pin register (R/W). Each bit in this register enables a signal to be carried over the INT1 pin. The output of the pin is the OR combination of the signals selected here and in the INT1_CTRL (0Dh) register. 


Table 175. MD1_CFG register


<table><tr><td>INT1_SLEEP_CHANGE</td><td>INT1_SINGLE_TAP</td><td>INT1_WU</td><td>INT1_FF</td><td>INT1_DOUBLE_TAP</td><td>INT1_6D</td><td>INT1_EMB_FUNC</td><td>INT1_SHUB</td></tr></table>


Table 176. MD1_CFG register description


<table><tr><td><eq>INT1\_SLEEP\_CHANGE^{(1)}</eq></td><td>Routing activity/inactivity recognition event to INT1. Default: 0(0: routing activity/inactivity event to INT1 disabled;1: routing activity/inactivity event to INT1 enabled)</td></tr><tr><td><eq>INT1\_SINGLE\_TAP</eq></td><td>Routing single-tap recognition event to INT1. Default: 0(0: routing single-tap event to INT1 disabled;1: routing single-tap event to INT1 enabled)</td></tr><tr><td><eq>INT1\_WU</eq></td><td>Routing wake-up event to INT1. Default value: 0(0: routing wake-up event to INT1 disabled;1: routing wake-up event to INT1 enabled)</td></tr><tr><td><eq>INT1\_FF</eq></td><td>Routing free-fall event to INT1. Default value: 0(0: routing free-fall event to INT1 disabled;1: routing free-fall event to INT1 enabled)</td></tr><tr><td><eq>INT1\_DOUBLE\_TAP</eq></td><td>Routing tap event to INT1. Default value: 0(0: routing double-tap event to INT1 disabled;1: routing double-tap event to INT1 enabled)</td></tr><tr><td><eq>INT1\_6D</eq></td><td>Routing 6D event to INT1. Default value: 0(0: routing 6D event to INT1 disabled;1: routing 6D event to INT1 enabled)</td></tr><tr><td><eq>INT1\_EMB\_FUNC</eq></td><td>Routing embedded functions event to INT1. Default value: 0(0: routing embedded functions event to INT1 disabled;1: routing embedded functions event to INT1 enabled)</td></tr><tr><td><eq>INT1\_SHUB</eq></td><td>Routing sensor hub communication concluded event to INT1. Default value: 0(0: routing sensor hub communication concluded event to INT1 disabled;1: routing sensor hub communication concluded event to INT1 enabled)</td></tr></table>


1. Activity/inactivity interrupt mode (sleep change or sleep status) depends on the SLEEP_STATUS_ON_INT bit in the INACTIVITY_DUR (54h) register. 


9.66 

## MD2_CFG (5Fh)

Functions routing to INT2 pin register (R/W). Each bit in this register enables a signal to be carried over the INT2 pin. The output of the pin is the OR combination of the signals selected here and in the INT2_CTRL (0Eh) register. 


Table 177. MD2_CFG register


<table><tr><td>INT2_SLEEP_CHANGE</td><td>INT2_SINGLE_TAP</td><td>INT2_WU</td><td>INT2_FF</td><td>INT2_DOUBLE_TAP</td><td>INT2_6D</td><td>INT2_EMB_FUNC</td><td>INT2_TIMESTAMP</td></tr></table>


Table 178. MD2_CFG register description


<table><tr><td><eq>INT2\_SLEEP\_CHANGE^{(1)}</eq></td><td>Routing activity/inactivity recognition event to INT2. Default: 0(0: routing activity/inactivity event to INT2 disabled;1: routing activity/inactivity event to INT2 enabled)</td></tr><tr><td>INT2_SINGLE_TAP</td><td>Single-tap recognition routing to INT2. Default: 0(0: routing single-tap event to INT2 disabled;1: routing single-tap event to INT2 enabled)</td></tr><tr><td>INT2_WU</td><td>Routing wake-up event to INT2. Default value: 0(0: routing wake-up event to INT2 disabled;1: routing wake-up event to INT2 enabled)</td></tr><tr><td>INT2_FF</td><td>Routing free-fall event to INT2. Default value: 0(0: routing free-fall event to INT2 disabled;1: routing free-fall event to INT2 enabled)</td></tr><tr><td>INT2_DOUBLE_TAP</td><td>Routing tap event to INT2. Default value: 0(0: routing double-tap event to INT2 disabled;1: routing double-tap event to INT2 enabled)</td></tr><tr><td>INT2_6D</td><td>Routing 6D event to INT2. Default value: 0(0: routing 6D event to INT2 disabled;1: routing 6D event to INT2 enabled)</td></tr><tr><td>INT2_EMB_FUNC</td><td>Routing embedded functions event to INT2. Default value: 0(0: routing embedded functions event to INT2 disabled;1: routing embedded functions event to INT2 enabled)</td></tr><tr><td>INT2_TIMESTAMP</td><td>Enables routing the alert for timestamp overflow within 5.6 ms to the INT2 pin.</td></tr></table>


1. Activity/inactivity interrupt mode (sleep change or sleep status) depends on the SLEEP_STATUS_ON_INT bit in the INACTIVITY_DUR (54h) register. 


## HAODR_CFG (62h)

9.68 

## EMB_FUNC_CFG (63h)

Embedded functions configuration register (R/W) 


Table 181. EMB_FUNC_CFG register


<table><tr><td>XL_DualC_BATCH_FROM_IF</td><td><eq>0^{(1)}</eq></td><td>EMB_FUNC_IRQ_MASK_G_SETTL</td><td>EMB_FUNC_IRQ_MASK_XL_SETTL</td><td>EMB_FUNC_DISABLE</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 182. EMB_FUNC_CFG register description


<table><tr><td>XL_DualC_BATCH_FROM_IF</td><td>When dual-channel mode is enabled, this bit enables batching the accelerometer channel 2 in FIFO. Default value: 0(0: disabled; 1: enabled)</td></tr><tr><td>EMB_FUNC_IRQ_MASK_G_SETTL</td><td>Enables / masks execution trigger of the embedded functions when gyroscope data are settling. Default value: 0(0: disabled;1: masks execution trigger of the embedded functions until gyroscope filter settling ends)Note: Refer to the product application note for the details regarding operating/power mode configurations, settings, turn-on/off time and on-the-fly changes.</td></tr><tr><td>EMB_FUNC_IRQ_MASK_XL_SETTL</td><td>Enables / masks execution trigger of the embedded functions when accelerometer data are settling. Default value: 0(0: disabled;1: masks execution trigger of the embedded functions until accelerometer filter settling ends)Note: Refer to the product application note for the details regarding operating/power mode configurations, settings, turn-on/off time and on-the-fly changes.</td></tr><tr><td>EMB_FUNC_DISABLE</td><td>Disables execution of the embedded functions. Default value: 0(0: disabled;1: embedded functions execution trigger is not generated anymore and all initialization procedures are forced when this bit is set back to 0).</td></tr></table>

## UI_HANDSHAKE_CTRL (64h)

Control register (UI side) for UI / SPI2 shared registers (R/W) 


Table 183. UI_HANDSHAKE_CTRL register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>UI_SHARED_ACK</td><td>UI_SHARED_REQ</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 


## Table 184. UI_HANDSHAKE_CTRL register description

<table><tr><td>UI_SHARED_ACK</td><td>Primary interface side. This bit acknowledges the handshake. If the secondary interface is not accessing the shared registers, this bit is set to 1 by the device and the R/W operation on the UI_SPI2_SHARED_0 (65h) through UI_SPI2_SHARED_5 (6Ah) registers is allowed on the primary interface.</td></tr><tr><td>UI_SHARED_REQ</td><td>This bit is used by the primary interface master to request access to the UI_SPI2_SHARED_0 (65h) through UI_SPI2_SHARED_5 (6Ah) registers. When the R/W operation is finished, the master must reset this bit.</td></tr></table>

## UI_SPI2_SHARED_0 (65h)

UI / SPI2 shared register 0 (R/W) 


Table 185. UI_SPI2_SHARED_0 register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 186. UI_SPI2_SHARED_0 register description


<table><tr><td>D[7:0]</td><td>Volatile byte is used as a contact point between the primary and secondary interface host. These shared registers are accessible only by one interface at a time and access is managed through the UI_SHARED_ACK and UI_SHARED_REQ bits of register UI_HANDSHAKE_CTRL (64h) and the SPI2_SHARED_ACK and SPI2_SHARED_REQ bits of register SPI2_HANDSHAKE_CTRL (6Eh).</td></tr></table>

## UI_SPI2_SHARED_1 (66h)

UI / SPI2 shared register 1 (R/W) 


Table 187. UI_SPI2_SHARED_1 register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 188. UI_SPI2_SHARED_1 register description


<table><tr><td>D[7:0]</td><td>Volatile byte is used as a contact point between the primary and secondary interface host. These shared registers are accessible only by one interface at a time and access is managed through the UI_SHARED_ACK and UI_SHARED_REQ bits of register UI_HANDSHAKE_CTRL (64h) and the SPI2_SHARED_ACK and SPI2_SHARED_REQ bits of register SPI2_HANDSHAKE_CTRL (6Eh).</td></tr></table>

## UI_SPI2_SHARED_2 (67h)

UI / SPI2 shared register 2 (R/W) 


Table 189. UI_SPI2_SHARED_2 register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 190. UI_SPI2_SHARED_2 register description


<table><tr><td>D[7:0]</td><td>Volatile byte is used as a contact point between the primary and secondary interface host. These shared registers are accessible only by one interface at a time and access is managed through the UI_SHARED_ACK and UI_SHARED_REQ bits of register UI_HANDSHAKE_CTRL (64h) and the SPI2_SHARED_ACK and SPI2_SHARED_REQ bits of register SPI2_HANDSHAKE_CTRL (6Eh).</td></tr></table>

## UI_SPI2_SHARED_3 (68h)

UI / SPI2 shared register 3 (R/W) 


Table 191. UI_SPI2_SHARED_3 register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>

## Table 192. UI_SPI2_SHARED_3 register description

<table><tr><td>D[7:0]</td><td>Volatile byte is used as a contact point between the primary and secondary interface host. These shared registers are accessible only by one interface at a time and access is managed through the UI_SHARED_ACK and UI_SHARED_REQ bits of register UI_HANDSHAKE_CTRL (64h) and the SPI2_SHARED_ACK and SPI2_SHARED_REQ bits of register SPI2_HANDSHAKE_CTRL (6Eh).</td></tr></table>

## UI_SPI2_SHARED_4 (69h)

UI / SPI2 shared register 4 (R/W) 


Table 193. UI_SPI2_SHARED_4 register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 194. UI_SPI2_SHARED_4 register description


<table><tr><td>D[7:0]</td><td>Volatile byte is used as a contact point between the primary and secondary interface host. These shared registers are accessible only by one interface at a time and access is managed through the UI_SHARED_ACK and UI_SHARED_REQ bits of register UI_HANDSHAKE_CTRL (64h) and the SPI2_SHARED_ACK and SPI2_SHARED_REQ bits of register SPI2_HANDSHAKE_CTRL (6Eh).</td></tr></table>

## UI_SPI2_SHARED_5 (6Ah)

UI / SPI2 shared register 5 (R/W) 


Table 195. UI_SPI2_SHARED_5 register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 196. UI_SPI2_SHARED_5 register description


<table><tr><td>D[7:0]</td><td>Volatile byte is used as a contact point between the primary and secondary interface host. These shared registers are accessible only by one interface at a time and access is managed through the UI_SHARED_ACK and UI_SHARED_REQ bits of register UI_HANDSHAKE_CTRL (64h) and the SPI2_SHARED_ACK and SPI2_SHARED_REQ bits of register SPI2_HANDSHAKE_CTRL (6Eh).</td></tr></table>

## CTRL_EIS (6Bh)

Gyroscope EIS channel control register (R/W) 


Table 197. CTRL_EIS register


<table><tr><td>ODR_G_EIS_1</td><td>ODR_G_EIS_0</td><td><eq>0^{(1)}</eq></td><td>LPF_G_EIS_BW</td><td>G_EIS_ON_G_OIS_OUT_REG</td><td>FS_G_EIS_2</td><td>FS_G_EIS_1</td><td>FS_G_EIS_0</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 198. CTRL_EIS register description


<table><tr><td>ODR_G_EIS_[1:0]</td><td>Enables and selects the ODR of the gyroscope EIS channel.(00: EIS channel is off (default);01: 1.92 kHz;10: 960 Hz;11: reserved)</td></tr><tr><td>LPF_G_EIS_BW</td><td>Gyroscope digital LPF_EIS filter bandwidth selection. Refer to Table 199.</td></tr><tr><td>G_EIS_ON_G_OIS_OUT_REG</td><td>Enables routing gyroscope EIS output to OIS from UI output addresses (2Eh – 33h). When this bit is set to 1, the gyroscope OIS data cannot be read from primary interface. Default value: 0(0: disabled; 1: enabled)</td></tr><tr><td>FS_G_EIS_[2:0]</td><td>Gyroscope full-scale selection for EIS channel. If the FS_G_[3:0] bits in CTRL6 (15h) are equal to 1100 (±4000 dps), FS_G_EIS_[2:0] must be set to “100” in order to have ±4000 dps full scale on both UI and EIS channels. If the FS_G_3 bit in register CTRL6 (15h) is equal to 0, the EIS channel full scale can be selected as follows:(000: ±125 dps (default);001: ±250 dps;010: ±500 dps;011: ±1000 dps;100: ±2000 dps;101: reserved;110: reserved;111: reserved)</td></tr></table>


Table 199. Gyroscope EIS chain digital LPF_EIS filter bandwidth selection


<table><tr><td>ODR_G_EIS_[1:0]</td><td>Gyroscope EIS ODR [Hz]</td><td>LPF_G_EIS_BW</td><td>Cutoff [Hz]</td><td>Phase @ 20 Hz [°]</td></tr><tr><td rowspan="2">01</td><td rowspan="2">1.92 kHz</td><td>0</td><td>153 Hz</td><td>-13.5°</td></tr><tr><td>1</td><td>203 Hz</td><td>-10.8°</td></tr><tr><td rowspan="2">10</td><td rowspan="2">960</td><td>0</td><td>148 Hz</td><td>-15.4°</td></tr><tr><td>1</td><td>193 Hz</td><td>-12.7°</td></tr></table>

## UI_INT_OIS (6Fh)

## OIS interrupt configuration register

The primary interface can write to this register when the OIS_CTRL_FROM_UI bit in the FUNC_CFG_ACCESS (01h) register is equal to 1 (primary IF full-control mode); this register is read-only when the OIS_CTRL_FROM_UI bit is equal to 0 (SPI2 full-control mode) and shows the content of the SPI2_INT_OIS (6Fh) register. 


Table 200. UI_INT_OIS register


<table><tr><td>INT2_DRDY_OIS</td><td>DRDY_MASK_OIS</td><td><eq>0^{(1)}</eq></td><td>ST_OIS_CLAMPDIS</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 


## Table 201. UI_INT_OIS register description

<table><tr><td>INT2_DRDY_OIS</td><td>Enables OIS chain DRDY on INT2 pin from the UI interface. This setting has priority over all other INT2 settings.</td></tr><tr><td>DRDY_MASK_OIS</td><td>Enables / masks OIS data available. Default value: 0(0: disabled;1: masks OIS DRDY signals (both accelerometer and gyroscope) until filter settling ends (accelerometer and gyroscope independently masked))</td></tr><tr><td>ST_OIS_CLAMPDIS</td><td>Disables OIS chain clamp during self-test. Default value: 0(0: All OIS chain outputs = 8000h during self-test;1: OIS chain self-test outputs)</td></tr></table>

## UI_CTRL1_OIS (70h)

OIS configuration register 

The primary interface can write this register when the OIS_CTRL_FROM_UI bit in the FUNC_CFG_ACCESS (01h) register is equal to 1 (primary IF full-control mode); this register is read-only when the OIS_CTRL_FROM_UI bit is equal to 0 (SPI2 full-control mode) and shows the content of the SPI2_CTRL1_OIS (70h) register. 


Table 202. UI_CTRL1_OIS register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>SIM_OIS</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>OIS_XL_EN</td><td>OIS_G_EN</td><td>SPI2_READ_EN</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 203. UI_CTRL1_OIS register description


<table><tr><td>SIM_OIS</td><td>SPI2 3- or 4-wire interface. Default value: 0(0: 4-wire SPI2;1: 3-wire SPI2)</td></tr><tr><td>OIS_XL_EN</td><td>Enables accelerometer OIS chain. Default value: 0(0: accelerometer OIS chain disabled;1: accelerometer OIS chain enabled)</td></tr><tr><td>OIS_G_EN</td><td>Enables gyroscope OIS chain. Default value: 0(0: gyroscope OIS chain disabled;1: gyroscope OIS chain enabled)</td></tr><tr><td>SPI2_READ_EN</td><td>In primary IF full-control mode, enables auxiliary SPI for reading OIS data in registers <eq>\text{SPI2\_OUTX\_L\_G\_OIS} (22h)</eq> and <eq>\text{SPI2\_OUTX\_H\_G\_OIS} (23h)</eq> through Section 11.9 <eq>\text{SPI2\_OUTZ\_L\_A\_OIS} (2Ch)</eq> and <eq>\text{SPI2\_OUTZ\_H\_A\_OIS} (2Dh)</eq>. Default value: 0(0: OIS data read from auxiliary SPI disabled;1: OIS data read from auxiliary SPI enabled)</td></tr></table>

## UI_CTRL2_OIS (71h)

OIS configuration register 

The primary interface can write this register when the OIS_CTRL_FROM_UI bit in the FUNC_CFG_ACCESS (01h) register is equal to 1 (primary IF full-control mode); this register is read-only when the OIS_CTRL_FROM_UI bit is equal to 0 (SPI2 full-control mode) and shows the content of the SPI2_CTRL2_OIS (71h) register. 


Table 204. UI_CTRL2_OIS register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>LPF1_G_OIS_BW_1</td><td>LPF1_G_OIS_BW_0</td><td>FS_G_OIS_2</td><td>FS_G_OIS_1</td><td>FS_G_OIS_0</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 205. UI_CTRL2_OIS register description


<table><tr><td>LPF1_G_OIS_BW_[1:0]</td><td>Gyroscope OIS digital LPF1 filter bandwidth selection. Refer to Table 206.</td></tr><tr><td>FS_G_OIS_[2:0]</td><td>Gyroscope OIS full-scale selection:(000: ±125 dps;001: ±250 dps;010: ±500 dps;011: ±1000 dps;100: ±2000 dps;101: reserved;110: reserved;111: reserved)</td></tr></table>


Table 206. Gyroscope OIS chain digital LPF1 filter bandwidth selection


<table><tr><td>LPF1_G_OIS_BW_[1:0]</td><td>Cutoff [Hz]</td><td>Phase @ 20 Hz [°]</td></tr><tr><td>00</td><td>293 Hz</td><td>-7.1°</td></tr><tr><td>01</td><td>217 Hz</td><td>-9.1°</td></tr><tr><td>10</td><td>158 Hz</td><td>-11.9°</td></tr><tr><td>11</td><td>476 Hz</td><td>-5.1°</td></tr></table>

## UI_CTRL3_OIS (72h)

OIS configuration register 

The primary interface can write this register when the OIS_CTRL_FROM_UI bit in the FUNC_CFG_ACCESS (01h) register is equal to 1 (primary IF full-control mode); this register is read-only when the OIS_CTRL_FROM_UI bit is equal to 0 (SPI2 full-control mode) and shows the content of the SPI2_CTRL3_OIS (72h) register. 


Table 207. UI_CTRL3_OIS register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>LPF_XL_OIS_BW_2</td><td>LPF_XL_OIS_BW_1</td><td>LPF_XL_OIS_BW_0</td><td><eq>0^{(1)}</eq></td><td>FS_XL_OIS_1</td><td>FS_XL_OIS_0</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 208. UI_CTRL3_OIS register description


<table><tr><td>LPF_XL_OIS_BW_[2:0]</td><td>Selects accelerometer OIS channel bandwidth, see Table 209. Default value: 0</td></tr><tr><td>FS_XL_OIS_[1:0]</td><td>Selects accelerometer OIS channel full-scale:(00: ±2 g (default);01: ±4 g;10: ±8 g;11: ±16 g)</td></tr></table>

When the accelerometer full-scale value is selected only from the UI side it is readable also from the OIS side. 


Table 209. Accelerometer OIS channel bandwidth and phase


<table><tr><td>LPF_XL_OIS_BW_[2:0]</td><td>Typ. overall bandwidth [Hz]</td><td>Typ. overall phase [°]</td></tr><tr><td>000</td><td>749 Hz</td><td>-3.41 deg @ 20 Hz</td></tr><tr><td>001</td><td>539 Hz</td><td>-4.04 deg@ 20 Hz</td></tr><tr><td>010</td><td>342 Hz</td><td>-5.31 deg@ 20 Hz</td></tr><tr><td>011</td><td>162 Hz</td><td>-9.08 deg@ 20 Hz</td></tr><tr><td>100</td><td>78.5 Hz</td><td>-16.4 deg @ 20 Hz</td></tr><tr><td>101</td><td>38.6 Hz</td><td>-29.6 deg@ 20 Hz</td></tr><tr><td>110</td><td>19.3 Hz</td><td>-28.8 deg @ 10 Hz</td></tr><tr><td>111</td><td>9.8 Hz</td><td>-29.1 deg @ 5 Hz</td></tr></table>

## X_OFS_USR (73h)

Accelerometer X-axis user offset correction (R/W). The offset value set in the X_OFS_USR offset register is internally subtracted from the acceleration value measured on the X-axis. 


Table 210. X_OFS_USR register


<table><tr><td>X_OFSSUR_7</td><td>X_OFSSUR_6</td><td>X_OFSSUR_5</td><td>X_OFSSUR_4</td><td>X_OFSSUR_3</td><td>X_OFSSUR_2</td><td>X_OFSSUR_1</td><td>X_OFSSUR_0</td></tr></table>


Table 211. X_OFS_USR register description


<table><tr><td>X_OFS_USR_[7:0]</td><td>Accelerometer X-axis user offset correction expressed in two&#x27;s complement, weight depends on USR_OFF_W in CTRL9 (18h). The offset can be applied to the output registers (see USR_OFF_ON_OUT bit in the CTRL9 (18h) register) or to the wake-up function input data (see USR_OFF_ON_WU bit in the WAKE_UP_THS (5Bh) register).The value must be in the range [-127 127].</td></tr></table>

## Y_OFS_USR (74h)

Accelerometer Y-axis user offset correction (R/W). The offset value set in the Y_OFS_USR offset register is internally subtracted from the acceleration value measured on the Y-axis 


Table 212. Y_OFS_USR register


<table><tr><td>Y_OFS_USR_7</td><td>Y_OFS_USR_6</td><td>Y_OFS_USR_5</td><td>Y_OFS_USR_4</td><td>Y_OFS_USR_3</td><td>Y_OFS_USR_2</td><td>Y_OFS_USR_1</td><td>Y_OFS_USR_0</td></tr></table>


Table 213. Y_OFS_USR register description


<table><tr><td>Y_OFS_USR_[7:0]</td><td>Accelerometer Y-axis user offset correction expressed in two’s complement, weight depends on USR_OFF_W in CTRL9 (18h). The offset can be applied to the output registers (see USR_OFF_ON_OUT bit in the CTRL9 (18h) register) or to the wake-up function input data (see USR_OFF_ON_WU bit in the WAKE_UP_THS (5Bh) register).The value must be in the range [-127 127].</td></tr></table>

## Z_OFS_USR (75h)

Accelerometer Z-axis user offset correction (R/W). The offset value set in the $Z \_ { \mathsf { O F S } }$ _USR offset register is internally subtracted from the acceleration value measured on the Z-axis. 


Table 214. Z_OFS_USR register


<table><tr><td>Z_OFSSUR_7</td><td>Z_OFSSUR_6</td><td>Z_OFSSUR_5</td><td>Z_OFSSUR_4</td><td>Z_OFSSUR_3</td><td>Z_OFSSUR_2</td><td>Z_OFSSUR_1</td><td>Z_OFSSUR_0</td></tr></table>

## Table 215. Z_OFS_USR register description

<table><tr><td>Z_OFS_USR_[7:0]</td><td>Accelerometer Z-axis user offset correction expressed in two’s complement, weight depends on USR_OFF_W in CTRL9 (18h). The offset can be applied to the output registers (see USR_OFF_ON_OUT bit in the CTRL9 (18h) register) or to the wake-up function input data (see USR_OFF_ON_WU bit in the WAKE_UP_THS (5Bh) register).The value must be in the range [-127 127].</td></tr></table>

## FIFO_DATA_OUT_TAG (78h)

FIFO tag register (R) 


Table 216. FIFO_DATA_OUT_TAG register


<table><tr><td>TAG_SENSOR_4</td><td>TAG_SENSOR_3</td><td>TAG_SENSOR_2</td><td>TAG_SENSOR_1</td><td>TAG_SENSOR_0</td><td>TAG_CNT_1</td><td>TAG_CNT_0</td><td>-</td></tr></table>


Table 217. FIFO_DATA_OUT_TAG register description


<table><tr><td>TAG_SENSOR_[4:0]</td><td>FIFO tag. Identifies the sensor in:FIFO_DATA_OUT_X_L (79h) and FIFO_DATA_OUT_X_H (7Ah), FIFO_DATA_OUT_Y_L (7Bh) andFIFO_DATA_OUT_Y_H (7Ch), and FIFO_DATA_OUT_Z_L (7Dh) and FIFO_DATA_OUT_Z_H (7Eh)For details, refer to Table 218.</td></tr><tr><td>TAG_CNT_[1:0]</td><td>2-bit counter which identifies sensor time slot</td></tr></table>


Table 218. FIFO tag


<table><tr><td>TAG_SENSOR_[4:0]</td><td>Sensor name</td></tr><tr><td>0x00</td><td>FIFO empty</td></tr><tr><td>0x01</td><td>Gyroscope NC</td></tr><tr><td>0x02</td><td>Accelerometer NC</td></tr><tr><td>0x03</td><td>Temperature</td></tr><tr><td>0x04</td><td>Timestamp</td></tr><tr><td>0x05</td><td>CFG_Change</td></tr><tr><td>0x06</td><td>Accelerometer NC_T_2</td></tr><tr><td>0x07</td><td>Accelerometer NC_T_1</td></tr><tr><td>0x08</td><td>Accelerometer 2xC</td></tr><tr><td>0x09</td><td>Accelerometer 3xC</td></tr><tr><td>0x0A</td><td>Gyroscope NC_T_2</td></tr><tr><td>0x0B</td><td>Gyroscope NC_T_1</td></tr><tr><td>0x0C</td><td>Gyroscope 2xC</td></tr><tr><td>0x0D</td><td>Gyroscope 3xC</td></tr><tr><td>0x0E</td><td>Sensor hub slave 0</td></tr><tr><td>0x0F</td><td>Sensor hub slave 1</td></tr><tr><td>0x10</td><td>Sensor hub slave 2</td></tr><tr><td>0x11</td><td>Sensor hub slave 3</td></tr><tr><td>0x12</td><td>Step counter</td></tr><tr><td>0x13</td><td>SFLP game rotation vector</td></tr><tr><td>0x16</td><td>SFLP gyroscope bias</td></tr><tr><td>0x17</td><td>SFLP gravity vector</td></tr><tr><td>0x19</td><td>Sensor hub nack</td></tr><tr><td>0x1A</td><td>MLC result</td></tr><tr><td>0x1B</td><td>MLC filter</td></tr><tr><td>0x1C</td><td>MLC feature</td></tr><tr><td>0x1D</td><td>Accelerometer dualC</td></tr><tr><td>0x1E</td><td>Enhanced EIS gyroscope</td></tr></table>

## FIFO_DATA_OUT_X_L (79h) and FIFO_DATA_OUT_X_H (7Ah)

FIFO data output X (R) 


Table 219. FIFO_DATA_OUT_X_H and FIFO_DATA_OUT_X_L registers


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 220. FIFO_DATA_OUT_X_H and FIFO_DATA_OUT_X_L register description


<table><tr><td>D[15:0]</td><td>FIFO X-axis output</td></tr></table>

## FIFO_DATA_OUT_Y_L (7Bh) and FIFO_DATA_OUT_Y_H (7Ch)

FIFO data output Y (R) 


Table 221. FIFO_DATA_OUT_Y_H and FIFO_DATA_OUT_Y_L registers


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 222. FIFO_DATA_OUT_Y_H and FIFO_DATA_OUT_Y_L register description


<table><tr><td>D[15:0]</td><td>FIFO Y-axis output</td></tr></table>

## FIFO_DATA_OUT_Z_L (7Dh) and FIFO_DATA_OUT_Z_H (7Eh)

FIFO data output Z (R) 


Table 223. FIFO_DATA_OUT_Z_H and FIFO_DATA_OUT_Z_L registers


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>

<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 224. FIFO_DATA_OUT_Z_H and FIFO_DATA_OUT_Z_L register description


<table><tr><td>D[15:0]</td><td>FIFO Z-axis output</td></tr></table>

## SPI2 register mapping

The table given below provides a list of the 8/16-bit registers embedded in the device and the corresponding addresses. 

All these registers are accessible from auxiliary SPI interface only. 


Table 225. SPI2 register address map


<table><tr><td rowspan="2">Name</td><td rowspan="2">Type</td><td colspan="2">Register address</td><td rowspan="2">Default</td><td rowspan="2">Comment</td></tr><tr><td>Hex</td><td>Binary</td></tr><tr><td>SPI2_WHO_AM_I</td><td>R</td><td>0F</td><td>00001111</td><td>01110000</td><td></td></tr><tr><td>SPI2_STATUS_REG_OIS</td><td>R</td><td>1E</td><td>00011110</td><td>output</td><td></td></tr><tr><td>SPI2_OUT_TEMP_L</td><td>R</td><td>20</td><td>00100000</td><td>output</td><td></td></tr><tr><td>SPI2_OUT_TEMP_H</td><td>R</td><td>21</td><td>00100001</td><td>output</td><td></td></tr><tr><td>SPI2_OUTX_L_G_OIS</td><td>R</td><td>22</td><td>00100010</td><td>output</td><td></td></tr><tr><td>SPI2_OUTX_H_G_OIS</td><td>R</td><td>23</td><td>00100011</td><td>output</td><td></td></tr><tr><td>SPI2_OUTY_L_G_OIS</td><td>R</td><td>24</td><td>00100100</td><td>output</td><td></td></tr><tr><td>SPI2_OUTY_H_G_OIS</td><td>R</td><td>25</td><td>00100101</td><td>output</td><td></td></tr><tr><td>SPI2_OUTZ_L_G_OIS</td><td>R</td><td>26</td><td>00100110</td><td>output</td><td></td></tr><tr><td>SPI2_OUTZ_H_G_OIS</td><td>R</td><td>27</td><td>00100111</td><td>output</td><td></td></tr><tr><td>SPI2_OUTX_L_A_OIS</td><td>R</td><td>28</td><td>00101000</td><td>output</td><td></td></tr><tr><td>SPI2_OUTX_H_A_OIS</td><td>R</td><td>29</td><td>00101001</td><td>output</td><td></td></tr><tr><td>SPI2_OUTY_L_A_OIS</td><td>R</td><td>2A</td><td>00101010</td><td>output</td><td></td></tr><tr><td>SPI2_OUTY_H_A_OIS</td><td>R</td><td>2B</td><td>00101011</td><td>output</td><td></td></tr><tr><td>SPI2_OUTZ_L_A_OIS</td><td>R</td><td>2C</td><td>00101100</td><td>output</td><td></td></tr><tr><td>SPI2_OUTZ_H_A_OIS</td><td>R</td><td>2D</td><td>00101101</td><td>output</td><td></td></tr><tr><td>SPI2_HANDSHAKE_CTRL</td><td>R/W</td><td>6E</td><td>01101110</td><td>00000000</td><td></td></tr><tr><td>SPI2_INT_OIS</td><td>R/W (SPI2 full-control mode)R (primary IF full-control mode)</td><td>6F</td><td>01101111</td><td>00000000</td><td></td></tr><tr><td>SPI2_CTRL1_OIS</td><td>R/W (SPI2 full-control mode)R (primary IF full-control mode)</td><td>70</td><td>01110000</td><td>00000000</td><td></td></tr><tr><td>SPI2_CTRL2_OIS</td><td>R/W (SPI2 full-control mode)R (primary IF full-control mode)</td><td>71</td><td>01110001</td><td>00000000</td><td></td></tr><tr><td>SPI2_CTRL3_OIS</td><td>R/W (SPI2 full-control mode)R (primary IF full-control mode)</td><td>72</td><td>01110010</td><td>00000000</td><td></td></tr></table>

Reserved registers must not be changed. Writing to those registers may cause permanent damage to the device. The content of the registers that are loaded at boot should not be changed. They contain the factory calibration values. Their content is automatically restored when the device is powered up. 

## 11 SPI2 register description

## 11.1 SPI2_WHO_AM_I (0Fh)

WHO_AM_I register (R). This is a read-only register. Its value is fixed at 70h. 


Table 226. SPI2_WhoAmI register


<table><tr><td>0</td><td>1</td><td>1</td><td>1</td><td>0</td><td>0</td><td>0</td><td>0</td></tr></table>

## 11.2 SPI2_STATUS_REG_OIS (1Eh)

The SPI2_STATUS_REG_OIS register is read by the auxiliary SPI (R). 


Table 227. SPI2_STATUS_REG_OIS register


<table><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>GYRO_SETTLING</td><td>GDA</td><td>XLDA</td></tr></table>


Table 228. SPI2_STATUS_REG_OIS description


<table><tr><td>GYRO_SETTLING</td><td>High when the gyroscope output is in the settling phase</td></tr><tr><td>GDA</td><td>Gyroscope data available (reset when one of the high parts of the output data is read)</td></tr><tr><td>XLDA</td><td>Accelerometer data available (reset when one of the high parts of the output data is read)</td></tr></table>

## SPI2_OUT_TEMP_L (20h) and SPI2_OUT_TEMP_H (21h)

Temperature data output register (R). L and H registers together express a 16-bit word in two’s complement. 


Table 229. SPI2_OUT_TEMP_L register


<table><tr><td>Temp7</td><td>Temp6</td><td>Temp5</td><td>Temp4</td><td>Temp3</td><td>Temp2</td><td>Temp1</td><td>Temp0</td></tr></table>


Table 230. SPI2_OUT_TEMP_H register


<table><tr><td>Temp15</td><td>Temp14</td><td>Temp13</td><td>Temp12</td><td>Temp11</td><td>Temp10</td><td>Temp9</td><td>Temp8</td></tr></table>


Table 231. SPI2_OUT_TEMP register description


<table><tr><td>Temp[15:0]</td><td>Temperature sensor output dataThe value is expressed as two&#x27;s complement sign extended on the MSB.</td></tr></table>

## 11.4

## SPI2_OUTX_L_G_OIS (22h) and SPI2_OUTX_H_G_OIS (23h)

Angular rate sensor pitch axis (X) angular rate output register (R). The value is expressed as a 16-bit word in two’s complement. 

Data are according to the gyroscope full-scale and ODR (7.68 kHz) settings of the OIS gyroscope. 


Table 232. SPI2_OUTX_L_G_OIS register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 233. SPI2_OUTX_H_G_OIS register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>


Table 234. SPI2_OUTX_H_G_OIS register description


<table><tr><td>D[15:0]</td><td>Gyroscope OIS chain pitch axis (X) angular rate output value</td></tr></table>

## SPI2_OUTY_L_G_OIS (24h) and SPI2_OUTY_H_G_OIS (25h)

Angular rate sensor roll axis (Y) angular rate output register (R). The value is expressed as a 16-bit word in two’s complement. 

Data are according to the gyroscope full-scale and ODR (7.68 kHz) settings of the OIS gyroscope. 


Table 235. SPI2_OUTY_L_G_OIS register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 236. SPI2_OUTY_H_G_OIS register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>


Table 237. SPI2_OUTY_H_G_OIS register description


<table><tr><td>D[15:0]</td><td>Gyroscope OIS chain roll axis (Y) angular rate output value</td></tr></table>

## SPI2_OUTZ_L_G_OIS (26h) and SPI2_OUTZ_H_G_OIS (27h)

Angular rate sensor yaw axis (Z) angular rate output register (R). The value is expressed as a 16-bit word in two’s complement. 

Data are according to the gyroscope full-scale and ODR (7.68 kHz) settings of the OIS gyroscope. 


Table 238. SPI2_OUTZ_L_G_OIS register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 239. SPI2_OUTZ_H_G_OIS register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>


Table 240. SPI2_OUTZ_H_G_OIS register description


<table><tr><td>D[15:0]</td><td>Gyroscope OIS chain yaw axis (Z) angular rate output value</td></tr></table>

## SPI2_OUTX_L_A_OIS (28h) and SPI2_OUTX_H_A_OIS (29h)

Linear acceleration sensor X-axis output register (R). The value is expressed as a 16-bit word in two’s complement. 

Data are according to the accelerometer full scale and ODR (7.68 kHz) settings of the OIS accelerometer. 


Table 241. SPI2_OUTX_L_A_OIS register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 242. SPI2_OUTX_H_A_OIS register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>

## Table 243. SPI2_OUTX_H_A_OIS register description

<table><tr><td>D[15:0]</td><td>Accelerometer OIS chain X-axis linear acceleration output value</td></tr></table>

## SPI2_OUTY_L_A_OIS (2Ah) and SPI2_OUTY_H_A_OIS (2Bh)

Linear acceleration sensor Y-axis output register (R). The value is expressed as a 16-bit word in two’s complement. 

Data are according to the accelerometer full scale and ODR (7.68 kHz) settings of the OIS accelerometer. 


Table 244. SPI2_OUTY_L_A_OIS register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 245. SPI2_OUTY_H_A_OIS register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>


Table 246. SPI2_OUTY_H_A_OIS register description


<table><tr><td>D[15:0]</td><td>Accelerometer OIS chain Y-axis linear acceleration output value</td></tr></table>

## SPI2_OUTZ_L_A_OIS (2Ch) and SPI2_OUTZ_H_A_OIS (2Dh)

Linear acceleration sensor Z-axis output register (R). The value is expressed as a 16-bit word in two’s complement. 

Data are according to the accelerometer full scale and ODR (7.68 kHz) settings of the OIS accelerometer. 


Table 247. SPI2_OUTZ_L_A_OIS register


<table><tr><td>D7</td><td>D6</td><td>D5</td><td>D4</td><td>D3</td><td>D2</td><td>D1</td><td>D0</td></tr></table>


Table 248. SPI2_OUTZ_H_A_OIS register


<table><tr><td>D15</td><td>D14</td><td>D13</td><td>D12</td><td>D11</td><td>D10</td><td>D9</td><td>D8</td></tr></table>


Table 249. SPI2_OUTZ_H_A_OIS register description


<table><tr><td>D[15:0]</td><td>Accelerometer OIS chain Z-axis linear acceleration output value</td></tr></table>

## SPI2_HANDSHAKE_CTRL (6Eh)

Control register (SPI2 side) for UI / SPI2 shared registers (R/W) 


Table 250. SPI2_HANDSHAKE_CTRL register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>SPI2_SHARED_REQ</td><td>SPI2_SHARED_ACK</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 


## Table 251. SPI2_HANDSHAKE_CTRL register description

<table><tr><td>SPI2_SHARED_REQ</td><td>This bit is used by the auxiliary SPI (SPI2) interface master to request access to the UI_SPI2_SHARED_0 (65h) through UI_SPI2_SHARED_5 (6Ah) registers. When the R/W operation is finished, the master must reset this bit.</td></tr><tr><td>SPI2_SHARED_ACK</td><td>Auxiliary SPI (SPI2) interface side. This bit acknowledges the handshake. If the primary interface is not accessing the shared registers, this bit is set to 1 by the device and the R/W operation on the UI_SPI2_SHARED_0 (65h) through UI_SPI2_SHARED_5 (6Ah) registers is allowed on the auxiliary SPI interface.</td></tr></table>

## 11.11

## SPI2_INT_OIS (6Fh)

OIS interrupt configuration register and self-test setting 

The auxiliary SPI interface can write this register when the OIS_CTRL_FROM_UI bit in the FUNC_CFG_ACCESS (01h) register is equal to 0 (SPI2 full-control mode); this register is read-only when the OIS_CTRL_FROM_UI bit is equal to 1 (primary IF full-control mode) and shows the content of the UI_INT_OIS (6Fh) register. 


Table 252. SPI2_INT_OIS register


<table><tr><td>INT2_DRDY_OIS</td><td>DRDY_MASK_OIS</td><td><eq>0^{(1)}</eq></td><td>ST_OIS_CLAMPDIS</td><td>ST_G_OIS_1</td><td>ST_G_OIS_0</td><td>ST_XL_OIS_1</td><td>ST_XL_OIS_0</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 253. SPI2_INT_OIS register description


<table><tr><td>INT2_DRDY_OIS</td><td>Enables OIS chain DRDY on INT2 pin. This setting has priority over all other INT2 settings.</td></tr><tr><td>DRDY_MASK_OIS</td><td>Enables / masks OIS data available. Default value: 0(0: disabled;1: masks OIS DRDY on pin (both accelerometer and gyroscope) until filter settling ends (accelerometer and gyroscope independently masked))</td></tr><tr><td>ST_OIS_CLAMPDIS</td><td>Disables OIS chain clamp during self-test. Default value: 0(0: All OIS chain outputs = 8000h during self-test;1: OIS chain self-test outputs)</td></tr><tr><td>ST_G_OIS_[1:0]</td><td>Gyroscope OIS chain self-test selection when the self-test is enabled and ST_OIS_CLAMPDIS = 0.(00: normal mode (default);01: positive sign self-test;10: normal mode;11: negative sign self-test)</td></tr><tr><td>ST_XL_OIS_[1:0]</td><td>Accelerometer OIS chain self-test selection; activated only if the accelerometer OIS chain is enabled.(00: normal mode (default);01: positive sign self-test;10: negative sign self-test;11: reserved)</td></tr></table>

## 11.12 SPI2_CTRL1_OIS (70h)

## OIS configuration register

The auxiliary SPI interface can write this register when the OIS_CTRL_FROM_UI bit in the FUNC_CFG_ACCESS (01h) register is equal to 0 (SPI2 full-control mode); this register is read-only when the OIS_CTRL_FROM_UI bit is equal to 1 (primary IF full-control mode) and shows the content of the UI_CTRL1_OIS (70h) register. 


Table 254. SPI2_CTRL1_OIS register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>SIM_OIS</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>OIS_XL_EN</td><td>OIS_G_EN</td><td>SPI2_READ_EN</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 255. SPI2_CTRL1_OIS register description


<table><tr><td>SIM_OIS</td><td>SPI2 3- or 4-wire interface. Default value: 0(0: 4-wire SPI2;1: 3-wire SPI2)</td></tr><tr><td>OIS_XL_EN</td><td>Enables accelerometer OIS chain. Default value: 0(0: accelerometer OIS chain disabled;1: accelerometer OIS chain enabled)</td></tr><tr><td>OIS_G_EN</td><td>Enables gyroscope OIS chain. Default value: 0(0: gyroscope OIS chain disabled;1: gyroscope OIS chain enabled)</td></tr><tr><td>SPI2_READ_EN</td><td>In auxiliary SPI full-control mode, enables auxiliary SPI for reading OIS data in registers <eq>\text{SPI2\_OUTX\_L\_G\_OIS} (22h)</eq> and <eq>\text{SPI2\_OUTX\_H\_G\_OIS} (23h)</eq> through Section 11.9 <eq>\text{SPI2\_OUTZ\_L\_A\_OIS} (2Ch)</eq> and <eq>\text{SPI2\_OUTZ\_H\_A\_OIS} (2Dh).</eq> Default value: 0(0: OIS data read from auxiliary SPI disabled;1: OIS data read from auxiliary SPI enabled)</td></tr></table>

## 11.13

## SPI2_CTRL2_OIS (71h)

## OIS configuration register

The auxiliary SPI interface can write this register when the OIS_CTRL_FROM_UI bit in the FUNC_CFG_ACCESS (01h) register is equal to 0 (SPI2 full-control mode); this register is read-only when the OIS_CTRL_FROM_UI bit is equal to 1 (primary IF full-control mode) and shows the content of the UI_CTRL2_OIS (71h) register. 


Table 256. SPI2_CTRL2_OIS register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>LPF1_G_OIS_BW_1</td><td>LPF1_G_OIS_BW_0</td><td>FS_G_OIS_2</td><td>FS_G_OIS_1</td><td>FS_G_OIS_0</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 257. SPI2_CTRL2_OIS register description


<table><tr><td>LPF1_G_OIS_BW_[1:0]</td><td>Gyroscope OIS digital LPF1 filter bandwidth selection. Refer to Table 258.</td></tr><tr><td>FS_G_OIS_[2:0]</td><td>Gyroscope OIS full-scale selection:(000: ±125 dps;001: ±250 dps;010: ±500 dps;011: ±1000 dps;100: ±2000 dps;101: reserved;110: reserved;111: reserved)</td></tr></table>


Table 258. Gyroscope OIS chain digital LPF1 filter bandwidth selection


<table><tr><td>LPF1_G_OIS_BW_[1:0]</td><td>Cutoff [Hz]</td><td>Phase @ 20 Hz [°]</td></tr><tr><td>00</td><td>293 Hz</td><td>-7.1°</td></tr><tr><td>01</td><td>217 Hz</td><td>-9.1°</td></tr><tr><td>10</td><td>158 Hz</td><td>-11.9°</td></tr><tr><td>11</td><td>476 Hz</td><td>-5.1°</td></tr></table>

## 11.14

## SPI2_CTRL3_OIS (72h)

## OIS configuration register

The auxiliary SPI interface can write this register when the OIS_CTRL_FROM_UI bit in the FUNC_CFG_ACCESS (01h) register is equal to 0 (SPI2 full-control mode); this register is read-only when the OIS_CTRL_FROM_UI bit is equal to 1 (primary IF full-control mode) and shows the content of the UI_CTRL3_OIS (72h) register. 


Table 259. SPI2_CTRL3_OIS register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>LPF_XL_OIS_BW_2</td><td>LPF_XL_OIS_BW_1</td><td>LPF_XL_OIS_BW_0</td><td><eq>0^{(1)}</eq></td><td>FS_XL_OIS_1</td><td>FS_XL_OIS_0</td></tr></table>

1. This bit must be set to 0 for the correct operation of the device. 


Table 260. SPI2_CTRL3_OIS register description


<table><tr><td>LPF_XL_OIS_BW_[2:0]</td><td>Selects accelerometer OIS channel bandwidth, see Table 261. Default value: 0</td></tr><tr><td>FS_XL_OIS_[1:0]</td><td>Selects accelerometer OIS channel full-scale:(00: ±2 g (default);01: ±4 g;10: ±8 g;11: ±16 g)</td></tr></table>

When the accelerometer full-scale value is selected only from the UI side it is readable also from the OIS side. 


Table 261. Accelerometer OIS channel bandwidth and phase


<table><tr><td>LPF_XL_OIS_BW_[2:0]</td><td>Typ. overall bandwidth [Hz]</td><td>Typ. overall phase [°]</td></tr><tr><td>000</td><td>749 Hz</td><td>-3.41 deg @ 20 Hz</td></tr><tr><td>001</td><td>539 Hz</td><td>-4.04 deg@ 20 Hz</td></tr><tr><td>010</td><td>342 Hz</td><td>-5.31 deg@ 20 Hz</td></tr><tr><td>011</td><td>162 Hz</td><td>-9.08 deg@ 20 Hz</td></tr><tr><td>100</td><td>78.5 Hz</td><td>-16.4 deg @ 20 Hz</td></tr><tr><td>101</td><td>38.6 Hz</td><td>-29.6 deg@ 20 Hz</td></tr><tr><td>110</td><td>19.3 Hz</td><td>-28.8 deg @ 10 Hz</td></tr><tr><td>111</td><td>9.8 Hz</td><td>-29.1 deg @ 5 Hz</td></tr></table>

## Embedded functions register mapping

The table given below provides a list of the registers for the embedded functions available in the device and the corresponding addresses. Embedded functions registers are accessible when EMB_FUNC_REG_ACCESS is set to 1 in FUNC_CFG_ACCESS (01h). 


Table 262. Register address map - embedded functions


<table><tr><td rowspan="2">Name</td><td rowspan="2">Type</td><td colspan="2">Register address</td><td rowspan="2">Default</td><td rowspan="2">Comment</td></tr><tr><td>Hex</td><td>Binary</td></tr><tr><td>PAGE_SEL</td><td>R/W</td><td>02</td><td>00000010</td><td>00000001</td><td></td></tr><tr><td>EMB_FUNC_EN_A</td><td>R/W</td><td>04</td><td>00000100</td><td>00000000</td><td></td></tr><tr><td>EMB_FUNC_EN_B</td><td>R/W</td><td>05</td><td>00000101</td><td>00000000</td><td></td></tr><tr><td>EMB_FUNC_EXEC_STATUS</td><td>R</td><td>07</td><td>00000111</td><td>output</td><td></td></tr><tr><td>PAGE_ADDRESS</td><td>R/W</td><td>08</td><td>00001000</td><td>00000000</td><td></td></tr><tr><td>PAGE_VALUE</td><td>R/W</td><td>09</td><td>00001001</td><td>00000000</td><td></td></tr><tr><td>EMB_FUNC_INT1</td><td>R/W</td><td>0A</td><td>00001010</td><td>00000000</td><td></td></tr><tr><td>FSM_INT1</td><td>R/W</td><td>0B</td><td>00001011</td><td>00000000</td><td></td></tr><tr><td>RESERVED</td><td>-</td><td>0C</td><td></td><td></td><td></td></tr><tr><td>MLC_INT1</td><td>R/W</td><td>0D</td><td>00001101</td><td>00000000</td><td></td></tr><tr><td>EMB_FUNC_INT2</td><td>R/W</td><td>0E</td><td>00001110</td><td>00000000</td><td></td></tr><tr><td>FSM_INT2</td><td>R/W</td><td>0F</td><td>00001111</td><td>00000000</td><td></td></tr><tr><td>RESERVED</td><td>-</td><td>10</td><td></td><td></td><td></td></tr><tr><td>MLC_INT2</td><td>R/W</td><td>11</td><td>00010001</td><td>00000000</td><td></td></tr><tr><td>EMB_FUNC_STATUS</td><td>R</td><td>12</td><td>00010010</td><td>output</td><td></td></tr><tr><td>FSM_STATUS</td><td>R</td><td>13</td><td>00010011</td><td>output</td><td></td></tr><tr><td>RESERVED</td><td>-</td><td>14</td><td></td><td></td><td></td></tr><tr><td>MLC_STATUS</td><td>R</td><td>15</td><td>00010101</td><td>output</td><td></td></tr><tr><td>PAGE_RW</td><td>R/W</td><td>17</td><td>00010111</td><td>00000000</td><td></td></tr><tr><td>RESERVED</td><td>-</td><td>18-43</td><td></td><td></td><td></td></tr><tr><td>EMB_FUNC_FIFO_EN_A</td><td>R/W</td><td>44</td><td>01000100</td><td>00000000</td><td></td></tr><tr><td>EMB_FUNC_FIFO_EN_B</td><td>R/W</td><td>45</td><td>01000101</td><td></td><td></td></tr><tr><td>FSM_ENABLE</td><td>R/W</td><td>46</td><td>01000110</td><td>00000000</td><td></td></tr><tr><td>RESERVED</td><td>-</td><td>47</td><td></td><td></td><td></td></tr><tr><td>FSM_LONG_COUNTER_L</td><td>R/W</td><td>48</td><td>01001000</td><td>00000000</td><td></td></tr><tr><td>FSM_LONG_COUNTER_H</td><td>R/W</td><td>49</td><td>01001001</td><td>00000000</td><td></td></tr><tr><td>RESERVED</td><td>-</td><td>4A</td><td></td><td></td><td></td></tr><tr><td>INT_ACK_MASK</td><td>R/W</td><td>4B</td><td>01001011</td><td>00000000</td><td></td></tr><tr><td>FSM_OUTS1</td><td>R</td><td>4C</td><td>01001100</td><td>output</td><td></td></tr><tr><td>FSM_OUTS2</td><td>R</td><td>4D</td><td>01001101</td><td>output</td><td></td></tr><tr><td>FSM_OUTS3</td><td>R</td><td>4E</td><td>01001110</td><td>output</td><td></td></tr><tr><td>FSM_OUTS4</td><td>R</td><td>4F</td><td>01001111</td><td>output</td><td></td></tr><tr><td>FSM_OUTS5</td><td>R</td><td>50</td><td>01010000</td><td>output</td><td></td></tr><tr><td>FSM_OUTS6</td><td>R</td><td>51</td><td>01010001</td><td>output</td><td></td></tr><tr><td>FSM_OUTS7</td><td>R</td><td>52</td><td>01010010</td><td>output</td><td></td></tr><tr><td>FSM_OUTS8</td><td>R</td><td>53</td><td>01010011</td><td>output</td><td></td></tr><tr><td>RESERVED</td><td>-</td><td>54- 5D</td><td></td><td></td><td></td></tr><tr><td>SFLP_ODR</td><td>R/W</td><td>5E</td><td>01011110</td><td>01011011</td><td></td></tr><tr><td>FSM_ODR</td><td>R/W</td><td>5F</td><td>01011111</td><td>01001011</td><td></td></tr><tr><td>MLC_ODR</td><td>R/W</td><td>60</td><td>01100000</td><td>00010101</td><td></td></tr><tr><td>STEP_COUNTER_L</td><td>R</td><td>62</td><td>01100010</td><td>output</td><td></td></tr><tr><td>STEP_COUNTER_H</td><td>R</td><td>63</td><td>01100011</td><td>output</td><td></td></tr><tr><td>EMB_FUNC_SRC</td><td>R/W</td><td>64</td><td>01100100</td><td>output</td><td></td></tr><tr><td>EMB_FUNC_INIT_A</td><td>R/W</td><td>66</td><td>01100110</td><td>00000000</td><td></td></tr><tr><td>EMB_FUNC_INIT_B</td><td>R/W</td><td>67</td><td>01100111</td><td>00000000</td><td></td></tr><tr><td>MLC1_SRC</td><td>R</td><td>70</td><td>01110000</td><td>output</td><td></td></tr><tr><td>MLC2_SRC</td><td>R</td><td>71</td><td>01110001</td><td>output</td><td></td></tr><tr><td>MLC3_SRC</td><td>R</td><td>72</td><td>01110010</td><td>output</td><td></td></tr><tr><td>MLC4_SRC</td><td>R</td><td>73</td><td>01110011</td><td>output</td><td></td></tr></table>

Reserved registers must not be changed. Writing to those registers may cause permanent damage to the device. The content of the registers that are loaded at boot should not be changed. They contain the factory calibration values. Their content is automatically restored when the device is powered up. 

## Embedded functions register description

## 13.1 PAGE_SEL (02h)

Enable advanced features dedicated page (R/W) 


Table 263. PAGE_SEL register


<table><tr><td>PAGE_SEL3</td><td>PAGE_SEL2</td><td>PAGE_SEL1</td><td>PAGE_SEL0</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>1^{(2)}</eq></td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 


2. This bit must be set to 1 for the correct operation of the device. 


Table 264. PAGE_SEL register description


<table><tr><td>PAGE_SEL[3:0]</td><td>Selects the advanced features dedicated page. Default value: 0000</td></tr></table>

## 13.2 EMB_FUNC_EN_A (04h)

Enable embedded functions register (R/W) 


Table 265. EMB_FUNC_EN_A register


<table><tr><td>MLC_BEFORE_FSM_EN</td><td><eq>0^{(1)}</eq></td><td>SIGN_MOTION_EN</td><td>TILT_EN</td><td>PEDO_EN</td><td><eq>0^{(1)}</eq></td><td>SFLP_GAME_EN</td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 266. EMB_FUNC_EN_A register description


<table><tr><td>MLC_BEFORE_FSM_EN(1)</td><td>Enables machine learning core function. When the machine learning core is enabled by setting this bit to 1, the MLC algorithms are executed before the FSM programs. Default value: 0(0: machine learning core function disabled;1: machine learning core function enabled and executed before FSM programs)</td></tr><tr><td>SIGN_MOTION_EN</td><td>Enables significant motion detection function. Default value: 0(0: significant motion detection function disabled;1: significant motion detection function enabled)</td></tr><tr><td>TILT_EN</td><td>Enables tilt calculation. Default value: 0(0: tilt algorithm disabled;1: tilt algorithm enabled)</td></tr><tr><td>PEDO_EN</td><td>Enables pedometer algorithm. Default value: 0(0: pedometer algorithm disabled;1: pedometer algorithm enabled)</td></tr><tr><td>SFLP_GAME_EN</td><td>Enables sensor fusion low-power algorithm for 6-axis (accelerometer + gyroscope) game rotation vector. Default value: 0(0: sensor fusion algorithm for 6-axis accelerometer + gyroscope disabled;1: sensor fusion algorithm for 6-axis accelerometer + gyroscope enabled)</td></tr></table>


1. MLC_EN bit in the EMB_FUNC_EN_B (05h) register must be set to 0 when using this bit. 


## 13.3

## EMB_FUNC_EN_B (05h)

Enable embedded functions register (R/W) 


Table 267. EMB_FUNC_EN_B register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>MLC_EN</td><td>FIFO_COMPR_EN</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>FSM_EN</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 268. EMB_FUNC_EN_B register description


<table><tr><td>MLC_EN<eq>^{(1)}</eq></td><td>Enables machine learning core function. When the machine learning core is enabled by setting this bit to 1, the MLC algorithms are executed after executing the FSM programs. Default value: 0(0: machine learning core function disabled;1: machine learning core function enabled and executed after FSM programs)</td></tr><tr><td>FIFO_COMPR_EN<eq>^{(2)}</eq></td><td>Enables FIFO compression function. Default value: 0(0: FIFO compression function disabled;1: FIFO compression function enabled)</td></tr><tr><td>FSM_EN</td><td>Enables finite state machine (FSM) function. Default value: 0(0: FSM function disabled; 1: FSM function enabled)</td></tr></table>


1. MLC_BEFORE_FSM_EN bit in the EMB_FUNC_EN_A (04h) register must be set to 0 when using this bit. 



2. This bit is activated if the FIFO_COMPR_RT_EN bit of FIFO_CTRL2 (08h) is set to 1. 


## 13.4

## EMB_FUNC_EXEC_STATUS (07h)

Embedded functions execution status register (R) 


Table 269. EMB_FUNC_EXEC_STATUS register


<table><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>0</td><td>EMB_FUNC_EXEC_OVR</td><td>EMB_FUNC_ENDOP</td></tr></table>


Table 270. EMB_FUNC_EXEC_STATUS register description


<table><tr><td>EMB_FUNC_EXEC_OVR</td><td>This bit is set to 1 when the execution of the embedded functions program exceeds maximum time (new data are generated before the end of the algorithms). Default value: 0</td></tr><tr><td>EMB_FUNC_ENDOP</td><td>When this bit is set to 1, no embedded function is running. Default value: 0</td></tr></table>

## PAGE_ADDRESS (08h)

Page address register (R/W) 


Table 271. PAGE_ADDRESS register


<table><tr><td>PAGE_ADDR7</td><td>PAGE_ADDR6</td><td>PAGE_ADDR5</td><td>PAGE_ADDR4</td><td>PAGE_ADDR3</td><td>PAGE_ADDR2</td><td>PAGE_ADDR1</td><td>PAGE_ADDR0</td></tr></table>

## Table 272. PAGE_ADDRESS register description

<table><tr><td>PAGE_ADDR[7:0]</td><td>After setting the bit PAGE_WRITE / PAGE_READ in register PAGE_RW (17h), this register is used to set the address of the register to be written/read in the advanced features page selected through the bits PAGE_SEL[3:0] in register PAGE_SEL (02h).</td></tr></table>

## PAGE_VALUE (09h)

Page value register (R/W) 


Table 273. PAGE_VALUE register


<table><tr><td>PAGE_VALUE7</td><td>PAGE_VALUE6</td><td>PAGE_VALUE5</td><td>PAGE_VALUE4</td><td>PAGE_VALUE3</td><td>PAGE_VALUE2</td><td>PAGE_VALUE1</td><td>PAGE_VALUE0</td></tr></table>


Table 274. PAGE_VALUE register description


<table><tr><td>PAGE_VALUE[7:0]</td><td>These bits are used to write (if the bit PAGE_WRITE = 1 in register PAGE_RW (17h)) or read (if the bit PAGE_READ = 1 in register PAGE_RW (17h)) the data at the address PAGE_ADDR[7:0] of the selected advanced features page.</td></tr></table>

## EMB_FUNC_INT1 (0Ah)

INT1 pin control register (R/W) 

Each bit in this register enables a signal to be carried over INT1. The pin's output supplies the OR combination o the selected signals. 


Table 275. EMB_FUNC_INT1 register


<table><tr><td>INT1_FSM_LC</td><td><eq>0^{(1)}</eq></td><td>INT1_SIG_MOT</td><td>INT1_TILT</td><td>INT1_STEP_DETECTOR</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 276. EMB_FUNC_INT1 register description


<table><tr><td>INT1_FSM_LC(1)</td><td>Routing FSM long counter timeout interrupt event to INT1. Default value: 0 (0: routing to INT1 disabled; 1: routing to INT1 enabled)</td></tr><tr><td>INT1_SIG_MOT(1)</td><td>Routing significant motion event to INT1. Default value: 0(0: routing to INT1 disabled; 1: routing to INT1 enabled)</td></tr><tr><td>INT1_TILT(1)</td><td>Routing tilt event to INT1. Default value: 0(0: routing to INT1 disabled; 1: routing to INT1 enabled)</td></tr><tr><td>INT1_STEP_DETECTOR(1)</td><td>Routing pedometer step recognition event to INT1. Default value: 0(0: routing to INT1 disabled; 1: routing to INT1 enabled)</td></tr></table>


1. This bit is activated if the INT1_EMB_FUNC bit of MD1_CFG (5Eh) is set to 1. 


## 13.8

## FSM_INT1 (0Bh)

INT1 pin control register (R/W) 

Each bit in this register enables a signal to be carried over INT1. The pin's output supplies the OR combination of the selected signals. 


Table 277. FSM_INT1 register


<table><tr><td>INT1_FSM8</td><td>INT1_FSM7</td><td>INT1_FSM6</td><td>INT1_FSM5</td><td>INT1_FSM4</td><td>INT1_FSM3</td><td>INT1_FSM2</td><td>INT1_FSM1</td></tr></table>


Table 278. FSM_INT1 register description


<table><tr><td><eq>INT1\_ FSM8^{(1)}</eq></td><td>Routing FSM8 interrupt event to INT1. Default value: 0(0: routing to INT1 disabled; 1: routing to INT1 enabled)</td></tr><tr><td><eq>INT1\_ FSM7^{(1)}</eq></td><td>Routing FSM7 interrupt event to INT1. Default value: 0(0: routing to INT1 disabled; 1: routing to INT1 enabled)</td></tr><tr><td><eq>INT1\_ FSM6^{(1)}</eq></td><td>Routing FSM6 interrupt event to INT1. Default value: 0(0: routing to INT1 disabled; 1: routing to INT1 enabled)</td></tr><tr><td><eq>INT1\_ FSM5^{(1)}</eq></td><td>Routing FSM5 interrupt event to INT1. Default value: 0(0: routing to INT1 disabled; 1: routing to INT1 enabled)</td></tr><tr><td><eq>INT1\_ FSM4^{(1)}</eq></td><td>Routing FSM4 interrupt event to INT1. Default value: 0(0: routing to INT1 disabled; 1: routing to INT1 enabled)</td></tr><tr><td><eq>INT1\_ FSM3^{(1)}</eq></td><td>Routing FSM3 interrupt event to INT1. Default value: 0(0: routing to INT1 disabled; 1: routing to INT1 enabled)</td></tr><tr><td><eq>INT1\_ FSM2^{(1)}</eq></td><td>Routing FSM2 interrupt event to INT1. Default value: 0(0: routing to INT1 disabled; 1: routing to INT1 enabled)</td></tr><tr><td><eq>INT1\_ FSM1^{(1)}</eq></td><td>Routing FSM1 interrupt event to INT1. Default value: 0(0: routing to INT1 disabled; 1: routing to INT1 enabled)</td></tr></table>


1. This bit is activated if the INT1_EMB_FUNC bit of MD1_CFG (5Eh) is set to 1. 


## MLC_INT1 (0Dh)

INT1 pin control register (R/W) 

Each bit in this register enables a signal to be carried over INT1. The pin's output supplies the OR combination of the selected signals. 


Table 279. MLC_INT1 register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>INT1_MLC4</td><td>INT1_MLC3</td><td>INT1_MLC2</td><td>INT1_MLC1</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 280. MLC_INT1 register description


<table><tr><td>INT1_MLC4</td><td>Routing MLC4 interrupt event to INT1. Default value: 0(0: routing to INT1 disabled; 1: routing to INT1 enabled)</td></tr><tr><td>INT1_MLC3</td><td>Routing MLC3 interrupt event to INT1. Default value: 0(0: routing to INT1 disabled; 1: routing to INT1 enabled)</td></tr><tr><td>INT1_MLC2</td><td>Routing MLC2 interrupt event to INT1. Default value: 0(0: routing to INT1 disabled; 1: routing to INT1 enabled)</td></tr><tr><td>INT1_MLC1</td><td>Routing MLC1 interrupt event to INT1. Default value: 0(0: routing to INT1 disabled; 1: routing to INT1 enabled)</td></tr></table>

## 13.10 EMB_FUNC_INT2 (0Eh)

INT2 pin control register (R/W) 

Each bit in this register enables a signal to be carried over INT2. The pin's output supplies the OR combination of the selected signals. 


Table 281. EMB_FUNC_INT2 register


<table><tr><td>INT2_FSM_LC</td><td><eq>0^{(1)}</eq></td><td>INT2_SIG_MOT</td><td>INT2_TILT</td><td>INT2_STEP_DETECTOR</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 282. EMB_FUNC_INT2 register description


<table><tr><td>INT2_FSM_LC(1)</td><td>Routing FSM long counter timeout interrupt event to INT2. Default value: 0 (0: routing to INT2 disabled; 1: routing to INT2 enabled)</td></tr><tr><td>INT2_SIG_MOT(1)</td><td>Routing significant motion event to INT2. Default value: 0(0: routing to INT2 disabled; 1: routing to INT2 enabled)</td></tr><tr><td>INT2_TILT(1)</td><td>Routing tilt event to INT2. Default value: 0(0: routing to INT2 disabled; 1: routing to INT2 enabled)</td></tr><tr><td>INT2_STEP_DETECTOR(1)</td><td>Routing pedometer step recognition event to INT2. Default value: 0(0: routing to INT2 disabled; 1: routing to INT2 enabled)</td></tr></table>


1. This bit is activated if the INT2_EMB_FUNC bit of MD2_CFG (5Fh) is set to 1. 


## 13.11 FSM_INT2 (0Fh)

INT2 pin control register (R/W) 

Each bit in this register enables a signal to be carried over INT2. The pin's output supplies the OR combination of the selected signals. 


Table 283. FSM_INT2 register


<table><tr><td>INT2_FSM8</td><td>INT2_FSM7</td><td>INT2_FSM6</td><td>INT2_FSM5</td><td>INT2_FSM4</td><td>INT2_FSM3</td><td>INT2_FSM2</td><td>INT2_FSM1</td></tr></table>


Table 284. FSM_INT2 register description


<table><tr><td><eq>INT2\_FSM8^{(1)}</eq></td><td>Routing FSM8 interrupt event to INT2. Default value: 0(0: routing to INT2 disabled; 1: routing to INT2 enabled)</td></tr><tr><td><eq>INT2\_FSM7^{(1)}</eq></td><td>Routing FSM7 interrupt event to INT2. Default value: 0(0: routing to INT2 disabled; 1: routing to INT2 enabled)</td></tr><tr><td><eq>INT2\_FSM6^{(1)}</eq></td><td>Routing FSM6 interrupt event to INT2. Default value: 0(0: routing to INT2 disabled; 1: routing to INT2 enabled)</td></tr><tr><td><eq>INT2\_FSM5^{(1)}</eq></td><td>Routing FSM5 interrupt event to INT2. Default value: 0(0: routing to INT2 disabled; 1: routing to INT2 enabled)</td></tr><tr><td><eq>INT2\_FSM4^{(1)}</eq></td><td>Routing FSM4 interrupt event to INT2. Default value: 0(0: routing to INT2 disabled; 1: routing to INT2 enabled)</td></tr><tr><td><eq>INT2\_FSM3^{(1)}</eq></td><td>Routing FSM3 interrupt event to INT2. Default value: 0(0: routing to INT2 disabled; 1: routing to INT2 enabled)</td></tr><tr><td><eq>INT2\_FSM2^{(1)}</eq></td><td>Routing FSM2 interrupt event to INT2. Default value: 0(0: routing to INT2 disabled; 1: routing to INT2 enabled)</td></tr><tr><td><eq>INT2\_FSM1^{(1)}</eq></td><td>Routing FSM1 interrupt event to INT2. Default value: 0(0: routing to INT2 disabled; 1: routing to INT2 enabled)</td></tr></table>


1. This bit is activated if the INT2_EMB_FUNC bit of MD2_CFG (5Fh) is set to 1. 


## 13.12

## MLC_INT2 (11h)

INT2 pin control register (R/W) 

Each bit in this register enables a signal to be carried over INT2. The pin's output supplies the OR combination of the selected signals. 


Table 285. MLC_INT2 register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>INT2_MLC4</td><td>INT2_MLC3</td><td>INT2_MLC2</td><td>INT2_MLC1</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 286. MLC_INT2 register description


<table><tr><td>INT2_MLC4</td><td>Routing MLC4 interrupt event to INT2. Default value: 0(0: routing to INT2 disabled; 1: routing to INT2 enabled)</td></tr><tr><td>INT2_MLC3</td><td>Routing MLC3 interrupt event to INT2. Default value: 0(0: routing to INT2 disabled; 1: routing to INT2 enabled)</td></tr><tr><td>INT2_MLC2</td><td>Routing MLC2 interrupt event to INT2. Default value: 0(0: routing to INT2 disabled; 1: routing to INT2 enabled)</td></tr><tr><td>INT2_MLC1</td><td>Routing MLC1 interrupt event to INT2. Default value: 0(0: routing to INT2 disabled; 1: routing to INT2 enabled)</td></tr></table>

## 13.13 EMB_FUNC_STATUS (12h)

Embedded function status register (R) 


Table 287. EMB_FUNC_STATUS register


<table><tr><td>IS_FSM_LC</td><td>0</td><td>IS_SIGMOT</td><td>IS_TILT</td><td>IS_STEP_DET</td><td>0</td><td>0</td><td>0</td></tr></table>


Table 288. EMB_FUNC_STATUS register description


<table><tr><td>IS_FSM_LC</td><td>Interrupt status bit for FSM long counter timeout interrupt event.(1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_SIGMOT</td><td>Interrupt status bit for significant motion detection(1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_TILT</td><td>Interrupt status bit for tilt detection(1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_STEP_DET</td><td>Interrupt status bit for step detection(1: interrupt detected; 0: no interrupt)</td></tr></table>

## 13.14

## FSM_STATUS (13h)

Finite state machine status register (R) 


Table 289. FSM_STATUS register


<table><tr><td>IS_FSM8</td><td>IS_FSM7</td><td>IS_FSM6</td><td>IS_FSM5</td><td>IS_FSM4</td><td>IS_FSM3</td><td>IS_FSM2</td><td>IS_FSM1</td></tr></table>


Table 290. FSM_STATUS register description


<table><tr><td>IS_FSM8</td><td>Interrupt status bit for FSM8 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM7</td><td>Interrupt status bit for FSM7 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM6</td><td>Interrupt status bit for FSM6 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM5</td><td>Interrupt status bit for FSM5 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM4</td><td>Interrupt status bit for FSM4 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM3</td><td>Interrupt status bit for FSM3 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM2</td><td>Interrupt status bit for FSM2 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_FSM1</td><td>Interrupt status bit for FSM1 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr></table>

## 13.15

## MLC_STATUS (15h)

Machine learning core status register (R) 


Table 291. MLC_STATUS register


<table><tr><td>0</td><td>0</td><td>0</td><td>0</td><td>IS_MLC4</td><td>IS_MLC3</td><td>IS_MLC2</td><td>IS_MLC1</td></tr></table>


Table 292. MLC_STATUS register description


<table><tr><td>IS_MLC4</td><td>Interrupt status bit for MLC4 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_MLC3</td><td>Interrupt status bit for MLC3 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_MLC2</td><td>Interrupt status bit for MLC2 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr><tr><td>IS_MLC1</td><td>Interrupt status bit for MLC1 interrupt event. (1: interrupt detected; 0: no interrupt)</td></tr></table>

## 13.16

## PAGE_RW (17h)

Enable read and write mode of advanced features dedicated page (R/W) 


Table 293. PAGE_RW register


<table><tr><td>EMB_FUNC_LIR</td><td>PAGE_WRITE</td><td>PAGE_READ</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 294. PAGE_RW register description


<table><tr><td>EMB_FUNC_LIR</td><td>Latched interrupt mode for embedded functions. Default value: 0(0: embedded functions interrupt request not latched;1: embedded functions interrupt request latched)</td></tr><tr><td>PAGE_WRITE</td><td>Enables writes to the selected advanced features dedicated page.(1) Default value: 0(1: enable; 0: disable)</td></tr><tr><td>PAGE_READ</td><td>Enables reads from the selected advanced features dedicated page.(1) Default value: 0(1: enable; 0: disable)</td></tr></table>


1. Page selected by PAGE_SEL[3:0] in PAGE_SEL (02h) register. 


## 13.17 EMB_FUNC_FIFO_EN_A (44h)

Embedded functions FIFO configuration register A (R/W) 


Table 295. EMB_FUNC_FIFO_EN_A register


<table><tr><td>MLC_FIFO_EN</td><td>STEP_COUNTER_FIFO_EN</td><td>SFLP_GBIAS_FIFO_EN</td><td>SFLP_GRAVITY_FIFO_EN</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>SFLP_GAME_FIFO_EN</td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 296. EMB_FUNC_FIFO_EN_A register description


<table><tr><td>MLC_FIFO_EN</td><td>Enables batching the machine learning core results in the FIFO buffer. Default value: 0(0: disabled; 1: enabled)</td></tr><tr><td>STEP_COUNTER_FIFO_EN</td><td>Enables batching the step counter values in the FIFO buffer. Default value: 0(0: disabled; 1: enabled)</td></tr><tr><td>SFLP_GBIAS_FIFO_EN</td><td>Enables batching the gyroscope bias values computed by the SFLP algorithm in the FIFO buffer. Default value: 0(0: disabled; 1: enabled)</td></tr><tr><td>SFLP_GRAVITY_FIFO_EN</td><td>Enables batching the gravity values computed by the SFLP algorithm in the FIFO buffer. Default value: 0(0: disabled; 1: enabled)</td></tr><tr><td>SFLP_GAME_FIFO_EN</td><td>Enables batching the game rotation vector (quaternion) values computed by the SFLP algorithm in the FIFO buffer. Default value: 0(0: disabled; 1: enabled)</td></tr></table>

## 13.18

## EMB_FUNC_FIFO_EN_B (45h)

Embedded functions FIFO configuration register B (R/W) 


Table 297. EMB_FUNC_FIFO_EN_B register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>MLC_FILTER_FEATURE_FIFO_EN</td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 298. EMB_FUNC_FIFO_EN_B register description


<table><tr><td>MLC_FILTER_FEATURE_FIFO_EN</td><td>Enables batching the machine learning core filters and features in the FIFO buffer. Default value: 0(0: disabled; 1: enabled)</td></tr></table>

## 13.19 FSM_ENABLE (46h)

Enable FSM register (R/W) 


Table 299. FSM_ENABLE register


<table><tr><td>FSM8_EN</td><td>FSM7_EN</td><td>FSM6_EN</td><td>FSM5_EN</td><td>FSM4_EN</td><td>FSM3_EN</td><td>FSM2_EN</td><td>FSM1_EN</td></tr></table>


Table 300. FSM_ENABLE register description


<table><tr><td>FSM8_EN</td><td>Enables FSM8. Default value: 0 (0: FSM8 disabled; 1: FSM8 enabled)</td></tr><tr><td>FSM7_EN</td><td>Enables FSM7. Default value: 0 (0: FSM7 disabled; 1: FSM7 enabled)</td></tr><tr><td>FSM6_EN</td><td>Enables FSM6. Default value: 0 (0: FSM6 disabled; 1: FSM6 enabled)</td></tr><tr><td>FSM5_EN</td><td>Enables FSM5. Default value: 0 (0: FSM5 disabled; 1: FSM5 enabled)</td></tr><tr><td>FSM4_EN</td><td>Enables FSM4. Default value: 0 (0: FSM4 disabled; 1: FSM4 enabled)</td></tr><tr><td>FSM3_EN</td><td>Enables FSM3. Default value: 0 (0: FSM3 disabled; 1: FSM3 enabled)</td></tr><tr><td>FSM2_EN</td><td>Enables FSM2. Default value: 0 (0: FSM2 disabled; 1: FSM2 enabled)</td></tr><tr><td>FSM1_EN</td><td>Enables FSM1. Default value: 0 (0: FSM1 disabled; 1: FSM1 enabled)</td></tr></table>

## 13.20

## FSM_LONG_COUNTER_L (48h) and FSM_LONG_COUNTER_H (49h)

## FSM long counter status register (R/W)

The long counter value is an unsigned integer value (16-bit format). 

## Table 301. FSM_LONG_COUNTER_L register

<table><tr><td>FSM_LC_7</td><td>FSM_LC_6</td><td>FSM_LC_5</td><td>FSM_LC_4</td><td>FSM_LC_3</td><td>FSM_LC_2</td><td>FSM_LC_1</td><td>FSM_LC_0</td></tr></table>

## Table 302. FSM_LONG_COUNTER_L register description

<table><tr><td>FSM_LC_[7:0]</td><td>Long counter current value (LSbyte). Default value: 00000000</td></tr></table>

## Table 303. FSM_LONG_COUNTER_H register

<table><tr><td>FSM_LC_15</td><td>FSM_LC_14</td><td>FSM_LC_13</td><td>FSM_LC_12</td><td>FSM_LC_11</td><td>FSM_LC_10</td><td>FSM_LC_9</td><td>FSM_LC_8</td></tr></table>

## Table 304. FSM_LONG_COUNTER_H register description

<table><tr><td>FSM_LC_[15:8]</td><td>Long counter current value (MSbyte). Default value: 00000000</td></tr></table>

## 13.21

## INT_ACK_MASK (4Bh)

Reset status register (R/W) 


Table 305. INT_ACK_MASK register


<table><tr><td>IACK_MASK7</td><td>IACK_MASK6</td><td>IACK_MASK5</td><td>IACK_MASK4</td><td>IACK_MASK3</td><td>IACK_MASK2</td><td>IACK_MASK1</td><td>IACK_MASK0</td></tr></table>


Table 306. INT_ACK_MASK register description


<table><tr><td>IACK_MASK7</td><td>If set to 1, when reading the EMB_FUNC_STATUS (12h) / EMB_FUNC_STATUS_MAINPAGE (49h), FSM_STATUS (13h) / FSM_STATUS_MAINPAGE (4Ah) and MLC_STATUS (15h) /MLC_STATUS_MAINPAGE (4Bh) registers in latched mode (when the EMB_FUNC_LIR bit is set to 1 in the PAGE_RW (17h) register), bit 7 of the status register is not reset. When this bit is set to 0, bit 7 of the status register is reset. Default value: 0</td></tr><tr><td>IACK_MASK6</td><td>If set to 1, when reading the EMB_FUNC_STATUS (12h) / EMB_FUNC_STATUS_MAINPAGE (49h), FSM_STATUS (13h) / FSM_STATUS_MAINPAGE (4Ah) and MLC_STATUS (15h) /MLC_STATUS_MAINPAGE (4Bh) registers in latched mode (when the EMB_FUNC_LIR bit is set to 1 in the PAGE_RW (17h) register), bit 6 of the status register is not reset. When this bit is set to 0, bit 6 of the status register is reset. Default value: 0</td></tr><tr><td>IACK_MASK5</td><td>If set to 1, when reading the EMB_FUNC_STATUS (12h) / EMB_FUNC_STATUS_MAINPAGE (49h), FSM_STATUS (13h) / FSM_STATUS_MAINPAGE (4Ah) and MLC_STATUS (15h) /MLC_STATUS_MAINPAGE (4Bh) registers in latched mode (when the EMB_FUNC_LIR bit is set to 1 in the PAGE_RW (17h) register), bit 5 of the status register is not reset. When this bit is set to 0, bit 5 of the status register is reset. Default value: 0</td></tr><tr><td>IACK_MASK4</td><td>If set to 1, when reading the EMB_FUNC_STATUS (12h) / EMB_FUNC_STATUS_MAINPAGE (49h), FSM_STATUS (13h) / FSM_STATUS_MAINPAGE (4Ah) and MLC_STATUS (15h) /MLC_STATUS_MAINPAGE (4Bh) registers in latched mode (when the EMB_FUNC_LIR bit is set to 1 in the PAGE_RW (17h) register), bit 4 of the status register is not reset. When this bit is set to 0, bit 4 of the status register is reset. Default value: 0</td></tr><tr><td>IACK_MASK3</td><td>If set to 1, when reading the EMB_FUNC_STATUS (12h) / EMB_FUNC_STATUS_MAINPAGE (49h), FSM_STATUS (13h) / FSM_STATUS_MAINPAGE (4Ah) and MLC_STATUS (15h) /MLC_STATUS_MAINPAGE (4Bh) registers in latched mode (when the EMB_FUNC_LIR bit is set to 1 in the PAGE_RW (17h) register), bit 3 of the status register is not reset. When this bit is set to 0, bit 3 of the status register is reset. Default value: 0</td></tr><tr><td>IACK_MASK2</td><td>If set to 1, when reading the EMB_FUNC_STATUS (12h) / EMB_FUNC_STATUS_MAINPAGE (49h), FSM_STATUS (13h) / FSM_STATUS_MAINPAGE (4Ah) and MLC_STATUS (15h) /MLC_STATUS_MAINPAGE (4Bh) registers in latched mode (when the EMB_FUNC_LIR bit is set to 1 in the PAGE_RW (17h) register), bit 2 of the status register is not reset. When this bit is set to 0, bit 2 of the status register is reset. Default value: 0</td></tr><tr><td>IACK_MASK1</td><td>If set to 1, when reading the EMB_FUNC_STATUS (12h) / EMB_FUNC_STATUS_MAINPAGE (49h), FSM_STATUS (13h) / FSM_STATUS_MAINPAGE (4Ah) and MLC_STATUS (15h) /MLC_STATUS_MAINPAGE (4Bh) registers in latched mode (when the EMB_FUNC_LIR bit is set to 1 in the PAGE_RW (17h) register), bit 1 of the status register is not reset. When this bit is set to 0, bit 1 of the status register is reset. Default value: 0</td></tr><tr><td>IACK_MASK0</td><td>If set to 1, when reading the EMB_FUNC_STATUS (12h) / EMB_FUNC_STATUS_MAINPAGE (49h), FSM_STATUS (13h) / FSM_STATUS_MAINPAGE (4Ah) and MLC_STATUS (15h) /MLC_STATUS_MAINPAGE (4Bh) registers in latched mode (when the EMB_FUNC_LIR bit is set to 1 in the PAGE_RW (17h) register), bit 0 of the status register is not reset. When this bit is set to 0, bit 0 of the status register is reset. Default value: 0</td></tr></table>

## 13.22

## FSM_OUTS1 (4Ch)

FSM1 output register (R) 


Table 307. FSM_OUTS1 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 308. FSM_OUTS1 register description


<table><tr><td>P_X</td><td>FSM1 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM1 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM1 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM1 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM1 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM1 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM1 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM1 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

## 13.23

## FSM_OUTS2 (4Dh)

FSM2 output register (R) 


Table 309. FSM_OUTS2 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 310. FSM_OUTS2 register description


<table><tr><td>P_X</td><td>FSM2 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM2 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM2 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM2 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM2 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM2 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM2 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM2 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

## 13.24

## FSM_OUTS3 (4Eh)

FSM3 output register (R) 


Table 311. FSM_OUTS3 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 312. FSM_OUTS3 register description


<table><tr><td>P_X</td><td>FSM3 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM3 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM3 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM3 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM3 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM3 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM3 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM3 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

## FSM_OUTS4 (4Fh)

FSM4 output register (R) 


Table 313. FSM_OUTS4 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 314. FSM_OUTS4 register description


<table><tr><td>P_X</td><td>FSM4 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM4 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM4 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM4 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM4 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM4 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM4 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM4 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

## 13.26

## FSM_OUTS5 (50h)

FSM5 output register (R) 


Table 315. FSM_OUTS5 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 316. FSM_OUTS5 register description


<table><tr><td>P_X</td><td>FSM5 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM5 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM5 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM5 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM5 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM5 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM5 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM5 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

## 13.27 FSM_OUTS6 (51h)

FSM6 output register (R) 


Table 317. FSM_OUTS6 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 318. FSM_OUTS6 register description


<table><tr><td>P_X</td><td>FSM6 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM6 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM6 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM6 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM6 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM6 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM6 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM6 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

## 13.28

## FSM_OUTS7 (52h)

FSM7 output register (R) 


Table 319. FSM_OUTS7 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 320. FSM_OUTS7 register description


<table><tr><td>P_X</td><td>FSM7 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM7 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM7 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM7 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM7 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM7 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM7 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM7 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

## FSM_OUTS8 (53h)

FSM8 output register (R) 


Table 321. FSM_OUTS8 register


<table><tr><td>P_X</td><td>N_X</td><td>P_Y</td><td>N_Y</td><td>P_Z</td><td>N_Z</td><td>P_V</td><td>N_V</td></tr></table>


Table 322. FSM_OUTS8 register description


<table><tr><td>P_X</td><td>FSM8 output: positive event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_X</td><td>FSM8 output: negative event detected on the X-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Y</td><td>FSM8 output: positive event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Y</td><td>FSM8 output: negative event detected on the Y-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_Z</td><td>FSM8 output: positive event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>N_Z</td><td>FSM8 output: negative event detected on the Z-axis. (0: event not detected; 1: event detected)</td></tr><tr><td>P_V</td><td>FSM8 output: positive event detected on the vector. (0: event not detected; 1: event detected)</td></tr><tr><td>N_V</td><td>FSM8 output: negative event detected on the vector. (0: event not detected; 1: event detected)</td></tr></table>

## 13.30

## SFLP_ODR (5Eh)

Sensor fusion low-power output data rate configuration register (R/W) 


Table 323. SFLP_ODR register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>1^{(2)}</eq></td><td>SFLP_GAME_ODR_2</td><td>SFLP_GAME_ODR_1</td><td>SFLP_GAME_ODR_0</td><td><eq>0^{(1)}</eq></td><td><eq>1^{(2)}</eq></td><td><eq>1^{(2)}</eq></td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 


2. This bit must be set to 1 for the correct operation of the device. 


Table 324. SFLP_ODR register description


<table><tr><td>SFLP_GAME_ODR_[2:0]</td><td>ODR configuration of the SFLP game algorithm:(000: 15 Hz;001: 30 Hz;010: 60 Hz;011: 120 Hz (default);100: 240 Hz;101: 480 Hz)</td></tr></table>

## 13.31 FSM_ODR (5Fh)

Finite state machine output data rate configuration register (R/W) 


Table 325. FSM_ODR register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>1^{(2)}</eq></td><td>FSM_ODR_2</td><td>FSM_ODR_1</td><td>FSM_ODR_0</td><td><eq>0^{(1)}</eq></td><td><eq>1^{(2)}</eq></td><td><eq>1^{(2)}</eq></td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 


2. This bit must be set to 1 for the correct operation of the device. 


Table 326. FSM_ODR register description


<table><tr><td>FSM_ODR_[2:0]</td><td>Finite state machine ODR configuration:(000: 15 Hz;001: 30 Hz (default);010: 60 Hz;011: 120 Hz;100: 240 Hz;101: 480 Hz;110: 960 Hz)</td></tr></table>

## 13.32

## MLC_ODR (60h)

Machine learning core output data rate configuration register (R/W) 


Table 327. MLC_ODR register


<table><tr><td><eq>0^{(1)}</eq></td><td>MLC_ODR_2</td><td>MLC_ODR_1</td><td>MLC_ODR_0</td><td><eq>0^{(1)}</eq></td><td><eq>1^{(2)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>1^{(2)}</eq></td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



2. This bit must be set to 1 for the correct operation of the device. 



Table 328. MLC_ODR register description


<table><tr><td>MLC_ODR_[2:0]</td><td>Machine learning core ODR configuration:(000: 15 Hz;001: 30 Hz (default);010: 60 Hz;011: 120 Hz;100: 240 Hz)</td></tr></table>

## STEP_COUNTER_L (62h) and STEP_COUNTER_H (63h)

Step counter output register (R) 


Table 329. STEP_COUNTER_L register


<table><tr><td>STEP_7</td><td>STEP_6</td><td>STEP_5</td><td>STEP_4</td><td>STEP_3</td><td>STEP_2</td><td>STEP_1</td><td>STEP_0</td></tr></table>


Table 330. STEP_COUNTER_L register description


<table><tr><td>STEP_[7:0]</td><td>Step counter output (LSbyte)</td></tr></table>


Table 331. STEP_COUNTER_H register


<table><tr><td>STEP_15</td><td>STEP_14</td><td>STEP_13</td><td>STEP_12</td><td>STEP_11</td><td>STEP_10</td><td>STEP_9</td><td>STEP_8</td></tr></table>


Table 332. STEP_COUNTER_H register description


<table><tr><td>STEP_[15:8]</td><td>Step counter output (MSbyte)</td></tr></table>

## 13.34

## EMB_FUNC_SRC (64h)

Embedded function source register (R/W) 


Table 333. EMB_FUNC_SRC register


<table><tr><td>PEDO_RST_STEP</td><td><eq>0^{(1)}</eq></td><td>STEP_DETECTED</td><td>STEP_COUNT_DELTA_IA</td><td>STEP_OVERFLOW</td><td>STEPCOUNTER_BIT_SET</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 334. EMB_FUNC_SRC register description


<table><tr><td>PEDO_RST_STEP</td><td>Reset pedometer step counter. Read/write bit.(0: disabled; 1: enabled)</td></tr><tr><td>STEP_DETECTED</td><td>Step detector event detection status. Read-only bit.(0: step detection event not detected; 1: step detection event detected)</td></tr><tr><td>STEP_COUNT_DELTA_IA</td><td>Pedometer step recognition on delta time status. Read-only bit.(0: no step recognized during delta time;1: at least one step recognized during delta time)</td></tr><tr><td>STEP_OVERFLOW</td><td>Step counter overflow status. Read-only bit.(0: step counter value <eq>&lt; 2^{16}</eq>; 1: step counter value reached <eq>2^{16}</eq>)</td></tr><tr><td>STEPCOUNTER_BIT_SET</td><td>This bit is equal to 1 when the step count is increased. If a timer period is programmed in PEDO_SC_DELTAT_L (D0h) and PEDO_SC_DELTAT_H (D1h) embedded advanced features (page 1) registers, this bit is kept at 0.Read-only bit.</td></tr></table>

## 13.35

## EMB_FUNC_INIT_A (66h)

Embedded functions initialization register (R/W) 


Table 335. EMB_FUNC_INIT_A register


<table><tr><td>MLC_BEFORE_FSM_INIT</td><td><eq>0^{(1)}</eq></td><td>SIG_MOT_INIT</td><td>TILT_INIT</td><td>STEP_DET_INIT</td><td><eq>0^{(1)}</eq></td><td>SFLP_GAME_INIT</td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 336. EMB_FUNC_INIT_A register description


<table><tr><td>MLC_BEFORE_FSM_INIT</td><td>Machine learning core initialization request (MLC executed before FSM). Default value: 0</td></tr><tr><td>SIG_MOT_INIT</td><td>Significant motion detection algorithm initialization request. Default value: 0</td></tr><tr><td>TILT_INIT</td><td>Tilt algorithm initialization request. Default value: 0</td></tr><tr><td>STEP_DET_INIT</td><td>Pedometer step counter/detector algorithm initialization request. Default value: 0</td></tr><tr><td>SFLP_GAME_INIT</td><td>SFLP game algorithm initialization request. Default value: 0</td></tr></table>

## 13.36 EMB_FUNC_INIT_B (67h)

Embedded functions initialization register (R/W) 


Table 337. EMB_FUNC_INIT_B register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>MLC_INIT</td><td>FIFO_COMPR_INIT</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>FSM_INIT</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 338. EMB_FUNC_INIT_B register description


<table><tr><td>MLC_INIT</td><td>Machine learning core initialization request (MLC executed after FSM). Default value: 0</td></tr><tr><td>FIFO_COMPR_INIT</td><td>FIFO compression feature initialization request. Default value: 0</td></tr><tr><td>FSM_INIT</td><td>FSM initialization request. Default value: 0</td></tr></table>

## 13.37

## MLC1_SRC (70h)

Machine learning core source register (R) 


Table 339. MLC1_SRC register


<table><tr><td>MLC1_SRC_7</td><td>MLC1_SRC_6</td><td>MLC1_SRC_5</td><td>MLC1_SRC_4</td><td>MLC1_SRC_3</td><td>MLC1_SRC_2</td><td>MLC1_SRC_1</td><td>MLC1_SRC_0</td></tr></table>


Table 340. MLC1_SRC register description


<table><tr><td>MLC1_SRC_[7:0]</td><td>Output value of MLC1 decision tree</td></tr></table>

## 13.38

## MLC2_SRC (71h)

Machine learning core source register (R) 


Table 341. MLC2_SRC register


<table><tr><td>MLC2_SRC_7</td><td>MLC2_SRC_6</td><td>MLC2_SRC_5</td><td>MLC2_SRC_4</td><td>MLC2_SRC_3</td><td>MLCS2_SRC_2</td><td>MLC2_SRC_1</td><td>MLC2_SRC_0</td></tr></table>


Table 342. MLC2_SRC register description


<table><tr><td>MLC2_SRC_[7:0]</td><td>Output value of MLC2 decision tree</td></tr></table>

## 13.39

## MLC3_SRC (72h)

Machine learning core source register (R) 


Table 343. MLC3_SRC register


<table><tr><td>MLC3_SRC_7</td><td>MLC3_SRC_6</td><td>MLC3_SRC_5</td><td>MLC3_SRC_4</td><td>MLC3_SRC_3</td><td>MLC3_SRC_2</td><td>MLC3_SRC_1</td><td>MLC3_SRC_0</td></tr></table>


Table 344. MLC3_SRC register description


<table><tr><td>MLC3_SRC_[7:0]</td><td>Output value of MLC3 decision tree</td></tr></table>

## 13.40

## MLC4_SRC (73h)

Machine learning core source register (R) 


Table 345. MLC4_SRC register


<table><tr><td>MLC4_SRC_7</td><td>MLC4_SRC_6</td><td>MLC4_SRC_5</td><td>MLC4_SRC_4</td><td>MLC4_SRC_3</td><td>MLC4_SRC_2</td><td>MLC4_SRC_1</td><td>MLC4_SRC_0</td></tr></table>


Table 346. MLC4_SRC register description


<table><tr><td>MLC4_SRC_[7:0]</td><td>Output value of MLC4 decision tree</td></tr></table>

## Embedded advanced features pages

The table given below provides a list of the registers for the embedded advanced features page 0. These registers are accessible when PAGE_SEL[3:0] are set to 0000 in PAGE_SEL (02h). 

External sensor offset compensation registers and transformation matrix correction registers affect FSM data only. When these registers are set with their default values, no compensation is applied. 


Table 347. Register address map - embedded advanced features page 0


<table><tr><td rowspan="2">Name</td><td rowspan="2">Type</td><td colspan="2">Register address</td><td rowspan="2">Default</td><td rowspan="2">Comment</td></tr><tr><td>Hex</td><td>Binary</td></tr><tr><td>SFLP_GAME_GBIASX_L</td><td>R/W</td><td>6E</td><td>01101110</td><td>00000000</td><td></td></tr><tr><td>SFLP_GAME_GBIASX_H</td><td>R/W</td><td>6F</td><td>01101111</td><td>00000000</td><td></td></tr><tr><td>SFLP_GAME_GBIASY_L</td><td>R/W</td><td>70</td><td>01110000</td><td>00000000</td><td></td></tr><tr><td>SFLP_GAME_GBIASY_H</td><td>R/W</td><td>71</td><td>01110001</td><td>00000000</td><td></td></tr><tr><td>SFLP_GAME_GBIASZ_L</td><td>R/W</td><td>72</td><td>01110010</td><td>00000000</td><td></td></tr><tr><td>SFLP_GAME_GBIASZ_H</td><td>R/W</td><td>73</td><td>01110011</td><td>00000000</td><td></td></tr><tr><td>FSM_EXT_SENSITIVITY_L</td><td>R/W</td><td>BA</td><td>10111010</td><td>00100100</td><td></td></tr><tr><td>FSM_EXT_SENSITIVITY_H</td><td>R/W</td><td>BB</td><td>10111011</td><td>00010110</td><td></td></tr><tr><td>FSM_EXT_OFFX_L</td><td>R/W</td><td>C0</td><td>11000000</td><td>00000000</td><td></td></tr><tr><td>FSM_EXT_OFFX_H</td><td>R/W</td><td>C1</td><td>11000001</td><td>00000000</td><td></td></tr><tr><td>FSM_EXT_OFFY_L</td><td>R/W</td><td>C2</td><td>11000010</td><td>00000000</td><td></td></tr><tr><td>FSM_EXT_OFFY_H</td><td>R/W</td><td>C3</td><td>11000011</td><td>00000000</td><td></td></tr><tr><td>FSM_EXT_OFFZ_L</td><td>R/W</td><td>C4</td><td>11000100</td><td>00000000</td><td></td></tr><tr><td>FSM_EXT_OFFZ_H</td><td>R/W</td><td>C5</td><td>11000101</td><td>00000000</td><td></td></tr><tr><td>FSM_EXT_MATRIX_XX_L</td><td>R/W</td><td>C6</td><td>11000110</td><td>00000000</td><td></td></tr><tr><td>FSM_EXT_MATRIX_XX_H</td><td>R/W</td><td>C7</td><td>11000111</td><td>00111100</td><td></td></tr><tr><td>FSM_EXT_MATRIX_XY_L</td><td>R/W</td><td>C8</td><td>11001000</td><td>00000000</td><td></td></tr><tr><td>FSM_EXT_MATRIX_XY_H</td><td>R/W</td><td>C9</td><td>11001001</td><td>00000000</td><td></td></tr><tr><td>FSM_EXT_MATRIX_XZ_L</td><td>R/W</td><td>CA</td><td>11001010</td><td>00000000</td><td></td></tr><tr><td>FSM_EXT_MATRIX_XZ_H</td><td>R/W</td><td>CB</td><td>11001011</td><td>00000000</td><td></td></tr><tr><td>FSM_EXT_MATRIX_YY_L</td><td>R/W</td><td>CC</td><td>11001100</td><td>00000000</td><td></td></tr><tr><td>FSM_EXT_MATRIX_YY_H</td><td>R/W</td><td>CD</td><td>11001101</td><td>00111100</td><td></td></tr><tr><td>FSM_EXT_MATRIX_YZ_L</td><td>R/W</td><td>CE</td><td>11001110</td><td>00000000</td><td></td></tr><tr><td>FSM_EXT_MATRIX_YZ_H</td><td>R/W</td><td>CF</td><td>11001111</td><td>00000000</td><td></td></tr><tr><td>FSM_EXT_MATRIX_ZZ_L</td><td>R/W</td><td>D0</td><td>11010000</td><td>00000000</td><td></td></tr><tr><td>FSM_EXT_MATRIX_ZZ_H</td><td>R/W</td><td>D1</td><td>11010001</td><td>00111100</td><td></td></tr><tr><td>EXT_CFG_A</td><td>R/W</td><td>D4</td><td>11010100</td><td>00000101</td><td></td></tr><tr><td>EXT_CFG_B</td><td>R/W</td><td>D5</td><td>11010101</td><td>00000010</td><td></td></tr></table>

The following table provides a list of the registers for the embedded advanced features page 1. These registers are accessible when PAGE_SEL[3:0] are set to 0001 in PAGE_SEL (02h). 


Table 348. Register address map - embedded advanced features page 1


<table><tr><td rowspan="2">Name</td><td rowspan="2">Type</td><td colspan="2">Register address</td><td rowspan="2">Default</td><td rowspan="2">Comment</td></tr><tr><td>Hex</td><td>Binary</td></tr><tr><td>FSM_LC_TIMEOUT_L</td><td>R/W</td><td>7A</td><td>01111010</td><td>00000000</td><td></td></tr><tr><td>FSM_LC_TIMEOUT_H</td><td>R/W</td><td>7B</td><td>01111011</td><td>00000000</td><td></td></tr><tr><td>FSM_PROGRAMS</td><td>R/W</td><td>7C</td><td>01111100</td><td>00000000</td><td></td></tr><tr><td>FSM_START_ADD_L</td><td>R/W</td><td>7E</td><td>01111110</td><td>00000000</td><td></td></tr><tr><td>FSM_START_ADD_H</td><td>R/W</td><td>7F</td><td>01111111</td><td>00000000</td><td></td></tr><tr><td>PEDO_CMD_REG</td><td>R/W</td><td>83</td><td>10000011</td><td>00000000</td><td></td></tr><tr><td>PEDO_DEB_STEPS_CONF</td><td>R/W</td><td>84</td><td>10000100</td><td>00001010</td><td></td></tr><tr><td>PEDO_SC_DELTAT_L</td><td>R/W</td><td>D0</td><td>11010000</td><td>00000000</td><td></td></tr><tr><td>PEDO_SC_DELTAT_H</td><td>R/W</td><td>D1</td><td>11010001</td><td>00000000</td><td></td></tr><tr><td>MLC_EXT_SENSITIVITY_L</td><td>R/W</td><td>E8</td><td>11101000</td><td>00000000</td><td></td></tr><tr><td>MLC_EXT_SENSITIVITY_H</td><td>R/W</td><td>E9</td><td>11101001</td><td>00111100</td><td></td></tr></table>

The following table provides a list of the registers for the embedded advanced features page 2. These registers are accessible when PAGE_SEL[3:0] are set to 0010 in PAGE_SEL (02h). 


Table 349. Register address map - embedded advanced features page 2


<table><tr><td rowspan="2">Name</td><td rowspan="2">Type</td><td colspan="2">Register address</td><td rowspan="2">Default</td><td rowspan="2">Comment</td></tr><tr><td>Hex</td><td>Binary</td></tr><tr><td>EXT_FORMAT</td><td>R/W</td><td>00</td><td>00000000</td><td>00000000</td><td></td></tr><tr><td>EXT_3BYTE_SENSITIVITY_L</td><td>R/W</td><td>02</td><td>00000010</td><td>00000000</td><td></td></tr><tr><td>EXT_3BYTE_SENSITIVITY_H</td><td>R/W</td><td>03</td><td>00000011</td><td>00001100</td><td></td></tr><tr><td>EXT_3BYTE_OFFSET_XL</td><td>R/W</td><td>06</td><td>00000110</td><td>00000000</td><td></td></tr><tr><td>EXT_3BYTE_OFFSET_L</td><td>R/W</td><td>07</td><td>00000111</td><td>01010100</td><td></td></tr><tr><td>EXT_3BYTE_OFFSET_H</td><td>R/W</td><td>08</td><td>00001000</td><td>00111111</td><td></td></tr></table>

Reserved registers must not be changed. Writing to those registers may cause permanent damage to the device. The content of the registers that are loaded at boot should not be changed. They contain the factory calibration values. Their content is automatically restored when the device is powered up. 

Write procedure example: write value 06h in register at address 84h (PEDO_DEB_STEPS_CONF) in Page 1 

1. Write bit EMB_FUNC_REG_ACCESS = 1 in FUNC_CFG_ACCESS (01h) // Enable access to embedded functions 

2. Write bit PAGE_WRITE = 1 in PAGE_RW (17h) register // Select write operation mode 

3. Write 0001 in PAGE_SEL[3:0] field of register PAGE_SEL (02h) // Select page 1 

4. Write 84h in PAGE_ADDR register (08h) 

// Set address 

5. Write 06h in PAGE_DATA register (09h) 

// Set value to be written 

6. Write bit PAGE_WRITE = 0 in PAGE_RW (17h) register 

// Write operation disabled 

7. Write bit EMB_FUNC_REG_ACCESS = 0 in FUNC_CFG_ACCESS (01h) // Disable access to embedded functions registers 

## Read procedure example: read value of register at address 84h (PEDO_DEB_STEPS_CONF) in Page 1

1. Write bit EMB_FUNC_REG_ACCESS = 1 in FUNC_CFG_ACCESS (01h) // Enable access to embedded functions registers 

2. Write bit PAGE_READ = 1 in PAGE_RW (17h) register // Select read operation mode 

3. Write 0001 in PAGE_SEL[3:0] field of register PAGE_SEL (02h) // Select page 1 

4. Write 84h in PAGE_ADDR register (08h) 

// Set address 

5. Read value of PAGE_DATA register (09h) // Get register value 

6. Write bit PAGE_READ = 0 in PAGE_RW (17h) register // Read operation disabled 

7. Write bit EMB_FUNC_REG_ACCESS = 0 in FUNC_CFG_ACCESS (01h) // Disable access to embedded functions registers 

## Note:

Steps 1 and 2 of both procedures are intended to be performed at the beginning of the procedure. Steps 6 and 7 of both procedures are intended to be performed at the end of the procedure. If the procedure involves multiple operations, only steps 3, 4 and 5 must be repeated for each operation. If, in particular, the multiple operations involve consecutive registers, only step 5 can be performed. 

## Embedded advanced features register description

## 15.1 Page 0 - embedded advanced features registers

## 15.1.1 SFLP_GAME_GBIASX_L (6Eh) and SFLP_GAME_GBIASX_H (6Fh)

SFLP game algorithm X-axis gyroscope bias register (R/W) 

The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF (S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits) 


Table 350. SFLP_GAME_GBIASX_L register


<table><tr><td>GAME_GBIASX_7</td><td>GAME_GBIASX_6</td><td>GAME_GBIASX_5</td><td>GAME_GBIASX_4</td><td>GAME_GBIASX_3</td><td>GAME_GBIASX_2</td><td>GAME_GBIASX_1</td><td>GAME_GBIASX_0</td></tr></table>

## Table 351. SFLP_GAME_GBIASX_L register description

<table><tr><td>GAME_GBIASX_[7:0]</td><td>SFLP game algorithm X-axis gbias: temporary register for gbias setting procedure (LSbyte).Default value: 00000000</td></tr></table>


Table 352. SFLP_GAME_GBIASX_H register


<table><tr><td>GAME_GBIASX_15</td><td>GAME_GBIASX_14</td><td>GAME_GBIASX_13</td><td>GAME_GBIASX_12</td><td>GAME_GBIASX_11</td><td>GAME_GBIASX_10</td><td>GAME_GBIASX_9</td><td>GAME_GBIASX_8</td></tr></table>


Table 353. SFLP_GAME_GBIASX_H register description


<table><tr><td>GAME_GBIASX_[15:8]</td><td>SFLP game algorithm X-axis gbias: temporary register for gbias setting procedure (MSbyte).Default value: 00000000</td></tr></table>

## 15.1.2 SFLP_GAME_GBIASY_L (70h) and SFLP_GAME_GBIASY_H (71h)

SFLP game algorithm Y-axis gyroscope bias register (R/W) 

The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF (S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). 


Table 354. SFLP_GAME_GBIASY_L register


<table><tr><td>GAME_GBIASY_7</td><td>GAME_GBIASY_6</td><td>GAME_GBIASY_5</td><td>GAME_GBIASY_4</td><td>GAME_GBIASY_3</td><td>GAME_GBIASY_2</td><td>GAME_GBIASY_1</td><td>GAME_GBIASY_0</td></tr></table>

## Table 355. SFLP_GAME_GBIASY_L register description

<table><tr><td>GAME_GBIASY_[7:0]</td><td>SFLP game algorithm Y-axis gbias: temporary register for gbias setting procedure (LSbyte).Default value: 00000000</td></tr></table>


Table 356. SFLP_GAME_GBIASY_H register


<table><tr><td>GAME_GBIASY_15</td><td>GAME_GBIASY_14</td><td>GAME_GBIASY_13</td><td>GAME_GBIASY_12</td><td>GAME_GBIASY_11</td><td>GAME_GBIASY_10</td><td>GAME_GBIASY_9</td><td>GAME_GBIASY_8</td></tr></table>

## Table 357. SFLP_GAME_GBIASY_H register description

<table><tr><td>GAME_GBIASY_[15:8]</td><td>SFLP game algorithm Y-axis gbias: temporary register for gbias setting procedure (MSbyte).Default value: 00000000</td></tr></table>

## 15.1.3

## SFLP_GAME_GBIASZ_L (72h) and SFLP_GAME_GBIASZ_H (73h)

SFLP game algorithm Z-axis gyroscope bias register (R/W) 

The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF (S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). 


Table 358. SFLP_GAME_GBIASZ_L register


<table><tr><td>GAME_GBIASZ_7</td><td>GAME_GBIASZ_6</td><td>GAME_GBIASZ_5</td><td>GAME_GBIASZ_4</td><td>GAME_GBIASZ_3</td><td>GAME_GBIASZ_2</td><td>GAME_GBIASZ_1</td><td>GAME_GBIASZ_0</td></tr></table>


Table 359. SFLP_GAME_GBIASZ_L register description


<table><tr><td>GAME_GBIASZ_[7:0]</td><td>SFLP game algorithm Z-axis gbias: temporary register for gbias setting procedure (LSbyte).Default value: 00000000</td></tr></table>


Table 360. SFLP_GAME_GBIASZ_H register


<table><tr><td>GAME_GBIASZ_15</td><td>GAME_GBIASZ_14</td><td>GAME_GBIASZ_13</td><td>GAME_GBIASZ_12</td><td>GAME_GBIASZ_11</td><td>GAME_GBIASZ_10</td><td>GAME_GBIASZ_9</td><td>GAME_GBIASZ_8</td></tr></table>


Table 361. SFLP_GAME_GBIASZ_H register description


<table><tr><td>GAME_GBIASZ_[15:8]</td><td>SFLP game algorithm Z-axis gbias: temporary register for gbias setting procedure (MSbyte).Default value: 00000000</td></tr></table>

## 15.1.4 FSM_EXT_SENSITIVITY_L (BAh) and FSM_EXT_SENSITIVITY_H (BBh)

External sensor sensitivity value register for the finite state machine (R/W) 

This register corresponds to the conversion value of the external sensor. The register value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF (S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). 

Default value of FSM_EXT_S_[15:0] bits is 0x1624 (when using an external magnetometer this value corresponds to 0.0015 gauss/LSB). 


Table 362. FSM_EXT_SENSITIVITY_L register


<table><tr><td>FSM_EXT_S_7</td><td>FSM_EXT_S_6</td><td>FSM_EXT_S_5</td><td>FSM_EXT_S_4</td><td>FSM_EXT_S_3</td><td>FSM_EXT_S_2</td><td>FSM_EXT_S_1</td><td>FSM_EXT_S_0</td></tr></table>


Table 363. FSM_EXT_SENSITIVITY_L register description


<table><tr><td>FSM_EXT_S_[7:0]</td><td>External sensor sensitivity (LSbyte). Default value: 00100100</td></tr></table>


Table 364. FSM_EXT_SENSITIVITY_H register


<table><tr><td>FSM_EXT_S_15</td><td>FSM_EXT_S_14</td><td>FSM_EXT_S_13</td><td>FSM_EXT_S_12</td><td>FSM_EXT_S_11</td><td>FSM_EXT_S_10</td><td>FSM_EXT_S_9</td><td>FSM_EXT_S_8</td></tr></table>


Table 365. FSM_EXT_SENSITIVITY_H register description


<table><tr><td>FSM_EXT_S_[15:8]</td><td>External sensor (MSbyte). Default value: 00010110</td></tr></table>

## FSM_EXT_OFFX_L (C0h) and FSM_EXT_OFFX_H (C1h)

External sensor X-axis offset 

The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF 

(S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). 


Table 366. FSM_EXT_OFFX_L register


<table><tr><td>FSM_EXT_OFFX_7</td><td>FSM_EXT_OFFX_6</td><td>FSM_EXT_OFFX_5</td><td>FSM_EXT_OFFX_4</td><td>FSM_EXT_OFFX_3</td><td>FSM_EXT_OFFX_2</td><td>FSM_EXT_OFFX_1</td><td>FSM_EXT_OFFX_0</td></tr></table>


Table 367. FSM_EXT_OFFX_L register description


<table><tr><td>FSM_EXT_OFFX_[7:0]</td><td>External sensor X-axis offset (LSbyte). Default value: 00000000</td></tr></table>


Table 368. FSM_EXT_OFFX_H register


<table><tr><td>FSM_EXT_OFFX_15</td><td>FSM_EXT_OFFX_14</td><td>FSM_EXT_OFFX_13</td><td>FSM_EXT_OFFX_12</td><td>FSM_EXT_OFFX_11</td><td>FSM_EXT_OFFX_10</td><td>FSM_EXT_OFFX_9</td><td>FSM_EXT_OFFX_8</td></tr></table>


Table 369. FSM_EXT_OFFX_H register description


<table><tr><td>FSM_EXT_OFFX_[15:8]</td><td>External sensor X-axis offset (MSbyte). Default value: 00000000</td></tr></table>

## 15.1.6 FSM_EXT_OFFY_L (C2h) and FSM_EXT_OFFY_H (C3h)

External sensor Y-axis offset 

The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF 

(S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). 


Table 370. FSM_EXT_OFFY_L register


<table><tr><td>FSM_EXT_OFFY_7</td><td>FSM_EXT_OFFY_6</td><td>FSM_EXT_OFFY_5</td><td>FSM_EXT_OFFY_4</td><td>FSM_EXT_OFFY_3</td><td>FSM_EXT_OFFY_2</td><td>FSM_EXT_OFFY_1</td><td>FSM_EXT_OFFY_0</td></tr></table>


Table 371. FSM_EXT_OFFY_L register description


<table><tr><td>FSM_EXT_OFFY_[7:0]</td><td>External sensor Y-axis offset (LSbyte). Default value: 00000000</td></tr></table>


Table 372. FSM_EXT_OFFY_H register


<table><tr><td>FSM_EXT_OFFY_15</td><td>FSM_EXT_OFFY_14</td><td>FSM_EXT_OFFY_13</td><td>FSM_EXT_OFFY_12</td><td>FSM_EXT_OFFY_11</td><td>FSM_EXT_OFFY_10</td><td>FSM_EXT_OFFY_9</td><td>FSM_EXT_OFFY_8</td></tr></table>


Table 373. FSM_EXT_OFFY_H register description


<table><tr><td>FSM_EXT_OFFY_[15:8]</td><td>External sensor Y-axis offset (MSbyte). Default value: 00000000</td></tr></table>

## FSM_EXT_OFFZ_L (C4h) and FSM_EXT_OFFZ_H (C5h)

External sensor Z-axis offset register (R/W) 

The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF 

(S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). 


Table 374. FSM_EXT_OFFZ_L register


<table><tr><td>FSM_EXT_OFFZ_7</td><td>FSM_EXT_OFFZ_6</td><td>FSM_EXT_OFFZ_5</td><td>FSM_EXT_OFFZ_4</td><td>FSM_EXT_OFFZ_3</td><td>FSM_EXT_OFFZ_2</td><td>FSM_EXT_OFFZ_1</td><td>FSM_EXT_OFFZ_0</td></tr></table>


Table 375. FSM_EXT_OFFZ_L register description


<table><tr><td>FSM_EXT_OFFZ_[7:0]</td><td>External sensor Z-axis offset (LSbyte). Default value: 00000000</td></tr></table>


Table 376. FSM_EXT_OFFZ_H register


<table><tr><td>FSM_EXT_OFFZ_15</td><td>FSM_EXT_OFFZ_14</td><td>FSM_EXT_OFFZ_13</td><td>FSM_EXT_OFFZ_12</td><td>FSM_EXT_OFFZ_11</td><td>FSM_EXT_OFFZ_10</td><td>FSM_EXT_OFFZ_9</td><td>FSM_EXT_OFFZ_8</td></tr></table>


Table 377. FSM_EXT_OFFZ_H register description


<table><tr><td>FSM_EXT_OFFZ_[15:8]</td><td>External sensor Z-axis offset (MSbyte). Default value: 00000000</td></tr></table>

## FSM_EXT_MATRIX_XX_L (C6h) and FSM_EXT_MATRIX_XX_H (C7h)

External sensor transformation matrix register (R/W) 

The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF 

(S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). 


Table 378. FSM_EXT_MATRIX_XX_L register


<table><tr><td>FSM_EXT_MAT_XX_7</td><td>FSM_EXT_MAT_XX_6</td><td>FSM_EXT_MAT_XX_5</td><td>FSM_EXT_MAT_XX_4</td><td>FSM_EXT_MAT_XX_3</td><td>FSM_EXT_MAT_XX_2</td><td>FSM_EXT_MAT_XX_1</td><td>FSM_EXT_XX_0</td></tr></table>


Table 379. FSM_EXT_MATRIX_XX_L register description


<table><tr><td>FSM_EXT_MAT_XX_[7:0]</td><td>Transformation matrix row1 col1 coefficient (LSbyte). Default value: 00000000</td></tr></table>


Table 380. FSM_EXT_MATRIX_XX_H register


<table><tr><td>FSM_EXT_MAT_XX_15</td><td>FSM_EXT_MAT_XX_14</td><td>FSM_EXT_MAT_XX_13</td><td>FSM_EXT_MAT_XX_12</td><td>FSM_EXT_MAT_XX_11</td><td>FSM_EXT_MAT_XX_10</td><td>FSM_EXT_XX_9</td><td>FSM_EXT_XX_8</td></tr></table>


Table 381. FSM_EXT_MATRIX_XX_H register description


<table><tr><td>FSM_EXT_MAT_[15:8]</td><td>Transformation matrix row1 col1 coefficient (MSbyte). Default value: 00111100</td></tr></table>

## FSM_EXT_MATRIX_XY_L (C8h) and FSM_EXT_MATRIX_XY_H (C9h)

External sensor transformation matrix register (R/W) 

The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF 

(S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). 


Table 382. FSM_EXT_MATRIX_XY_L register


<table><tr><td>FSM_EXT_MAT_XY_7</td><td>FSM_EXT_MAT_XY_6</td><td>FSM_EXT_MAT_XY_5</td><td>FSM_EXT_MAT_XY_4</td><td>FSM_EXT_MAT_XY_3</td><td>FSM_EXT_MAT_XY_2</td><td>FSM_EXT_MAT_XY_1</td><td>FSM_EXT_MAT_XY_0</td></tr></table>


Table 383. FSM_EXT_MATRIX_XY_L register description


<table><tr><td>FSM_EXT_MAT_XY_[7:0]</td><td>Transformation matrix row1 col2 (and row2 col1) coefficient (LSbyte). Default value: 00000000</td></tr></table>


Table 384. FSM_EXT_MATRIX_XY_H register


<table><tr><td>FSM_EXT_XY_15</td><td>FSM_EXT_XY_14</td><td>FSM_EXT_XY_13</td><td>FSM_EXT_XY_12</td><td>FSM_EXT_XY_11</td><td>FSM_EXT_XY_10</td><td>FSM_EXT_XY_9</td><td>FSM_EXT_XY_8</td></tr></table>


Table 385. FSM_EXT_MATRIX_XY_H register description


<table><tr><td>FSM_EXT_MAT_XY_[15:8]</td><td>Transformation matrix row1 col2 (and row2 col1) coefficient (MSbyte). Default value: 00000000</td></tr></table>

## 15.1.10 FSM_EXT_MATRIX_XZ_L (CAh) and FSM_EXT_MATRIX_XZ_H (CBh)

External sensor transformation matrix register (R/W) 

The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF 

(S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). 


Table 386. FSM_EXT_MATRIX_XZ_L register


<table><tr><td>FSM_EXT_MAT_XZ_7</td><td>FSM_EXT_MAT_XZ_6</td><td>FSM_EXT_MAT_XZ_5</td><td>FSM_EXT_MAT_XZ_4</td><td>FSM_EXT_MAT_XZ_3</td><td>FSM_EXT_MAT_XZ_2</td><td>FSM_EXT_MAT_XZ_1</td><td>FSM_EXT_MAT_XZ_0</td></tr></table>


Table 387. FSM_EXT_MATRIX_XZ_L register description


<table><tr><td>FSM_EXT_MAT_XZ_[7:0]</td><td>Transformation matrix row1 col3 (and row3 col1) coefficient (LSbyte). Default value: 00000000</td></tr></table>


Table 388. FSM_EXT_MATRIX_XZ_H register


<table><tr><td>FSM_EXT_MAT_XZ_15</td><td>FSM_EXT_MAT_XZ_14</td><td>FSM_EXT_MAT_XZ_13</td><td>FSM_EXT_MAT_XZ_12</td><td>FSM_EXT_MAT_XZ_11</td><td>FSM_EXT_MAT_XZ_10</td><td>FSM_EXT_MAT_XZ_9</td><td>FSM_EXT_MAT_XZ_8</td></tr></table>

## Table 389. FSM_EXT_MATRIX_XZ_H register description

<table><tr><td>FSM_EXT_MAT_XZ_[15:8]</td><td>Transformation matrix row1 col3 (and row3 col1) coefficient (MSbyte). Default value: 00000000</td></tr></table>

## FSM_EXT_MATRIX $\yen 1$ (CCh) and FSM_EXT_MATRIX_YY_H (CDh)

External sensor transformation matrix register (R/W) 

The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF 

(S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). 


Table 390. FSM_EXT_MATRIX_YY_L register


<table><tr><td>FSM_EXT_MAT_YY_7</td><td>FSM_EXT_MAT_YY_6</td><td>FSM_EXT_MAT_YY_5</td><td>FSM_EXT_MAT_YY_4</td><td>FSM_EXT_MAT_YY_3</td><td>FSM_EXT_MAT_YY_2</td><td>FSM_EXT_MAT_YY_1</td><td>FSM_EXT_MAT_YY_0</td></tr></table>


Table 391. FSM_EXT_MATRIX_YY_L register description


<table><tr><td>FSM_EXT_MAT_YY_[7:0]</td><td>Transformation matrix row2 col2 coefficient (LSbyte). Default value: 00000000</td></tr></table>


Table 392. FSM_EXT_MATRIX_YY_H register


<table><tr><td>FSM_EXT_MAT_YY_15</td><td>FSM_EXT_MAT_YY_14</td><td>FSM_EXT_MAT_YY_13</td><td>FSM_EXT_MAT_YY_12</td><td>FSM_EXT_MAT_YY_11</td><td>FSM_EXT_MAT_YY_10</td><td>FSM_EXT_MAT_YY_9</td><td>FSM_EXT_MAT_YY_8</td></tr></table>


Table 393. FSM_EXT_MATRIX_YY_H register description


<table><tr><td>FSM_EXT_MAT_YY_[15:8]</td><td>Transformation matrix row2 col2 coefficient (MSbyte). Default value: 00111100</td></tr></table>

## 15.1.12 FSM_EXT_MATRIX $\yen 1$ (CEh) and FSM_EXT_MATRIX_YZ_H (CFh)

External sensor transformation matrix register (R/W) 

The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF 

(S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). 


Table 394. FSM_EXT_MATRIX_YZ_L register


<table><tr><td>FSM_EXT_MAT_YZ_7</td><td>FSM_EXT_MAT_YZ_6</td><td>FSM_EXT_MAT_YZ_5</td><td>FSM_EXT_MAT_YZ_4</td><td>FSM_EXT_MAT_YZ_3</td><td>FSM_EXT_MAT_YZ_2</td><td>FSM_EXT_MAT_YZ_1</td><td>FSM_EXT_MAT_YZ_0</td></tr></table>


Table 395. FSM_EXT_MATRIX_YZ_L register description


<table><tr><td>FSM_EXT_MAT_YZ[7:0]</td><td>Transformation matrix row2 col3 (and row3 col2) coefficient (LSbyte).Default value: 00000000</td></tr></table>


Table 396. FSM_EXT_MATRIX_YZ_H register


<table><tr><td>FSM_EXT_MAT_YZ_15</td><td>FSM_EXT_MAT_YZ_14</td><td>FSM_EXT_MAT_YZ_13</td><td>FSM_EXT_MAT_YZ_12</td><td>FSM_EXT_MAT_YZ_11</td><td>FSM_EXT_MAT_YZ_10</td><td>FSM_EXT_MAT_YZ_9</td><td>FSM_EXT_MAT_YZ_8</td></tr></table>


Table 397. FSM_EXT_MATRIX_YZ_H register description


<table><tr><td>FSM_EXT_MAT_YZ_[15:8]</td><td>Transformation matrix row2 col3 (and row3 col2) coefficient (MSbyte).Default value: 00000000</td></tr></table>

## FSM_EXT_MATRIX_ZZ_L (D0h) and FSM_EXT_MATRIX_ZZ_H (D1h)

External sensor transformation matrix register (R/W) 

The value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF 

(S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). 


Table 398. FSM_EXT_MATRIX_ZZ_L register


<table><tr><td>FSM_EXT_MAT_ZZ_7</td><td>FSM_EXT_MAT_ZZ_6</td><td>FSM_EXT_MAT_ZZ_5</td><td>FSM_EXT_MAT_ZZ_4</td><td>FSM_EXT_MAT_ZZ_3</td><td>FSM_EXT_MAT_ZZ_2</td><td>FSM_EXT_MAT_ZZ_1</td><td>FSM_EXT_MAT_ZZ_0</td></tr></table>

## Table 399. FSM_EXT_MATRIX_ZZ_L register description

<table><tr><td>FSM_EXT_MAT_ZZ_[7:0]</td><td>Transformation matrix row3 col3 coefficient (LSbyte). Default value: 00000000</td></tr></table>


Table 400. FSM_EXT_MATRIX_ZZ_H register


<table><tr><td>FSM_EXT_MAT_ZZ_15</td><td>FSM_EXT_MAT_ZZ_14</td><td>FSM_EXT_MAT_ZZ_13</td><td>FSM_EXT_MAT_ZZ_12</td><td>FSM_EXT_MAT_ZZ_11</td><td>FSM_EXT_MAT_ZZ_10</td><td>FSM_EXT_MAT_ZZ_9</td><td>FSM_EXT_MAT_ZZ_8</td></tr></table>


Table 401. FSM_EXT_MATRIX_ZZ_H register description


<table><tr><td>FSM_EXT_MAT_ZZ_[15:8]</td><td>Transformation matrix row3 col3 coefficient (MSbyte). Default value: 00111100</td></tr></table>

## 15.1.14 EXT_CFG_A (D4h)

External sensor coordinates (Z and Y axes) rotation register (r/w). 


Table 402. EXT_CFG_A register


<table><tr><td><eq>0^{(1)}</eq></td><td>EXT_Y_AXIS2</td><td>EXT_Y_AXIS1</td><td>EXT_Y_AXIS0</td><td><eq>0^{(1)}</eq></td><td>EXT_Z_AXIS2</td><td>EXT_Z_AXIS1</td><td>EXT_Z_AXIS0</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 403. EXT_CFG_A description


<table><tr><td>EXT_Y_AXIS[2:0]</td><td>External sensor Y-axis coordinates rotation (to be aligned to accelerometer/gyroscope axes orientation)(000: Y = Y; (default)001: Y = -Y;010: Y = X;011: Y = -X;100: Y = -Z;101: Y = Z;Others: Y = Y)</td></tr><tr><td>EXT_Z_AXIS[2:0]</td><td>External sensor Z-axis coordinates rotation (to be aligned to accelerometer/gyroscope axes orientation)(000: Z = Y;001: Z = -Y;010: Z = X;011: Z = -X;100: Z = -Z;101: Z = Z; (default)Others: Z = Y)</td></tr></table>

## 15.1.15 EXT_CFG_B (D5h)

External sensor coordinates (X-axis) rotation register (r/w). 


Table 404. EXT_CFG_B register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>EXT_X_AXIS2</td><td>EXT_X_AXIS1</td><td>EXT_X_AXIS0</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 405. EXT_CFG_B description


<table><tr><td>EXT_X_AXIS[2:0]</td><td>External sensor X-axis coordinates rotation (to be aligned to accelerometer/gyroscope axes orientation)(000: X = Y;001: X = -Y;010: X = X; (default)011: X = -X;100: X = -Z;101: X = Z;Others: X = Y)</td></tr></table>

## 15.2

## Page 1 - embedded advanced features registers

## 15.2.1

## FSM_LC_TIMEOUT_L (7Ah) and FSM_LC_TIMEOUT_H (7Bh)

FSM long counter timeout register (R/W) 

The long counter timeout value is an unsigned integer value (16-bit format). When the long counter value reached this value, the FSM generates an interrupt. 


Table 406. FSM_LC_TIMEOUT_L register


<table><tr><td>FSM_LC_TIMEOUT7</td><td>FSM_LC_TIMEOUT6</td><td>FSM_LC_TIMEOUT5</td><td>FSM_LC_TIMEOUT4</td><td>FSM_LC_TIMEOUT3</td><td>FSM_LC_TIMEOUT2</td><td>FSM_LC_TIMEOUT1</td><td>FSM_LC_TIMEOUT0</td></tr></table>

## Table 407. FSM_LC_TIMEOUT_L register description

<table><tr><td>FSM_LC_TIMEOUT[7:0]</td><td>FSM long counter timeout value (LSbyte). Default value: 00000000</td></tr></table>


Table 408. FSM_LC_TIMEOUT_H register


<table><tr><td>FSM_LC_TIMEOUT15</td><td>FSM_LC_TIMEOUT14</td><td>FSM_LC_TIMEOUT13</td><td>FSM_LC_TIMEOUT12</td><td>FSM_LC_TIMEOUT11</td><td>FSM_LC_TIMEOUT10</td><td>FSM_LC_TIMEOUT9</td><td>FSM_LC_TIMEOUT8</td></tr></table>


Table 409. FSM_LC_TIMEOUT_H register description


<table><tr><td>FSM_LC_TIMEOUT[15:8]</td><td>FSM long counter timeout value (MSbyte). Default value: 00000000</td></tr></table>

## 15.2.2

## FSM_PROGRAMS (7Ch)

FSM number of programs register (R/W) 


Table 410. FSM_PROGRAMS register


<table><tr><td>FSM_N_PROG7</td><td>FSM_N_PROG6</td><td>FSM_N_PROG5</td><td>FSM_N_PROG4</td><td>FSM_N_PROG3</td><td>FSM_N_PROG2</td><td>FSM_N_PROG1</td><td>FSM_N_PROG0</td></tr></table>


Table 411. FSM_PROGRAMS register description


<table><tr><td>FSM_N_PROG[7:0]</td><td>Number of FSM programs; must be less than or equal to 8.Default value: 00000000</td></tr></table>

## 15.2.3

## FSM_START_ADD_L (7Eh) and FSM_START_ADD_H (7Fh)

FSM start address register (R/W). First available address is 0x35C. 


Table 412. FSM_START_ADD_L register


<table><tr><td>FSM_START7</td><td>FSM_START6</td><td>FSM_START5</td><td>FSM_START4</td><td>FSM_START3</td><td>FSM_START2</td><td>FSM_START1</td><td>FSM_START0</td></tr></table>


Table 413. FSM_START_ADD_L register description


<table><tr><td>FSM_START[7:0]</td><td>FSM start address value (LSbyte). Default value: 00000000</td></tr></table>


Table 414. FSM_START_ADD_H register


<table><tr><td>FSM_START15</td><td>FSM_START14</td><td>FSM_START13</td><td>FSM_START12</td><td>FSM_START11</td><td>FSM_START10</td><td>FSM_START9</td><td>FSM_START8</td></tr></table>

## Table 415. FSM_START_ADD_H register description

<table><tr><td>FSM_START[15:8]</td><td>FSM start address value (MSbyte). Default value: 00000000</td></tr></table>

## 15.2.4

## PEDO_CMD_REG (83h)

Pedometer configuration register (R/W) 


Table 416. PEDO_CMD_REG register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>CARRY_COUNT_EN</td><td>FP_REJECTION_EN</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 417. PEDO_CMD_REG register description


<table><tr><td>CARRY_COUNT_EN</td><td>Set when user wants to generate interrupt only on count overflow event.</td></tr><tr><td>FP_REJECTION_EN(1)</td><td>Enables the false-positive rejection feature</td></tr></table>

1. This bit is activated if the MLC_EN bit of EMB_FUNC_EN_B (05h) or the MLC_BEFORE_FSM_EN bit in the EMB_FUNC_EN_A (04h) register is set to 1. 


Table 419. PEDO_DEB_STEPS_CONF register description


## 15.2.5

## PEDO_DEB_STEPS_CONF (84h)

Pedometer debounce configuration register (R/W) 


Table 418. PEDO_DEB_STEPS_CONF register


<table><tr><td>DEB_STEP7</td><td>DEB_STEP6</td><td>DEB_STEP5</td><td>DEB_STEP4</td><td>DEB_STEP3</td><td>DEB_STEP2</td><td>DEB_STEP1</td><td>DEB_STEP0</td></tr></table>

<table><tr><td>DEB_STEP[7:0]</td><td>Debounce threshold. Minimum number of steps to increment the step counter (debounce).Default value: 00001010</td></tr></table>

## 15.2.6

## PEDO_SC_DELTAT_L (D0h) and PEDO_SC_DELTAT_H (D1h)

Time period register for step detection on delta time (R/W) 


Table 420. PEDO_SC_DELTAT_L register


<table><tr><td>PD_SC_7</td><td>PD_SC_6</td><td>PD_SC_5</td><td>PD_SC_4</td><td>PD_SC_3</td><td>PD_SC_2</td><td>PD_SC_1</td><td>PD_SC_0</td></tr></table>


Table 421. PEDO_SC_DELTAT_H register


<table><tr><td>PD_SC_15</td><td>PD_SC_14</td><td>PD_SC_13</td><td>PD_SC_12</td><td>PD_SC_11</td><td>PD_SC_10</td><td>PD_SC_9</td><td>PD_SC_8</td></tr></table>

<table><tr><td>PD_SC_[15:0]</td><td>Time period value (1LSB = 6.4 ms)</td></tr></table>

## MLC_EXT_SENSITIVITY_L (E8h) and MLC_EXT_SENSITIVITY_H (E9h)

External sensor sensitivity value register for the machine learning core (R/W) 

This register corresponds to the conversion value of the external sensor. The register value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF (S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). Default value of MLC_EXT_S_[15:0] is 0x3C00 (when using an external magnetometer this value corresponds to 1 gauss/LSB). 


Table 423. MLC_EXT_SENSITIVITY_L register


<table><tr><td>MLC_EXT_S_7</td><td>MLC_EXT_S_6</td><td>MLC_EXT_S_5</td><td>MLC_EXT_S_4</td><td>MLC_EXT_S_3</td><td>MLC_EXT_S_2</td><td>MLC_EXT_S_1</td><td>MLC_EXT_S_0</td></tr></table>

## Table 424. MLC_ EXT_SENSITIVITY_L register description

<table><tr><td>MLC_EXT_S_[7:0]</td><td>External sensor sensitivity (LSbyte). Default value: 00000000</td></tr></table>

## Table 425. MLC_EXT_SENSITIVITY_H register

<table><tr><td>MLC_EXT_S_15</td><td>MLC_EXT_S_14</td><td>MLC_EXT_S_13</td><td>MLC_EXT_S_12</td><td>MLC_EXT_S_11</td><td>MLC_EXT_S_10</td><td>MLC_EXT_S_9</td><td>MLC_EXT_S_8</td></tr></table>

## Table 426. MLC_EXT_SENSITIVITY_H register description

<table><tr><td>MLC_EXT_S_[15:8]</td><td>External sensor sensitivity (MSbyte). Default value: 00111100</td></tr></table>

## 15.3

## Page 2 - embedded advanced features registers

## 15.3.1 EXT_FORMAT (00h)

AH / Qvar / external sensor data format (2-byte or 3-byte) for the finite state machine and machine learning core (R/W) 


Table 427. EXT_FORMAT register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>EXT_FORMAT_SEL</td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 428. EXT_FORMAT register description


<table><tr><td>EXT_FORMAT_SEL</td><td>Selects the format of AH / Qvar / external sensor data for FSM and MLC processing. Default value: 0(0: 2-byte format; 1: 3-byte format)</td></tr></table>

## 15.3.2 EXT_3BYTE_SENSITIVITY_L (02h) and EXT_3BYTE_SENSITIVITY_H (03h)

External sensor (3-byte output data) sensitivity value register for the finite state machine and machine learning core (R/W) 

This register corresponds to the conversion value of the external sensor having 3-byte output data. The register value is expressed as half-precision floating-point format: SEEEEEFFFFFFFFFF (S: 1 sign bit; E: 5 exponent bits; F: 10 fraction bits). 

The default value of EXT_3BYTE_S_[15:0] is 0x0C00 (when using an external pressure sensor this value corresponds to 2.441e-04 hPa/LSB). 


Table 429. EXT_3BYTE_SENSITIVITY_L register


<table><tr><td>EXT_3BYTE_S_7</td><td>EXT_3BYTE_S_6</td><td>EXT_3BYTE_S_5</td><td>EXT_3BYTE_S_4</td><td>EXT_3BYTE_S_3</td><td>EXT_3BYTE_S_2</td><td>EXT_3BYTE_S_1</td><td>EXT_3BYTE_S_0</td></tr></table>

## Table 430. EXT_3BYTE_SENSITIVITY_L register description

<table><tr><td>EXT_3BYTE_S_[7:0]</td><td>External sensor (3-byte output data) sensitivity (LSbyte). Default value: 00000000</td></tr></table>


Table 431. EXT_3BYTE_SENSITIVITY_H register


<table><tr><td>EXT_3BYTE_S_15</td><td>EXT_3BYTE_S_14</td><td>EXT_3BYTE_S_13</td><td>EXT_3BYTE_S_12</td><td>EXT_3BYTE_S_11</td><td>EXT_3BYTE_S_10</td><td>EXT_3BYTE_S_9</td><td>EXT_3BYTE_S_8</td></tr></table>


Table 432. EXT_3BYTE_SENSITIVITY_H register description


<table><tr><td>EXT_3BYTE_S_[15:8]</td><td>External sensor (3-byte output data) sensitivity (MSbyte). Default value: 00001100</td></tr></table>

## 15.3.3

## EXT_3BYTE_OFFSET_XL (06h), EXT_3BYTE_OFFSET_L (07h) and EXT_3BYTE_OFFSET_H (08h)

External sensor (3-byte output data) offset value register for the finite state machine and machine learning core (R/W) 

This register corresponds to the offset value applied to external sensor output data (3-byte) before being processed in FSM and MLC. The value is expressed as a 24-bit word in two’s complement. 

The default value of EXT_3BYTE_OFF_[23:0] is 0x3F5400, which corresponds to 4150272 LSB. This offset is subtracted from the external output data (in LSB) before the sensitivity (configured in the EXT_3BYTE_SENSITIVITY_L (02h) and EXT_3BYTE_SENSITIVITY_H (03h) registers) is internally applied. 


Table 433. EXT_3BYTE_OFFSET_XL register


<table><tr><td>EXT_3BYTE_OFF_7</td><td>EXT_3BYTE_OFF_6</td><td>EXT_3BYTE_OFF_5</td><td>EXT_3BYTE_OFF_4</td><td>EXT_3BYTE_OFF_3</td><td>EXT_3BYTE_OFF_2</td><td>EXT_3BYTE_OFF_1</td><td>EXT_3BYTE_OFF_0</td></tr></table>

## Table 434. EXT_3BYTE_OFFSET_XL register description

<table><tr><td>EXT_3BYTE_OFF_[7:0]</td><td>External sensor (3-byte output data) offset (low byte). Default value: 00000000</td></tr></table>


Table 435. EXT_3BYTE_OFFSET_L register


<table><tr><td>EXT_3BYTE_OFF_15</td><td>EXT_3BYTE_OFF_14</td><td>EXT_3BYTE_OFF_13</td><td>EXT_3BYTE_OFF_12</td><td>EXT_3BYTE_OFF_11</td><td>EXT_3BYTE_OFF_10</td><td>EXT_3BYTE_OFF_9</td><td>EXT_3BYTE_OFF_8</td></tr></table>


Table 436. EXT_3BYTE_OFFSET_L register description


<table><tr><td>EXT_3BYTE_OFF_[15:8]</td><td>External sensor (3-byte output data) offset (mid byte). Default value: 01010100</td></tr></table>


Table 437. EXT_3BYTE_OFFSET_H register


<table><tr><td>EXT_3BYTE_OFF_23</td><td>EXT_3BYTE_OFF_22</td><td>EXT_3BYTE_OFF_21</td><td>EXT_3BYTE_OFF_20</td><td>EXT_3BYTE_OFF_19</td><td>EXT_3BYTE_OFF_18</td><td>EXT_3BYTE_OFF_17</td><td>EXT_3BYTE_OFF_16</td></tr></table>


Table 438. EXT_3BYTE_OFFSET_H register description


<table><tr><td>EXT_3BYTE_OFF_[23:16]</td><td>External sensor (3-byte output data) offset (high byte). Default value: 00111111</td></tr></table>

## Sensor hub register mapping

The table given below provides a list of the registers for the sensor hub functions available in the device and the corresponding addresses. The sensor hub registers are accessible when bit SHUB_REG_ACCESS is set to 1 in FUNC_CFG_ACCESS (01h). 


Table 439. Register address map - sensor hub registers


<table><tr><td rowspan="2">Name</td><td rowspan="2">Type</td><td colspan="2">Register address</td><td rowspan="2">Default</td><td rowspan="2">Comment</td></tr><tr><td>Hex</td><td>Binary</td></tr><tr><td>SENSOR_HUB_1</td><td>R</td><td>02</td><td>00000010</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_2</td><td>R</td><td>03</td><td>00000011</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_3</td><td>R</td><td>04</td><td>00000100</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_4</td><td>R</td><td>05</td><td>00000101</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_5</td><td>R</td><td>06</td><td>00000110</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_6</td><td>R</td><td>07</td><td>00000111</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_7</td><td>R</td><td>08</td><td>00001000</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_8</td><td>R</td><td>09</td><td>00001001</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_9</td><td>R</td><td>0A</td><td>00001010</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_10</td><td>R</td><td>0B</td><td>00001011</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_11</td><td>R</td><td>0C</td><td>00001100</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_12</td><td>R</td><td>0D</td><td>00001101</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_13</td><td>R</td><td>0E</td><td>00001110</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_14</td><td>R</td><td>0F</td><td>00001111</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_15</td><td>R</td><td>10</td><td>00010000</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_16</td><td>R</td><td>11</td><td>00010001</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_17</td><td>R</td><td>12</td><td>00010010</td><td>output</td><td></td></tr><tr><td>SENSOR_HUB_18</td><td>R</td><td>13</td><td>00010011</td><td>output</td><td></td></tr><tr><td>MASTER_CONFIG</td><td>R/W</td><td>14</td><td>00010100</td><td>00000000</td><td></td></tr><tr><td>SLV0_ADD</td><td>R/W</td><td>15</td><td>00010101</td><td>00000000</td><td></td></tr><tr><td>SLV0_SUBADD</td><td>R/W</td><td>16</td><td>00010110</td><td>00000000</td><td></td></tr><tr><td>SLV0_CONFIG</td><td>R/W</td><td>17</td><td>00010111</td><td>10000000</td><td></td></tr><tr><td>SLV1_ADD</td><td>R/W</td><td>18</td><td>00011000</td><td>00000000</td><td></td></tr><tr><td>SLV1_SUBADD</td><td>R/W</td><td>19</td><td>00011001</td><td>00000000</td><td></td></tr><tr><td>SLV1_CONFIG</td><td>R/W</td><td>1A</td><td>00011010</td><td>00010000</td><td></td></tr><tr><td>SLV2_ADD</td><td>R/W</td><td>1B</td><td>00011011</td><td>00000000</td><td></td></tr><tr><td>SLV2_SUBADD</td><td>R/W</td><td>1C</td><td>00011100</td><td>00000000</td><td></td></tr><tr><td>SLV2_CONFIG</td><td>R/W</td><td>1D</td><td>00011101</td><td>00000000</td><td></td></tr><tr><td>SLV3_ADD</td><td>R/W</td><td>1E</td><td>00011110</td><td>00000000</td><td></td></tr><tr><td>SLV3_SUBADD</td><td>R/W</td><td>1F</td><td>00011111</td><td>00000000</td><td></td></tr><tr><td>SLV3_CONFIG</td><td>R/W</td><td>20</td><td>00100000</td><td>00000000</td><td></td></tr><tr><td>DATAWRITE_SLV0</td><td>R/W</td><td>21</td><td>00100001</td><td>00000000</td><td></td></tr><tr><td>STATUS_MASTER</td><td>R</td><td>22</td><td>00100010</td><td>output</td><td></td></tr></table>

Reserved registers must not be changed. Writing to those registers may cause permanent damage to the device. The content of the registers that are loaded at boot should not be changed. They contain the factory calibration values. Their content is automatically restored when the device is powered up. 

## Sensor hub register description

## 17.1 SENSOR_HUB_1 (02h)

Sensor hub output register (R) 

First byte associated to external sensors. The content of the register is consistent with the SLVx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 440. SENSOR_HUB_1 register


<table><tr><td>SensorHub1_7</td><td>SensorHub1_6</td><td>SensorHub1_5</td><td>SensorHub1_4</td><td>SensorHub1_3</td><td>SensorHub1_2</td><td>SensorHub1_1</td><td>SensorHub1_0</td></tr></table>


Table 441. SENSOR_HUB_1 register description


<table><tr><td>SensorHub1_[7:0]</td><td>First byte associated to external sensors</td></tr></table>

## SENSOR_HUB_2 (03h)

Sensor hub output register (R) 

Second byte associated to external sensors. The content of the register is consistent with the SLVx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 442. SENSOR_HUB_2 register


<table><tr><td>SensorHub2_7</td><td>SensorHub2_6</td><td>SensorHub2_5</td><td>SensorHub2_4</td><td>SensorHub2_3</td><td>SensorHub2_2</td><td>SensorHub2_1</td><td>SensorHub2_0</td></tr></table>


Table 443. SENSOR_HUB_2 register description


<table><tr><td>SensorHub2_[7:0]</td><td>Second byte associated to external sensors</td></tr></table>

## 17.3 SENSOR_HUB_3 (04h)

Sensor hub output register (R) 

Third byte associated to external sensors. The content of the register is consistent with the SLVx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 444. SENSOR_HUB_3 register


<table><tr><td>SensorHub3_7</td><td>SensorHub3_6</td><td>SensorHub3_5</td><td>SensorHub3_4</td><td>SensorHub3_3</td><td>SensorHub3_2</td><td>SensorHub3_1</td><td>SensorHub3_0</td></tr></table>


Table 445. SENSOR_HUB_3 register description


<table><tr><td>SensorHub3_[7:0]</td><td>Third byte associated to external sensors</td></tr></table>

## 17.4

## SENSOR_HUB_4 (05h)

Sensor hub output register (R) 

Fourth byte associated to external sensors. The content of the register is consistent with the SLVx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 446. SENSOR_HUB_4 register


<table><tr><td>SensorHub4_7</td><td>SensorHub4_6</td><td>SensorHub4_5</td><td>SensorHub4_4</td><td>SensorHub4_3</td><td>SensorHub4_2</td><td>SensorHub4_1</td><td>SensorHub4_0</td></tr></table>


Table 447. SENSOR_HUB_4 register description


<table><tr><td>SensorHub4_[7:0]</td><td>Fourth byte associated to external sensors</td></tr></table>

## SENSOR_HUB_5 (06h)

Sensor hub output register (R) 

Fifth byte associated to external sensors. The content of the register is consistent with the SLVx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 448. SENSOR_HUB_5 register


<table><tr><td>SensorHub5_7</td><td>SensorHub5_6</td><td>SensorHub5_5</td><td>SensorHub5_4</td><td>SensorHub5_3</td><td>SensorHub5_2</td><td>SensorHub5_1</td><td>SensorHub5_0</td></tr></table>


Table 449. SENSOR_HUB_5 register description


<table><tr><td>SensorHub5_[7:0]</td><td>Fifth byte associated to external sensors</td></tr></table>

## SENSOR_HUB_6 (07h)

Sensor hub output register (R) 

Sixth byte associated to external sensors. The content of the register is consistent with the SLVx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 450. SENSOR_HUB_6 register


<table><tr><td>SensorHub6_7</td><td>SensorHub6_6</td><td>SensorHub6_5</td><td>SensorHub6_4</td><td>SensorHub6_3</td><td>SensorHub6_2</td><td>SensorHub6_1</td><td>SensorHub6_0</td></tr></table>


Table 451. SENSOR_HUB_6 register description


<table><tr><td>SensorHub6_[7:0]</td><td>Sixth byte associated to external sensors</td></tr></table>

## SENSOR_HUB_7 (08h)

Sensor hub output register (R) 

Seventh byte associated to external sensors. The content of the register is consistent with the SLVx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 452. SENSOR_HUB_7 register


<table><tr><td>SensorHub7_7</td><td>SensorHub7_6</td><td>SensorHub7_5</td><td>SensorHub7_4</td><td>SensorHub7_3</td><td>SensorHub7_2</td><td>SensorHub7_1</td><td>SensorHub7_0</td></tr></table>


Table 453. SENSOR_HUB_7 register description


<table><tr><td>SensorHub7_[7:0]</td><td>Seventh byte associated to external sensors</td></tr></table>

## SENSOR_HUB_8 (09h)

Sensor hub output register (R) 

Eighth byte associated to external sensors. The content of the register is consistent with the SLVx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 454. SENSOR_HUB_8 register


<table><tr><td>SensorHub8_7</td><td>SensorHub8_6</td><td>SensorHub8_5</td><td>SensorHub8_4</td><td>SensorHub8_3</td><td>SensorHub8_2</td><td>SensorHub8_1</td><td>SensorHub8_0</td></tr></table>


Table 455. SENSOR_HUB_8 register description


<table><tr><td>SensorHub8_[7:0]</td><td>Eighth byte associated to external sensors</td></tr></table>

## SENSOR_HUB_9 (0Ah)

Sensor hub output register (R) 

Ninth byte associated to external sensors. The content of the register is consistent with the SLVx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 456. SENSOR_HUB_9 register


<table><tr><td>SensorHub9_7</td><td>SensorHub9_6</td><td>SensorHub9_5</td><td>SensorHub9_4</td><td>SensorHub9_3</td><td>SensorHub9_2</td><td>SensorHub9_1</td><td>SensorHub9_0</td></tr></table>


Table 457. SENSOR_HUB_9 register description


<table><tr><td>SensorHub9_[7:0]</td><td>Ninth byte associated to external sensors</td></tr></table>

## SENSOR_HUB_10 (0Bh)

Sensor hub output register (R) 

Tenth byte associated to external sensors. The content of the register is consistent with the $\mathsf { S L V } \mathsf { x } _ { \mathsf { \_ } }$ _CONFIG number of read operation configurations (for external sensors from ${ \sf x } = 0$ to x = 3). 


Table 458. SENSOR_HUB_10 register


<table><tr><td>SensorHub10_7</td><td>SensorHub10_6</td><td>SensorHub10_5</td><td>SensorHub10_4</td><td>SensorHub10_3</td><td>SensorHub10_2</td><td>SensorHub10_1</td><td>SensorHub10_0</td></tr></table>


Table 459. SENSOR_HUB_10 register description


<table><tr><td>SensorHub10_[7:0]</td><td>Tenth byte associated to external sensors</td></tr></table>

## 17.11 SENSOR_HUB_11 (0Ch)

Sensor hub output register (R) 

Eleventh byte associated to external sensors. The content of the register is consistent with the SLVx_CONFIG number of read operation configurations (for external sensors from $\mathsf { x } = 0 \mathrm { t } 0 \mathsf { x } = 3 )$ 


Table 460. SENSOR_HUB_11 register


<table><tr><td>SensorHub11_7</td><td>SensorHub11_6</td><td>SensorHub11_5</td><td>SensorHub11_4</td><td>SensorHub11_3</td><td>SensorHub11_2</td><td>SensorHub11_1</td><td>SensorHub11_0</td></tr></table>


Table 461. SENSOR_HUB_11 register description


<table><tr><td>SensorHub11_[7:0]</td><td>Eleventh byte associated to external sensors</td></tr></table>

## SENSOR_HUB_12 (0Dh)

Sensor hub output register (R) 

Twelfth byte associated to external sensors. The content of the register is consistent with the SLVx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 462. SENSOR_HUB_12 register


<table><tr><td>SensorHub12_7</td><td>SensorHub12_6</td><td>SensorHub12_5</td><td>SensorHub12_4</td><td>SensorHub12_3</td><td>SensorHub12_2</td><td>SensorHub12_1</td><td>SensorHub12_0</td></tr></table>


Table 463. SENSOR_HUB_12 register description


<table><tr><td>SensorHub12_[7:0]</td><td>Twelfth byte associated to external sensors</td></tr></table>

## 17.13

## SENSOR_HUB_13 (0Eh)

Sensor hub output register (R) 

Thirteenth byte associated to external sensors. The content of the register is consistent with the SLVx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 464. SENSOR_HUB_13 register


<table><tr><td>SensorHub13_7</td><td>SensorHub13_6</td><td>SensorHub13_5</td><td>SensorHub13_4</td><td>SensorHub13_3</td><td>SensorHub13_2</td><td>SensorHub13_1</td><td>SensorHub13_0</td></tr></table>


Table 465. SENSOR_HUB_13 register description


<table><tr><td>SensorHub13_[7:0]</td><td>Thirteenth byte associated to external sensors</td></tr></table>

## 17.14 SENSOR_HUB_14 (0Fh)

Sensor hub output register (R) 

Fourteenth byte associated to external sensors. The content of the register is consistent with the SLVx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 466. SENSOR_HUB_14 register


<table><tr><td>SensorHub14_7</td><td>SensorHub14_6</td><td>SensorHub14_5</td><td>SensorHub14_4</td><td>SensorHub14_3</td><td>SensorHub14_2</td><td>SensorHub14_1</td><td>SensorHub14_0</td></tr></table>


Table 467. SENSOR_HUB_14 register description


<table><tr><td>SensorHub14_[7:0]</td><td>Fourteenth byte associated to external sensors</td></tr></table>

## SENSOR_HUB_15 (10h)

Sensor hub output register (R) 

Fifteenth byte associated to external sensors. The content of the register is consistent with the SLVx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 468. SENSOR_HUB_15 register


<table><tr><td>SensorHub15_7</td><td>SensorHub15_6</td><td>SensorHub15_5</td><td>SensorHub15_4</td><td>SensorHub15_3</td><td>SensorHub15_2</td><td>SensorHub15_1</td><td>SensorHub15_0</td></tr></table>


Table 469. SENSOR_HUB_15 register description


<table><tr><td>SensorHub15_[7:0]</td><td>Fifteenth byte associated to external sensors</td></tr></table>

## SENSOR_HUB_16 (11h)

Sensor hub output register (R) 

Sixteenth byte associated to external sensors. The content of the register is consistent with the SLVx_CONFIG number of read operation configurations (for external sensors from ${ \sf x } = 0$ to x = 3). 


Table 470. SENSOR_HUB_16 register


<table><tr><td>SensorHub16_7</td><td>SensorHub16_6</td><td>SensorHub16_5</td><td>SensorHub16_4</td><td>SensorHub16_3</td><td>SensorHub16_2</td><td>SensorHub16_1</td><td>SensorHub16_0</td></tr></table>


Table 471. SENSOR_HUB_16 register description


<table><tr><td>SensorHub16_[7:0]</td><td>Sixteenth byte associated to external sensors</td></tr></table>

## SENSOR_HUB_17 (12h)

Sensor hub output register (R) 

Seventeenth byte associated to external sensors. The content of the register is consistent with the SLVx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 472. SENSOR_HUB_17 register


<table><tr><td>SensorHub17_7</td><td>SensorHub17_6</td><td>SensorHub17_5</td><td>SensorHub17_4</td><td>SensorHub17_3</td><td>SensorHub17_2</td><td>SensorHub17_1</td><td>SensorHub17_0</td></tr></table>


Table 473. SENSOR_HUB_17 register description


<table><tr><td>SensorHub17_[7:0]</td><td>Seventeenth byte associated to external sensors</td></tr></table>

## SENSOR_HUB_18 (13h)

Sensor hub output register (R) 

Eighteenth byte associated to external sensors. The content of the register is consistent with the SLVx_CONFIG number of read operation configurations (for external sensors from x = 0 to x = 3). 


Table 474. SENSOR_HUB_17 register


<table><tr><td>SensorHub18_7</td><td>SensorHub18_6</td><td>SensorHub18_5</td><td>SensorHub18_4</td><td>SensorHub18_3</td><td>SensorHub18_2</td><td>SensorHub18_1</td><td>SensorHub18_0</td></tr></table>


Table 475. SENSOR_HUB_17 register description


<table><tr><td>SensorHub18_[7:0]</td><td>Eighteenth byte associated to external sensors</td></tr></table>

## MASTER_CONFIG (14h)

Master configuration register (R/W) 


Table 476. MASTER_CONFIG register


<table><tr><td>RST_MASTER_REGS</td><td>WRITE_ONCE</td><td>START_CONFIG</td><td>PASS_THROUGH_MODE</td><td>0(1)</td><td>MASTER_ON</td><td>AUX_SENS_ON1</td><td>AUX_SENS_ON0</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 477. MASTER_CONFIG register description


<table><tr><td>RST_MASTER_REGS</td><td>Resets master logic and output registers. Must be set to 1 and then set to 0. Default value: 0</td></tr><tr><td>WRITE_ONCE</td><td>Slave 0 write operation is performed only at the first sensor hub cycle.Default value: 0(0: write operation for each sensor hub cycle;1: write operation only for the first sensor hub cycle)</td></tr><tr><td>START_CONFIG</td><td>Sensor hub trigger signal selection. Default value: 0(0: sensor hub trigger signal is the accelerometer/gyro data-ready;1: sensor hub trigger signal external from INT2 pin)</td></tr><tr><td>PASS_THROUGH_MODE</td><td><eq>I^{2}C</eq> interface pass-through. Default value: 0(0: pass-through disabled;1: pass-through enabled, primary <eq>I^{2}C</eq> line is short-circuited with the sensor hub line)</td></tr><tr><td>MASTER_ON</td><td>Enables sensor hub <eq>I^{2}C</eq> master. Default: 0(0: master <eq>I^{2}C</eq> of sensor hub disabled; 1: master <eq>I^{2}C</eq> of sensor hub enabled)</td></tr><tr><td>AUX_SENS_ON[1:0]</td><td>Number of external sensors to be read by the sensor hub.(00: one sensor (default);01: two sensors;10: three sensors;11: four sensors)</td></tr></table>

## SLV0_ADD (15h)

I²C slave address of the first external sensor (sensor 0) register (R/W) 


Table 478. SLV0_ADD register


<table><tr><td>slave0_add6</td><td>slave0_add5</td><td>slave0_add4</td><td>slave0_add3</td><td>slave0_add2</td><td>slave0_add1</td><td>slave0_add0</td><td>rw_0</td></tr></table>


Table 479. SLV_ADD register description


<table><tr><td>slave0_add[6:0]</td><td>I2C slave address of sensor 0 that can be read by the sensor hub.Default value: 0000000</td></tr><tr><td>rw_0</td><td>Read/write operation on sensor 0. Default value: 0(0: write operation; 1: read operation)</td></tr></table>

## SLV0_SUBADD (16h)

Address of register on the first external sensor (sensor 0) register (R/W) 


Table 480. SLV0_SUBADD register


<table><tr><td>slave0_reg7</td><td>slave0_reg6</td><td>slave0_reg5</td><td>slave0_reg4</td><td>slave0_reg3</td><td>slave0_reg2</td><td>slave0_reg1</td><td>slave0_reg0</td></tr></table>


Table 481. SLV0_SUBADD register description


<table><tr><td>slave0_reg[7:0]</td><td>Address of register on sensor 0 that has to be read/written according to the rw_0 bit value in SLV0_ADD (15h). Default value: 00000000</td></tr></table>

## 17.22

## SLV0_CONFIG (17h)

First external sensor (sensor 0) configuration and sensor hub settings register (R/W) 


Table 482. SLV0_CONFIG register


<table><tr><td>SHUB_ODR_2</td><td>SHUB_ODR_1</td><td>SHUB_ODR_0</td><td><eq>0^{(1)}</eq></td><td>BATCH_EXT_SENS_0_EN</td><td>Slave0_numop2</td><td>Slave0_numop1</td><td>Slave0_numop0</td></tr></table>


1. This bit must be set to 0 for the correct operation of the device. 



Table 483. SLV0_CONFIG register description


<table><tr><td>SHUB_ODR_[2:0]</td><td>Rate at which the master communicates.(000: 1.875 Hz;001: 15 Hz;010: 30 Hz;011: 60 Hz;100: 120 Hz (default);101: 240 Hz;110: 480 Hz;111: reserved</td></tr><tr><td>BATCH_EXT_SENS_0_EN</td><td>Enables FIFO data batching of first slave. Default value: 0</td></tr><tr><td>Slave0_numop[2:0]</td><td>Number of read operations on sensor 0. Default value: 000</td></tr></table>

## 17.25

## 17.23

## SLV1_ADD (18h)

I²C slave address of the second external sensor (sensor 1) register (R/W) 


Table 484. SLV1_ADD register


<table><tr><td>Slave1_add6</td><td>Slave1_add5</td><td>Slave1_add4</td><td>Slave1_add3</td><td>Slave1_add2</td><td>Slave1_add1</td><td>Slave1_add0</td><td>r_1</td></tr></table>


Table 485. SLV1_ADD register description


<table><tr><td>Slave1_add[6:0]</td><td>I2C slave address of sensor 1 that can be read by the sensor hub.Default value: 0000000</td></tr><tr><td>r_1</td><td>Enables read operation on sensor 1. Default value: 0(0: read operation disabled; 1: read operation enabled)</td></tr></table>

## SLV1_SUBADD (19h)

Address of register on the second external sensor (sensor 1) register (R/W) 


Table 486. SLV1_SUBADD register


<table><tr><td>Slave1_reg7</td><td>Slave1_reg6</td><td>Slave1_reg5</td><td>Slave1_reg4</td><td>Slave1_reg3</td><td>Slave1_reg2</td><td>Slave1_reg1</td><td>Slave1_reg0</td></tr></table>


Table 487. SLV1_SUBADD register description


<table><tr><td>Slave1_reg[7:0]</td><td>Address of register on sensor 1 that has to be read/written according to the r_1 bit value in SLV1_ADD (18h).</td></tr></table>

## SLV1_CONFIG (1Ah)

Second external sensor (sensor 2) configuration register (R/W) 


Table 488. SLV1_CONFIG register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>1^{(2)}</eq></td><td>BATCH_EXT_SENS_1_EN</td><td>Slave1_numop2</td><td>Slave1_numop1</td><td>Slave1_numop0</td></tr></table>

1. This bit must be set to 0 for the correct operation of the device. 

2. This bit must be set to 1 for the correct operation of the device. 


Table 489. SLV1_CONFIG register description


<table><tr><td>BATCH_EXT_SENS_1_EN</td><td>Enables FIFO data batching of second slave. Default value: 0</td></tr><tr><td>Slave1_numop[2:0]</td><td>Number of read operations on sensor 2. Default value: 000</td></tr></table>

## SLV2_ADD (1Bh)

I²C slave address of the third external sensor (sensor 2) register (R/W) 


Table 490. SLV2_ADD register


<table><tr><td>Slave2_add6</td><td>Slave2_add5</td><td>Slave2_add4</td><td>Slave2_add3</td><td>Slave2_add2</td><td>Slave2_add1</td><td>Slave2_add0</td><td>r_2</td></tr></table>


Table 491. SLV2_ADD register description


<table><tr><td>Slave2_add[6:0]</td><td>I2C slave address of sensor 2 that can be read by the sensor hub.</td></tr><tr><td>r_2</td><td>Enables read operation on sensor 2. Default value: 0(0: read operation disabled; 1: read operation enabled)</td></tr></table>

## SLV2_SUBADD (1Ch)

Address of register on the third external sensor (sensor 2) register (R/W) 


Table 492. SLV2_SUBADD register


<table><tr><td>Slave2_reg7</td><td>Slave2_reg6</td><td>Slave2_reg5</td><td>Slave2_reg4</td><td>Slave2_reg3</td><td>Slave2_reg2</td><td>Slave2_reg1</td><td>Slave2_reg0</td></tr></table>


Table 493. SLV2_SUBADD register description


<table><tr><td>Slave2_reg[7:0]</td><td>Address of register on sensor 2 that has to be read/written according to the r_2 bit value in SLV2_ADD (1Bh).</td></tr></table>

## SLV2_CONFIG (1Dh)

Third external sensor (sensor 2) configuration register (R/W) 


Table 494. SLV2_CONFIG register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td>BATCH_EXT_SENS_2_EN</td><td>Slave2_numop2</td><td>Slave2_numop1</td><td>Slave2_numop0</td></tr></table>

1. This bit must be set to 0 for the correct operation of the device. 


Table 495. SLV2_CONFIG register description


<table><tr><td>BATCH_EXT_SENS_2_EN</td><td>Enables FIFO data batching of third slave. Default value: 0</td></tr><tr><td>Slave2_numop[2:0]</td><td>Number of read operations on sensor 2. Default value: 000</td></tr></table>

## SLV3_ADD (1Eh)

I²C slave address of the fourth external sensor (sensor 3) register (R/W) 


Table 496. SLV3_ADD register


<table><tr><td>Slave3_add6</td><td>Slave3_add5</td><td>Slave3_add4</td><td>Slave3_add3</td><td>Slave3_add2</td><td>Slave3_add1</td><td>Slave3_add0</td><td>r_3</td></tr></table>


Table 497. SLV3_ADD register description


<table><tr><td>Slave3_add[6:0]</td><td>I2C slave address of sensor 3 that can be read by the sensor hub.</td></tr><tr><td>r_3</td><td>Enables read operation on sensor 3. Default value: 0(0: read operation disabled; 1: read operation enabled)</td></tr></table>

## SLV3_SUBADD (1Fh)

Address of register on the fourth external sensor (sensor 3) register (R/W) 


Table 498. SLV3_SUBADD register


<table><tr><td>Slave3_reg7</td><td>Slave3_reg6</td><td>Slave3_reg5</td><td>Slave3_reg4</td><td>Slave3_reg3</td><td>Slave3_reg2</td><td>Slave3_reg1</td><td>Slave3_reg0</td></tr></table>


Table 499. SLV3_SUBADD register description


<table><tr><td>Slave3_reg[7:0]</td><td>Address of register on sensor 3 that has to be read according to the r_3 bit value in SLV3_ADD (1Eh).</td></tr></table>

## SLV3_CONFIG (20h)

Fourth external sensor (sensor 3) configuration register (R/W) 


Table 500. SLV3_CONFIG register


<table><tr><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>0^{(1)}</eq></td><td><eq>BATCH\_EXT\_SENS\_3\_EN</eq></td><td>Slave3_numop2</td><td>Slave3_numop1</td><td>Slave3_numop0</td></tr></table>

1. This bit must be set to 0 for the correct operation of the device. 


Table 501. SLV3_CONFIG register description


<table><tr><td>BATCH_EXT_SENS_3_EN</td><td>Enables FIFO data batching of fourth slave. Default value: 0</td></tr><tr><td>Slave3_numop[2:0]</td><td>Number of read operations on sensor 3. Default value: 000</td></tr></table>

## 17.32

## DATAWRITE_SLV0 (21h)

Data to be written into the slave device register (R/W) 


Table 502. DATAWRITE_SLV0 register


<table><tr><td>Slave0_dataw7</td><td>Slave0_dataw6</td><td>Slave0_dataw5</td><td>Slave0_dataw4</td><td>Slave0_dataw3</td><td>Slave0_dataw2</td><td>Slave0_dataw1</td><td>Slave0_dataw0</td></tr></table>


Table 503. DATAWRITE_SLV0 register description


<table><tr><td>Slave0_dataw[7:0]</td><td>Data to be written into the slave 0 device according to the rw_0 bit in register SLV0_ADD (15h).Default value: 00000000</td></tr></table>

## 17.33

## STATUS_MASTER (22h)

Sensor hub source register (R) 


Table 504. STATUS_MASTER register


<table><tr><td>WR_ONCE_DONE</td><td>SLAVE3_NACK</td><td>SLAVE2_NACK</td><td>SLAVE1_NACK</td><td>SLAVE0_NACK</td><td>0</td><td>0</td><td>SENS_HUB_ENDOP</td></tr></table>

## Table 505. STATUS_MASTER register description

<table><tr><td>WR_ONCE_DONE</td><td>When the bit WRITE_ONCE in MASTER_CONFIG (14h) is configured as 1, this bit is set to 1 when the write operation on slave 0 has been performed and completed. Default value: 0</td></tr><tr><td>SLAVE3_NACK</td><td>This bit is set to 1 if Not acknowledge occurs on slave 3 communication. Default value: 0</td></tr><tr><td>SLAVE2_NACK</td><td>This bit is set to 1 if Not acknowledge occurs on slave 2 communication. Default value: 0</td></tr><tr><td>SLAVE1_NACK</td><td>This bit is set to 1 if Not acknowledge occurs on slave 1 communication. Default value: 0</td></tr><tr><td>SLAVE0_NACK</td><td>This bit is set to 1 if Not acknowledge occurs on slave 0 communication. Default value: 0</td></tr><tr><td>SENS_HUB_ENDOP</td><td>Sensor hub communication status. Default value: 0(0: sensor hub communication not concluded;1: sensor hub communication concluded)</td></tr></table>

## Soldering information

The LGA package is compliant with the ECOPACK and RoHS standard. 

It is qualified for soldering heat resistance according to JEDEC J-STD-020. 

For land pattern and soldering recommendations, consult technical note TN0018 available on www.st.com. 

## Package information

In order to meet environmental requirements, ST offers these devices in different grades of ECOPACK packages, depending on their level of environmental compliance. ECOPACK specifications, grade definitions and product status are available at: www.st.com. ECOPACK is an ST trademark. 

## 19.1 LGA-14L package information

Figure 33. LGA-14L 2.5 x 3.0 x 0.86 mm package outline and mechanical data 

![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/955f422399ca90c3e2cf3a5a767db745e1e830c24e95464a47b2c26f12a5d1c3.jpg)


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/9cf8212ac0800834d9dae012e37b1a5fc6c06326e87cc5141ef7193b00d9ba76.jpg)


Dimensions are in millimeter unless otherwise specified General tolerance is +/-0.1mm unless otherwise specified 


OUTER DIMENSIONS


<table><tr><td>ITEM</td><td>DIMENSION [mm]</td><td>TOLERANCE [mm]</td></tr><tr><td>Length [L]</td><td>2.50</td><td>±0.1</td></tr><tr><td>Width [W]</td><td>3.00</td><td>±0.1</td></tr><tr><td>Height [H]</td><td>0.86</td><td>MAX</td></tr></table>


DM00249496_5 


USER DIRECTION OF FEED 

## 19.2 LGA-14 packing information


Figure 34. Carrier tape information for LGA-14 package


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/af390d21c3bbf42ebe49fd1972ae2e8c11bcf346554428c66e9014a3c0441c7f.jpg)



Figure 35. LGA-14 package orientation in carrier tape


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/3acc78d1a3a654e8121bfa81003297310e1e404bb4cdbee76db65fe06aecab36.jpg)



Figure 36. Reel information for carrier tape of LGA-14 package


![image](https://cdn-mineru.openxlab.org.cn/result/2026-06-30/51b026cc-8b05-46aa-a52d-4e7bf5dc27be/edb9d1595d7becb3d2d2214a55d58eb5022a7c645249b728870ec91257cda26a.jpg)



Table 506. Reel dimensions for carrier tape of LGA-14 package


<table><tr><td colspan="2">Reel dimensions (mm)</td></tr><tr><td>A (max)</td><td>330</td></tr><tr><td>B (min)</td><td>1.5</td></tr><tr><td>C</td><td>13 ±0.25</td></tr><tr><td>D (min)</td><td>20.2</td></tr><tr><td>N (min)</td><td>60</td></tr><tr><td>G</td><td>12.4 +2/-0</td></tr><tr><td>T (max)</td><td>18.4</td></tr></table>

## Revision history


Table 507. Document revision history


<table><tr><td>Date</td><td>Revision</td><td>Changes</td></tr><tr><td>15-Jul-2022</td><td>1</td><td>Initial release</td></tr><tr><td>18-Nov-2022</td><td>2</td><td>Minor textual updatesAdded Section 2.8 Sensor fusion low powerUpdated Section 6.5 High-accuracy ODR mode and added HAODR_CFG (62h)Added Section 6.6 ODR-triggered mode and ODR_TRIG_CFG (06h)Minor update of registers in Section 9 Register description</td></tr><tr><td>01-Mar-2023</td><td>3</td><td>Added Note to Section 3.1 Pin connections</td></tr><tr><td>25-May-2023</td><td>4</td><td>Updated Section 2.1 Pedometer functions: step detector and step countersUpdated Note in Section 3.1 Pin connectionsUpdated footnotes of Table 3. Mechanical characteristicsUpdated Section 6 FunctionalityUpdated Section 6.5 High-accuracy ODR modeUpdated registers in Section 9 Register description</td></tr></table>

## Contents

1 Overview .... 3
2 Embedded low-power features.... 4
2.1 Pedometer functions: step detector and step counters .... 4
2.2 Pedometer algorithm .... 5
2.3 Tilt detection.... 5
2.4 Significant motion detection.... 5
2.5 Finite state machine.... 6
2.6 Machine learning core .... 7
2.7 Adaptive self-configuration (ASC).... 7
2.8 Sensor fusion low power.... 8
3 Pin description.... 9
3.1 Pin connections.... 10
4 Module specifications.... 12
4.1 Mechanical characteristics.... 12
4.2 Electrical characteristics.... 14
4.3 Temperature sensor characteristics.... 15
4.4 Communication interface characteristics.... 16
4.4.1 SPI - serial peripheral interface.... 16
4.4.2 I²C - inter-IC control interface.... 18
4.5 Absolute maximum ratings.... 19
4.6 Terminology.... 20
4.6.1 Sensitivity.... 20
4.6.2 Zero-g and zero-rate level.... 20
5 Digital interfaces.... 21
5.1 I²C/SPI interface.... 21
5.1.1 I²C serial interface.... 21
5.1.2 I²C operation.... 22
5.1.3 SPI bus interface.... 24
5.2 MIPI I3C® interface.... 27
5.2.1 MIPI I3C® slave interface.... 27
5.2.2 MIPI I3C® CCC supported commands.... 28
5.2.3 Overview of anti-spike filter management.... 29
5.3 Master I²C interface.... 30
5.4 Auxiliary SPI interface.... 30 

6 Functionality ....31
6.1 Operating modes....31
6.2 Accelerometer power modes....31
6.3 Accelerometer dual-channel mode....32
6.4 Gyroscope power modes....33
6.5 High-accuracy ODR mode....33
6.6 ODR-triggered mode....34
6.7 Analog hub functionality....34
6.8 Qvar functionality....34
6.9 Block diagram of filters....35
6.9.1 Block diagrams of the accelerometer filters....36
6.9.2 Block diagrams of the gyroscope filters....38
6.10 Enhanced EIS....40
6.11 OIS....41
6.11.1 Enabling OIS functionality and connection schemes....41
6.12 FIFO....44
6.12.1 Bypass mode....44
6.12.2 FIFO mode....45
6.12.3 Continuous mode....45
6.12.4 Continuous-to-FIFO mode....45
6.12.5 ContinuousWTM-to-full mode....45
6.12.6 Bypass-to-continuous mode....46
6.12.7 Bypass-to-FIFO mode....46
6.12.8 FIFO reading procedure....46
7 Application hints ....47
7.1 LSM6DSV16X electrical connections in mode 1....47
7.2 LSM6DSV16X electrical connections in mode 2....48
7.3 LSM6DSV16X electrical connections in mode 3....49
8 Register mapping....52
9 Register description ....56
9.1 FUNC_CFG_ACCESS (01h)....56
9.2 PIN_CTRL (02h)....57
9.3 IF_CFG (03h)....58
9.4 ODR_TRIG_CFG (06h)....58
9.5 FIFO_CTRL1 (07h)....59
9.6 FIFO_CTRL2 (08h)....59 

9.7 FIFO_CTRL3 (09h)....60
9.8 FIFO_CTRL4 (0Ah)....61
9.9 COUNTER_BDR_REG1 (0Bh)....62
9.10 COUNTER_BDR_REG2 (0Ch)....62
9.11 INT1_CTRL (0Dh)....63
9.12 INT2_CTRL (0Eh)....64
9.13 WHO_AM_I (0Fh)....64
9.14 CTRL1 (10h)....65
9.15 CTRL2 (11h)....66
9.16 CTRL3 (12h)....67
9.17 CTRL4 (13h)....68
9.18 CTRL5 (14h)....69
9.19 CTRL6 (15h)....69
9.20 CTRL7 (16h)....70
9.21 CTRL8 (17h)....71
9.22 CTRL9 (18h)....72
9.23 CTRL10 (19h)....74
9.24 CTRL_STATUS (1Ah)....74
9.25 FIFO_STATUS1 (1Bh)....75
9.26 FIFO_STATUS2 (1Ch)....75
9.27 ALL_INT_SRC (1Dh)....76
9.28 STATUS_REG (1Eh)....77
9.29 OUT_TEMP_L (20h), OUT_TEMP_H (21h)....78
9.30 OUTX_L_G (22h) and OUTX_H_G (23h)....78
9.31 OUTY_L_G (24h) and OUTY_H_G (25h)....79
9.32 OUTZ_L_G (26h) and OUTZ_H_G (27h)....79
9.33 OUTX_L_A (28h) and OUTX_H_A (29h)....80
9.34 OUTY_L_A (2Ah) and OUTY_H_A (2Bh)....80
9.35 OUTZ_L_A (2Ch) and OUTZ_H_A (2Dh)....81
9.36 UI_OUTX_L_G_OIS_EIS (2Eh) and UI_OUTX_H_G_OIS_EIS (2Fh)....81
9.37 UI_OUTY_L_G_OIS_EIS (30h) and UI_OUTY_H_G_OIS_EIS (31h)....82
9.38 UI_OUTZ_L_G_OIS_EIS (32h) and UI_OUTZ_H_G_OIS_EIS (33h)....82
9.39 UI_OUTX_L_A_OIS_DualC (34h) and UI_OUTX_H_A_OIS_DualC (35h)....83
9.40 UI_OUTY_L_A_OIS_DualC (36h) and UI_OUTY_H_A_OIS_DualC (37h)....83
9.41 UI_OUTZ_L_A_OIS_DualC (38h) and UI_OUTZ_H_A_OIS_DualC (39h)....84
9.42 AH_QVAR_OUT_L (3Ah) and AH_QVAR_OUT_H (3Bh)....84 

9.43 TIMESTAMP0 (40h), TIMESTAMP1 (41h), TIMESTAMP2 (42h), and TIMESTAMP3 (43h) 85
9.44 UI_STATUS_REG_OIS (44h) ..... 85
9.45 WAKE_UP_SRC (45h) ..... 86
9.46 TAP_SRC (46h) ..... 87
9.47 D6D_SRC (47h) ..... 88
9.48 STATUS_MASTER_MAINPAGE (48h) ..... 88
9.49 EMB_FUNC_STATUS_MAINPAGE (49h) ..... 89
9.50 FSM_STATUS_MAINPAGE (4Ah) ..... 89
9.51 MLC_STATUS_MAINPAGE (4Bh) ..... 90
9.52 INTERNAL_FREQ_FINE (4Fh) ..... 90
9.53 FUNCTIONS_ENABLE (50h) ..... 91
9.54 DEN (51h) ..... 92
9.55 INACTIVITY_DUR (54h) ..... 93
9.56 INACTIVITY_THS (55h) ..... 93
9.57 TAP_CFG0 (56h) ..... 94
9.58 TAP_CFG1 (57h) ..... 95
9.59 TAP_CFG2 (58h) ..... 95
9.60 TAP_THS_6D (59h) ..... 96
9.61 TAP_DUR (5Ah) ..... 97
9.62 WAKE_UP_THS (5Bh) ..... 97
9.63 WAKE_UP_DUR (5Ch) ..... 98
9.64 FREE_FALL (5Dh) ..... 98
9.65 MD1_CFG (5Eh) ..... 99
9.66 MD2_CFG (5Fh) ..... 100
9.67 HAODR_CFG (62h) ..... 100
9.68 EMB_FUNC_CFG (63h) ..... 101
9.69 UI_HANDSHAKE_CTRL (64h) ..... 101
9.70 UI_SPI2_SHARED_0 (65h) ..... 102
9.71 UI_SPI2_SHARED_1 (66h) ..... 102
9.72 UI_SPI2_SHARED_2 (67h) ..... 102
9.73 UI_SPI2_SHARED_3 (68h) ..... 103
9.74 UI_SPI2_SHARED_4 (69h) ..... 103
9.75 UI_SPI2_SHARED_5 (6Ah) ..... 103
9.76 CTRL_EIS (6Bh) ..... 104
9.77 UI_INT_OIS (6Fh) ..... 105
9.78 UI_CTRL1_OIS (70h) ..... 106 

9.79 UI_CTRL2_OIS (71h)....107
9.80 UI_CTRL3_OIS (72h)....108
9.81 X_OFS_USR (73h)....109
9.82 Y_OFS_USR (74h)....109
9.83 Z_OFS_USR (75h)....109
9.84 FIFO_DATA_OUT_TAG (78h)....110
9.85 FIFO_DATA_OUT_X_L (79h) and FIFO_DATA_OUT_X_H (7Ah)....111
9.86 FIFO_DATA_OUT_Y_L (7Bh) and FIFO_DATA_OUT_Y_H (7Ch)....111
9.87 FIFO_DATA_OUT_Z_L (7Dh) and FIFO_DATA_OUT_Z_H (7Eh)....111
10 SPI2 register mapping....112
11 SPI2 register description....113
11.1 SPI2_WHO_AM_I (0Fh)....113
11.2 SPI2_STATUS_REG_OIS (1Eh)....113
11.3 SPI2_OUT_TEMP_L (20h) and SPI2_OUT_TEMP_H (21h)....113
11.4 SPI2_OUTX_L_G_OIS (22h) and SPI2_OUTX_H_G_OIS (23h)....114
11.5 SPI2_OUTY_L_G_OIS (24h) and SPI2_OUTY_H_G_OIS (25h)....114
11.6 SPI2_OUTZ_L_G_OIS (26h) and SPI2_OUTZ_H_G_OIS (27h)....115
11.7 SPI2_OUTX_L_A_OIS (28h) and SPI2_OUTX_H_A_OIS (29h)....115
11.8 SPI2_OUTY_L_A_OIS (2Ah) and SPI2_OUTY_H_A_OIS (2Bh)....116
11.9 SPI2_OUTZ_L_A_OIS (2Ch) and SPI2_OUTZ_H_A_OIS (2Dh)....116
11.10 SPI2_HANDSHAKE_CTRL (6Eh)....116
11.11 SPI2_INT_OIS (6Fh)....117
11.12 SPI2_CTRL1_OIS (70h)....118
11.13 SPI2_CTRL2_OIS (71h)....119
11.14 SPI2_CTRL3_OIS (72h)....120
12 Embedded functions register mapping....121
13 Embedded functions register description....123
13.1 PAGE_SEL (02h)....123
13.2 EMB_FUNC_EN_A (04h)....123
13.3 EMB_FUNC_EN_B (05h)....124
13.4 EMB_FUNC_EXEC_STATUS (07h)....124
13.5 PAGE_ADDRESS (08h)....125
13.6 PAGE_VALUE (09h)....125
13.7 EMB_FUNC_INT1 (0Ah)....125
13.8 FSM_INT1 (0Bh)....126 

13.9 MLC_INT1 (0Dh)....127
13.10 EMB_FUNC_INT2 (0Eh)....127
13.11 FSM_INT2 (0Fh)....128
13.12 MLC_INT2 (11h)....129
13.13 EMB_FUNC_STATUS (12h)....129
13.14 FSM_STATUS (13h)....130
13.15 MLC_STATUS (15h)....130
13.16 PAGE_RW (17h)....131
13.17 EMB_FUNC_FIFO_EN_A (44h)....131
13.18 EMB_FUNC_FIFO_EN_B (45h)....132
13.19 FSM_ENABLE (46h)....132
13.20 FSM_LONG_COUNTER_L (48h) and FSM_LONG_COUNTER_H (49h)....133
13.21 INT_ACK_MASK (4Bh)....134
13.22 FSM_OUTS1 (4Ch)....135
13.23 FSM_OUTS2 (4Dh)....135
13.24 FSM_OUTS3 (4Eh)....136
13.25 FSM_OUTS4 (4Fh)....136
13.26 FSM_OUTS5 (50h)....137
13.27 FSM_OUTS6 (51h)....137
13.28 FSM_OUTS7 (52h)....138
13.29 FSM_OUTS8 (53h)....138
13.30 SFLP_ODR (5Eh)....139
13.31 FSM_ODR (5Fh)....139
13.32 MLC_ODR (60h)....140
13.33 STEP_COUNTER_L (62h) and STEP_COUNTER_H (63h)....140
13.34 EMB_FUNC_SRC (64h)....141
13.35 EMB_FUNC_INIT_A (66h)....142
13.36 EMB_FUNC_INIT_B (67h)....142
13.37 MLC1_SRC (70h)....143
13.38 MLC2_SRC (71h)....143
13.39 MLC3_SRC (72h)....143
13.40 MLC4_SRC (73h)....143
Embedded advanced features pages..... 144
Embedded advanced features register description ..... 147
15.1 Page 0 - embedded advanced features registers ..... 147
15.1.1 SFLP_GAME_GBIASX_L (6Eh) and SFLP_GAME_GBIASX_H (6Fh) ..... 147 

15.1.2 SFLP_GAME_GBIASY_L (70h) and SFLP_GAME_GBIASY_H (71h) ..... 147
15.1.3 SFLP_GAME_GBIASZ_L (72h) and SFLP_GAME_GBIASZ_H (73h) ..... 148
15.1.4 FSM_EXT_SENSITIVITY_L (BAh) and FSM_EXT_SENSITIVITY_H (BBh) ..... 148
15.1.5 FSM_EXT_OFFX_L (C0h) and FSM_EXT_OFFX_H (C1h) ..... 149
15.1.6 FSM_EXT_OFFY_L (C2h) and FSM_EXT_OFFY_H (C3h) ..... 149
15.1.7 FSM_EXT_OFFZ_L (C4h) and FSM_EXT_OFFZ_H (C5h) ..... 150
15.1.8 FSM_EXT_MATRIX_XX_L (C6h) and FSM_EXT_MATRIX_XX_H (C7h) ..... 150
15.1.9 FSM_EXT_MATRIX_XY_L (C8h) and FSM_EXT_MATRIX_XY_H (C9h) ..... 151
15.1.10 FSM_EXT_MATRIX_XZ_L (CAh) and FSM_EXT_MATRIX_XZ_H (CBh) ..... 151
15.1.11 FSM_EXT_MATRIX_YY_L (CCh) and FSM_EXT_MATRIX_YY_H (CDh) ..... 152
15.1.12 FSM_EXT_MATRIX_YZ_L (CEh) and FSM_EXT_MATRIX_YZ_H (CFh) ..... 152
15.1.13 FSM_EXT_MATRIX_ZZ_L (D0h) and FSM_EXT_MATRIX_ZZ_H (D1h) ..... 153
15.1.14 EXT_CFG_A (D4h) ..... 154
15.1.15 EXT_CFG_B (D5h) ..... 154
15.2 Page 1 - embedded advanced features registers ..... 155
15.2.1 FSM_LC_TIMEOUT_L (7Ah) and FSM_LC_TIMEOUT_H (7Bh) ..... 155
15.2.2 FSM_PROGRAMS (7Ch) ..... 155
15.2.3 FSM_START_ADD_L (7Eh) and FSM_START_ADD_H (7Fh) ..... 156
15.2.4 PEDO_CMD_REG (83h) ..... 156
15.2.5 PEDO_DEB_STEPS_CONF (84h) ..... 157
15.2.6 PEDO_SC_DELTAT_L (D0h) and PEDO_SC_DELTAT_H (D1h) ..... 157
15.2.7 MLC_EXT_SENSITIVITY_L (E8h) and MLC_EXT_SENSITIVITY_H (E9h) ..... 158
15.3 Page 2 - embedded advanced features registers ..... 159
15.3.1 EXT_FORMAT (00h) ..... 159
15.3.2 EXT_3BYTE_SENSITIVITY_L (02h) and EXT_3BYTE_SENSITIVITY_H (03h) ..... 159
15.3.3 EXT_3BYTE_OFFSET_XL (06h), EXT_3BYTE_OFFSET_L (07h) and EXT_3BYTE_OFFSET_H (08h) ..... 160
6 Sensor hub register mapping ..... 161
7 Sensor hub register description ..... 162
17.1 SENSOR_HUB_1 (02h) ..... 162
17.2 SENSOR_HUB_2 (03h) ..... 162
17.3 SENSOR_HUB_3 (04h) ..... 162
17.4 SENSOR_HUB_4 (05h) ..... 163
17.5 SENSOR_HUB_5 (06h) ..... 163
17.6 SENSOR_HUB_6 (07h) ..... 163
17.7 SENSOR_HUB_7 (08h) ..... 164
17.8 SENSOR_HUB_8 (09h) ..... 164 

17.9 SENSOR_HUB_9 (0Ah).... 164
17.10 SENSOR_HUB_10 (0Bh).... 165
17.11 SENSOR_HUB_11 (0Ch).... 165
17.12 SENSOR_HUB_12 (0Dh).... 165
17.13 SENSOR_HUB_13 (0Eh).... 166
17.14 SENSOR_HUB_14 (0Fh).... 166
17.15 SENSOR_HUB_15 (10h).... 166
17.16 SENSOR_HUB_16 (11h).... 167
17.17 SENSOR_HUB_17 (12h).... 167
17.18 SENSOR_HUB_18 (13h).... 167
17.19 MASTER_CONFIG (14h).... 168
17.20 SLV0_ADD (15h).... 169
17.21 SLV0_SUBADD (16h).... 169
17.22 SLV0_CONFIG (17h).... 169
17.23 SLV1_ADD (18h).... 170
17.24 SLV1_SUBADD (19h).... 170
17.25 SLV1_CONFIG (1Ah).... 170
17.26 SLV2_ADD (1Bh).... 171
17.27 SLV2_SUBADD (1Ch).... 171
17.28 SLV2_CONFIG (1Dh).... 171
17.29 SLV3_ADD (1Eh).... 172
17.30 SLV3_SUBADD (1Fh).... 172
17.31 SLV3_CONFIG (20h).... 172
17.32 DATAWRITE_SLV0 (21h).... 173
17.33 STATUS_MASTER (22h).... 173

18 Soldering information..... 174
19 Package information..... 175
19.1 LGA-14L package information..... 175
19.2 LGA-14 packing information..... 176
Revision history..... 178
List of tables..... 187
List of figures..... 197 

## List of tables

Table 1. Sensor fusion performance ..... 8
Table 2. Pin description ..... 11
Table 3. Mechanical characteristics ..... 12
Table 4. Electrical characteristics ..... 14
Table 5. Electrical parameters of Qvar (@Vdd = 1.8 V, T = 25 °C) ..... 14
Table 6. Temperature sensor characteristics ..... 15
Table 7. SPI slave timing values ..... 16
Table 8. I²C slave timing values ..... 18
Table 9. Absolute maximum ratings ..... 19
Table 10. Serial interface pin description ..... 21
Table 11. I²C terminology ..... 21
Table 12. SAD+read/write patterns ..... 22
Table 13. Transfer when master is writing one byte to slave ..... 22
Table 14. Transfer when master is writing multiple bytes to slave ..... 22
Table 15. Transfer when master is receiving (reading) one byte of data from slave ..... 22
Table 16. Transfer when master is receiving (reading) multiple bytes of data from slave ..... 22
Table 17. MIPI I3C® CCC commands ..... 28
Table 18. Master I²C pin details ..... 30
Table 19. Auxiliary SPI pin details ..... 30
Table 20. Accelerometer and gyroscope ODR selection in high-accuracy ODR mode ..... 33
Table 21. Gyroscope LPF2 bandwidth selection ..... 38
Table 22. OIS configurations ..... 41
Table 23. Internal pin status ..... 50
Table 24. Registers address map ..... 52
Table 25. FUNC_CFG_ACCESS register ..... 56
Table 26. FUNC_CFG_ACCESS register description ..... 56
Table 27. PIN_CTRL register ..... 57
Table 28. PIN_CTRL register description ..... 57
Table 29. IF_CFG register ..... 58
Table 30. IF_CFG register description ..... 58
Table 31. ODR_TRIG_CFG register ..... 58
Table 32. ODR_TRIG_CFG register description ..... 58
Table 33. FIFO_CTRL1 register ..... 59
Table 34. FIFO_CTRL1 register description ..... 59
Table 35. FIFO_CTRL2 register ..... 59
Table 36. FIFO_CTRL2 register description ..... 59
Table 37. FIFO_CTRL3 register ..... 60
Table 38. FIFO_CTRL3 register description ..... 60
Table 39. FIFO_CTRL4 register ..... 61
Table 40. FIFO_CTRL4 register description ..... 61
Table 41. COUNTER_BDR_REG1 register ..... 62
Table 42. COUNTER_BDR_REG1 register description ..... 62
Table 43. COUNTER_BDR_REG2 register ..... 62
Table 44. COUNTER_BDR_REG2 register description ..... 62
Table 45. INT1_CTRL register ..... 63
Table 46. INT1_CTRL register description ..... 63
Table 47. INT2_CTRL register ..... 64
Table 48. INT2_CTRL register description ..... 64
Table 49. WhoAml register ..... 64
Table 50. CTRL1 register ..... 65
Table 51. CTRL1 register description ..... 65
Table 52. Accelerometer ODR selection ..... 65
Table 53. CTRL2 register ..... 66 

Table 54. CTRL2 register description ..... 66
Table 55. Gyroscope ODR selection ..... 66
Table 56. CTRL3 register ..... 67
Table 57. CTRL3 register description ..... 67
Table 58. CTRL4 register ..... 68
Table 59. CTRL4 register description ..... 68
Table 60. CTRL5 register ..... 69
Table 61. CTRL5 register description ..... 69
Table 62. CTRL6 register ..... 69
Table 63. CTRL6 register description ..... 69
Table 64. Gyroscope LPF1 + LPF2 bandwidth selection ..... 70
Table 65. CTRL7 register ..... 70
Table 66. CTRL7 register description ..... 70
Table 67. CTRL8 register ..... 71
Table 68. CTRL8 register description ..... 71
Table 69. Accelerometer bandwidth configurations ..... 71
Table 70. CTRL9 register ..... 72
Table 71. CTRL9 register description ..... 72
Table 72. CTRL10 register ..... 74
Table 73. CTRL10 register description ..... 74
Table 74. CTRL_STATUS register ..... 74
Table 75. CTRL_STATUS register description ..... 74
Table 76. FIFO_STATUS1 register ..... 75
Table 77. FIFO_STATUS1 register description ..... 75
Table 78. FIFO_STATUS2 register ..... 75
Table 79. FIFO_STATUS2 register description ..... 75
Table 80. ALL_INT_SRC register ..... 76
Table 81. ALL_INT_SRC register description ..... 76
Table 82. STATUS_REG register ..... 77
Table 83. STATUS_REG register description ..... 77
Table 84. OUT_TEMP_L register ..... 78
Table 85. OUT_TEMP_H register ..... 78
Table 86. OUT_TEMP register description ..... 78
Table 87. OUTX_L_G register ..... 78
Table 88. OUTX_H_G register ..... 78
Table 89. OUTX_G register description ..... 78
Table 90. OUTY_L_G register ..... 79
Table 91. OUTY_H_G register ..... 79
Table 92. OUTY_G register description ..... 79
Table 93. OUTZ_L_G register ..... 79
Table 94. OUTZ_H_G register ..... 79
Table 95. OUTZ_H_G register description ..... 79
Table 96. OUTX_L_A register ..... 80
Table 97. OUTX_H_A register ..... 80
Table 98. OUTX_A register description ..... 80
Table 99. OUTY_L_A register ..... 80
Table 100. OUTY_H_A register ..... 80
Table 101. OUTY_A register description ..... 80
Table 102. OUTZ_L_A register ..... 81
Table 103. OUTZ_H_A register ..... 81
Table 104. OUTZ_A register description ..... 81
Table 105. UI_OUTX_L_G_OIS_EIS register ..... 81
Table 106. UI_OUTX_H_G_OIS_EIS register ..... 81
Table 107. UI_OUTX_G_OIS_EIS register description ..... 81
Table 108. UI_OUTY_L_G_OIS_EIS register ..... 82 

Table 109. UI_OUTY_H_G_OIS_EIS register ..... 82
Table 110. UI_OUTY_G_OIS_EIS register description ..... 82
Table 111. UI_OUTZ_L_G_OIS_EIS register ..... 82
Table 112. UI_OUTZ_H_G_OIS_EIS register ..... 82
Table 113. UI_OUTZ_G_OIS_EIS register description ..... 82
Table 114. UI_OUTX_L_A_OIS_DualC register ..... 83
Table 115. UI_OUTX_H_A_OIS_DualC register ..... 83
Table 116. UI_OUTX_A_OIS_DualC register description ..... 83
Table 117. UI_OUTY_L_A_OIS_DualC register ..... 83
Table 118. UI_OUTY_H_A_OIS_DualC register ..... 83
Table 119. UI_OUTY_A_OIS_DualC register description ..... 83
Table 120. UI_OUTZ_L_A_OIS_DualC register ..... 84
Table 121. UI_OUTZ_H_A_OIS_DualC register ..... 84
Table 122. UI_OUTZ_A_OIS_DualC register description ..... 84
Table 123. AH_QVAR_OUT_L register ..... 84
Table 124. AH_QVAR_OUT_H register ..... 84
Table 125. AH_QVAR_OUT register description ..... 84
Table 126. TIMESTAMP output registers ..... 85
Table 127. TIMESTAMP output register description ..... 85
Table 128. UI_STATUS_REG_OIS register ..... 85
Table 129. UI_STATUS_REG_OIS register description ..... 85
Table 130. WAKE_UP_SRC register ..... 86
Table 131. WAKE_UP_SRC register description ..... 86
Table 132. TAP_SRC register ..... 87
Table 133. TAP_SRC register description ..... 87
Table 134. D6D_SRC register ..... 88
Table 135. D6D_SRC register description ..... 88
Table 136. STATUS_MASTER_MAINPAGE register ..... 88
Table 137. STATUS_MASTER_MAINPAGE register description ..... 88
Table 138. EMB_FUNC_STATUS_MAINPAGE register ..... 89
Table 139. EMB_FUNC_STATUS_MAINPAGE register description ..... 89
Table 140. FSM_STATUS_MAINPAGE register ..... 89
Table 141. FSM_STATUS_MAINPAGE register description ..... 89
Table 142. MLC_STATUS_MAINPAGE register ..... 90
Table 143. MLC_STATUS_MAINPAGE register description ..... 90
Table 144. INTERNAL_FREQ_FINE register ..... 90
Table 145. INTERNAL_FREQ_FINE register description ..... 90
Table 146. ODRcoeff values ..... 90
Table 147. FUNCTIONS_ENABLE register ..... 91
Table 148. FUNCTIONS_ENABLE register description ..... 91
Table 149. DEN register ..... 92
Table 150. DEN register description ..... 92
Table 151. Trigger mode selection ..... 92
Table 152. INACTIVITY_DUR register ..... 93
Table 153. INACTIVITY_DUR register description ..... 93
Table 154. INACTIVITY_THS register ..... 93
Table 155. INACTIVITY_THS register description ..... 93
Table 156. TAP_CFG0 register ..... 94
Table 157. TAP_CFG0 register description ..... 94
Table 158. TAP_CFG1 register ..... 95
Table 159. TAP_CFG1 register description ..... 95
Table 160. TAP_priority decoding ..... 95
Table 161. TAP_CFG2 register ..... 95
Table 162. TAP_CFG2 register description ..... 95
Table 163. TAP_THS_6D register ..... 96 

Table 164. TAP_THS_6D register description ..... 96
Table 165. Threshold for D4D/D6D function ..... 96
Table 166. TAP_DUR register ..... 97
Table 167. TAP_DUR register description ..... 97
Table 168. WAKE_UP_THS register ..... 97
Table 169. WAKE_UP_THS register description ..... 97
Table 170. WAKE_UP_DUR register ..... 98
Table 171. WAKE_UP_DUR register description ..... 98
Table 172. FREE_FALL register ..... 98
Table 173. FREE_FALL register description ..... 98
Table 174. Threshold for free-fall function ..... 98
Table 175. MD1_CFG register ..... 99
Table 176. MD1_CFG register description ..... 99
Table 177. MD2_CFG register ..... 100
Table 178. MD2_CFG register description ..... 100
Table 179. HAODR_CFG register ..... 100
Table 180. HAODR_CFG register description ..... 100
Table 181. EMB_FUNC_CFG register ..... 101
Table 182. EMB_FUNC_CFG register description ..... 101
Table 183. UI_HANDSHAKE_CTRL register ..... 101
Table 184. UI_HANDSHAKE_CTRL register description ..... 101
Table 185. UI_SPI2_SHARED_0 register ..... 102
Table 186. UI_SPI2_SHARED_0 register description ..... 102
Table 187. UI_SPI2_SHARED_1 register ..... 102
Table 188. UI_SPI2_SHARED_1 register description ..... 102
Table 189. UI_SPI2_SHARED_2 register ..... 102
Table 190. UI_SPI2_SHARED_2 register description ..... 102
Table 191. UI_SPI2_SHARED_3 register ..... 103
Table 192. UI_SPI2_SHARED_3 register description ..... 103
Table 193. UI_SPI2_SHARED_4 register ..... 103
Table 194. UI_SPI2_SHARED_4 register description ..... 103
Table 195. UI_SPI2_SHARED_5 register ..... 103
Table 196. UI_SPI2_SHARED_5 register description ..... 103
Table 197. CTRL_EIS register ..... 104
Table 198. CTRL_EIS register description ..... 104
Table 199. Gyroscope EIS chain digital LPF_EIS filter bandwidth selection ..... 104
Table 200. UI_INT_OIS register ..... 105
Table 201. UI_INT_OIS register description ..... 105
Table 202. UI_CTRL1_OIS register ..... 106
Table 203. UI_CTRL1_OIS register description ..... 106
Table 204. UI_CTRL2_OIS register ..... 107
Table 205. UI_CTRL2_OIS register description ..... 107
Table 206. Gyroscope OIS chain digital LPF1 filter bandwidth selection ..... 107
Table 207. UI_CTRL3_OIS register ..... 108
Table 208. UI_CTRL3_OIS register description ..... 108
Table 209. Accelerometer OIS channel bandwidth and phase ..... 108
Table 210. X_OFS_USR register ..... 109
Table 211. X_OFS_USR register description ..... 109
Table 212. Y_OFS_USR register ..... 109
Table 213. Y_OFS_USR register description ..... 109
Table 214. Z_OFS_USR register ..... 109
Table 215. Z_OFS_USR register description ..... 109
Table 216. FIFO_DATA_OUT_TAG register..... . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . 

Table 219. FIFO_DATA_OUT_X_H and FIFO_DATA_OUT_X_L registers ..... 111
Table 220. FIFO_DATA_OUT_X_H and FIFO_DATA_OUT_X_L register description ..... 111
Table 221. FIFO_DATA_OUT_Y_H and FIFO_DATA_OUT_Y_L registers ..... 111
Table 222. FIFO_DATA_OUT_Y_H and FIFO_DATA_OUT_Y_L register description ..... 111
Table 223. FIFO_DATA_OUT_Z_H and FIFO_DATA_OUT_Z_L registers ..... 111
Table 224. FIFO_DATA_OUT_Z_H and FIFO_DATA_OUT_Z_L register description ..... 111
Table 225. SPI2 register address map ..... 112
Table 226. SPI2_WhoAml register ..... 113
Table 227. SPI2_STATUS_REG_OIS register ..... 113
Table 228. SPI2_STATUS_REG_OIS description ..... 113
Table 229. SPI2_OUT_TEMP_L register ..... 113
Table 230. SPI2_OUT_TEMP_H register ..... 113
Table 231. SPI2_OUT_TEMP register description ..... 113
Table 232. SPI2_OUTX_L_G_OIS register ..... 114
Table 233. SPI2_OUTX_H_G_OIS register ..... 114
Table 234. SPI2_OUTX_H_G_OIS register description ..... 114
Table 235. SPI2_OUTY_L_G_OIS register ..... 114
Table 236. SPI2_OUTY_H_G_OIS register ..... 114
Table 237. SPI2_OUTY_H_G_OIS register description ..... 114
Table 238. SPI2_OUTZ_L_G_OIS register ..... 115
Table 239. SPI2_OUTZ_H_G_OIS register ..... 115
Table 240. SPI2_OUTZ_H_G_OIS register description ..... 115
Table 241. SPI2_OUTX_L_A_OIS register ..... 115
Table 242. SPI2_OUTX_H_A_OIS register ..... 115
Table 243. SPI2_OUTX_H_A_OIS register description ..... 115
Table 244. SPI2_OUTY_L_A_OIS register ..... 116
Table 245. SPI2_OUTY_H_A_OIS register ..... 116
Table 246. SPI2_OUTY_H_A_OIS register description ..... 116
Table 247. SPI2_OUTZ_L_A_OIS register ..... 116
Table 248. SPI2_OUTZ_H_A_OIS register ..... 116
Table 249. SPI2_OUTZ_H_A_OIS register description ..... 116
Table 250. SPI2_HANDSHAKE_CTRL register ..... 116
Table 251. SPI2_HANDSHAKE_CTRL register description ..... 116
Table 252. SPI2_INT_OIS register ..... 117
Table 253. SPI2_INT_OIS register description ..... 117
Table 254. SPI2_CTRL1_OIS register ..... 118
Table 255. SPI2_CTRL1_OIS register description ..... 118
Table 256. SPI2_CTRL2_OIS register ..... 119
Table 257. SPI2_CTRL2_OIS register description ..... 119
Table 258. Gyroscope OIS chain digital LPF1 filter bandwidth selection ..... 119
Table 259. SPI2_CTRL3_OIS register ..... 120
Table 260. SPI2_CTRL3_OIS register description ..... 120
Table 261. Accelerometer OIS channel bandwidth and phase ..... 120
Table 262. Register address map - embedded functions ..... 121
Table 263. PAGE_SEL register ..... 123
Table 264. PAGE_SEL register description ..... 123
Table 265. EMB_FUNC_EN_A register ..... 123
Table 266. EMB_FUNC_EN_A register description ..... 123
Table 267. EMB_FUNC_EN_B register ..... 124
Table 268. EMB_FUNC_EN_B register description ..... 124
Table 269. EMB_FUNC_EXEC_STATUS register ..... 124
Table 270. EMB_FUNC_EXEC_STATUS register description ..... 124
Table 271. PAGE_ADDRESS register ..... 125
Table 272. PAGE_ADDRESS register description ..... 125
Table 273. PAGE_VALUE register ..... 125 

Table 274. PAGE_VALUE register description ..... 125
Table 275. EMB_FUNC_INT1 register ..... 125
Table 276. EMB_FUNC_INT1 register description ..... 125
Table 277. FSM_INT1 register..... 126
Table 278. FSM_INT1 register description ..... 126
Table 279. MLC_INT1 register..... 127
Table 280. MLC_INT1 register description ..... 127
Table 281. EMB_FUNC_INT2 register ..... 127
Table 282. EMB_FUNC_INT2 register description ..... 127
Table 283. FSM_INT2 register..... 128
Table 284. FSM_INT2 register description ..... 128
Table 285. MLC_INT2 register..... 129
Table 286. MLC_INT2 register description ..... 129
Table 287. EMB_FUNC_STATUS register..... 129
Table 288. EMB_FUNC_STATUS register description..... 129
Table 289. FSM_STATUS register ..... 130
Table 290. FSM_STATUS register description ..... 130
Table 291. MLC_STATUS register ..... 130
Table 292. MLC_STATUS register description ..... 130
Table 293. PAGE_RW register ..... 131
Table 294. PAGE_RW register description ..... 131
Table 295. EMB_FUNC_FIFO_EN_A register ..... 131
Table 296. EMB_FUNC_FIFO_EN_A register description ..... 131
Table 297. EMB_FUNC_FIFO_EN_B register ..... 132
Table 298. EMB_FUNC_FIFO_EN_B register description ..... 132
Table 299. FSM_ENABLE register..... 132
Table 300. FSM_ENABLE register description ..... 132
Table 301. FSM_LONG_COUNTER_L register ..... 133
Table 302. FSM_LONG_COUNTER_L register description ..... 133
Table 303. FSM_LONG_COUNTER_H register ..... 133
Table 304. FSM_LONG_COUNTER_H register description ..... 133
Table 305. INT_ACK_MASK register ..... 134
Table 306. INT_ACK_MASK register description ..... 134
Table 307. FSM_OUTS1 register..... 135
Table 308. FSM_OUTS1 register description..... 135
Table 309. FSM_OUTS2 register..... 135
Table 310. FSM_OUTS2 register description..... 135
Table 311. FSM_OUTS3 register..... 136
Table 312. FSM_OUTS3 register description..... 136
Table 313. FSM_OUTS4 register..... 136
Table 314. FSM_OUTS4 register description..... 136
Table 315. FSM_OUTS5 register..... 137
Table 316. FSM_OUTS5 register description..... 137
Table 317. FSM_OUTS6 register..... 137
Table 318. FSM_OUTS6 register description..... 137
Table 319. FSM_OUTS7 register..... 138
Table 320. FSM_OUTS7 register description..... 138
Table 321. FSM_OUTS8 register..... 138
Table 322. FSM_OUTS8 register description..... 138
Table 323. SFLP_ODR register ..... 139
Table 324. SFLP_ODR register description ..... 139
Table 325. FSM_ODR register..... 139
Table 326. FSM_ODR register description ..... 139
Table 327. MLC_ODR register..... 140
Table 328. MLC_ODR register description ..... 140 

Table 329. STEP_COUNTER_L register. 140
Table 330. STEP_COUNTER_L register description. 140
Table 331. STEP_COUNTER_H register. 140
Table 332. STEP_COUNTER_H register description. 140
Table 333. EMB_FUNC_SRC register. 141
Table 334. EMB_FUNC_SRC register description. 141
Table 335. EMB_FUNC_INIT_A register. 142
Table 336. EMB_FUNC_INIT_A register description. 142
Table 337. EMB_FUNC_INIT_B register. 142
Table 338. EMB_FUNC_INIT_B register description. 142
Table 339. MLC1_SRC register. 143
Table 340. MLC1_SRC register description. 143
Table 341. MLC2_SRC register. 143
Table 342. MLC2_SRC register description. 143
Table 343. MLC3_SRC register. 143
Table 344. MLC3_SRC register description. 143
Table 345. MLC4_SRC register. 143
Table 346. MLC4_SRC register description. 143
Table 347. Register address map - embedded advanced features page 0. 144
Table 348. Register address map - embedded advanced features page 1. 145
Table 349. Register address map - embedded advanced features page 2. 145
Table 350. SFLP_GAME_GBIASX_L register. 147
Table 351. SFLP_GAME_GBIASX_L register description. 147
Table 352. SFLP_GAME_GBIASX_H register. 147
Table 353. SFLP_GAME_GBIASX_H register description. 147
Table 354. SFLP_GAME_GBIASY_L register. 147
Table 355. SFLP_GAME_GBIASY_L register description. 147
Table 356. SFLP_GAME_GBIASY_H register. 147
Table 357. SFLP_GAME_GBIASY_H register description. 147
Table 358. SFLP_GAME_GBIASZ_L register. 148
Table 359. SFLP_GAME_GBIASZ_L register description. 148
Table 360. SFLP_GAME_GBIASZ_H register. 148
Table 361. SFLP_GAME_GBIASZ_H register description. 148
Table 362. FSM_EXT_SENSITIVITY_L register. 148
Table 363. FSM_EXT_SENSITIVITY_L register description. 148
Table 364. FSM_EXT_SENSITIVITY_H register. 148
Table 365. FSM_EXT_SENSITIVITY_H register description. 148
Table 366. FSM_EXT_OFFX_L register. 149
Table 367. FSM_EXT_OFFX_L register description. 149
Table 368. FSM_EXT_OFFX_H register. 149
Table 369. FSM_EXT_OFFX_H register description. 149
Table 370. FSM_EXT_OFFY_L register. 149
Table 371. FSM_EXT_OFFY_L register description. 149
Table 372. FSM_EXT_OFFY_H register. 149
Table 373. FSM_EXT_OFFY_H register description. 149
Table 374. FSM_EXT_OFFZ_L register. 150
Table 375. FSM_EXT_OFFZ_L register description. 150
Table 376. FSM_EXT_OFFZ_H register. 150
Table 377. FSM_EXT_OFFZ_H register description. 150
Table 378. FSM_EXT_MATRIX_XX_L register. 150
Table 379. FSM_EXT_MATRIX_XX_L register description. 150
Table 380. FSM_EXT_MATRIX_XX_H register. 150
Table 381. FSM_EXT_MATRIX_XX_H register description. 150
Table 382. FSM_EXT_MATRIX_XY_L register. 151
Table 383. FSM_EXT_MATRIX_XY_L register description. 151 

Table 384. FSM_EXT_MATRIX_XY_H register ..... 151
Table 385. FSM_EXT_MATRIX_XY_H register description ..... 151
Table 386. FSM_EXT_MATRIX_XZ_L register ..... 151
Table 387. FSM_EXT_MATRIX_XZ_L register description ..... 151
Table 388. FSM_EXT_MATRIX_XZ_H register ..... 151
Table 389. FSM_EXT_MATRIX_XZ_H register description ..... 151
Table 390. FSM_EXT_MATRIX_YY_L register ..... 152
Table 391. FSM_EXT_MATRIX_YY_L register description ..... 152
Table 392. FSM_EXT_MATRIX_YY_H register ..... 152
Table 393. FSM_EXT_MATRIX_YY_H register description ..... 152
Table 394. FSM_EXT_MATRIX_YZ_L register ..... 152
Table 395. FSM_EXT_MATRIX_YZ_L register description ..... 152
Table 396. FSM_EXT_MATRIX_YZ_H register ..... 152
Table 397. FSM_EXT_MATRIX_YZ_H register description ..... 152
Table 398. FSM_EXT_MATRIX_ZZ_L register ..... 153
Table 399. FSM_EXT_MATRIX_ZZ_L register description ..... 153
Table 400. FSM_EXT_MATRIX_ZZ_H register ..... 153
Table 401. FSM_EXT_MATRIX_ZZ_H register description ..... 153
Table 402. EXT_CFG_A register ..... 154
Table 403. EXT_CFG_A description ..... 154
Table 404. EXT_CFG_B register ..... 154
Table 405. EXT_CFG_B description ..... 154
Table 406. FSM_LC_TIMEOUT_L register ..... 155
Table 407. FSM_LC_TIMEOUT_L register description ..... 155
Table 408. FSM_LC_TIMEOUT_H register ..... 155
Table 409. FSM_LC_TIMEOUT_H register description ..... 155
Table 410. FSM_PROGRAMS register ..... 155
Table 411. FSM_PROGRAMS register description ..... 155
Table 412. FSM_START_ADD_L register ..... 156
Table 413. FSM_START_ADD_L register description ..... 156
Table 414. FSM_START_ADD_H register ..... 156
Table 415. FSM_START_ADD_H register description ..... 156
Table 416. PEDO_CMD_REG register ..... 156
Table 417. PEDO_CMD_REG register description ..... 156
Table 418. PEDO_DEB_STEPS_CONF register ..... 157
Table 419. PEDO_DEB_STEPS_CONF register description ..... 157
Table 420. PEDO_SC_DELTAT_L register ..... 157
Table 421. PEDO_SC_DELTAT_H register ..... 157
Table 422. PEDO_SC_DELTAT_H/L register description ..... 157
Table 423. MLC_EXT_SENSITIVITY_L register ..... 158
Table 424. MLC_EXT_SENSITIVITY_L register description ..... 158
Table 425. MLC_EXT_SENSITIVITY_H register ..... 158
Table 426. MLC_EXT_SENSITIVITY_H register description ..... 158
Table 427. EXT_FORMAT register ..... 159
Table 428. EXT_FORMAT register description ..... 159
Table 429. EXT_3BYTE_SENSITIVITY_L register ..... 159
Table 430. EXT_3BYTE_SENSITIVITY_L register description ..... 159
Table 431. EXT_3BYTE_SENSITIVITY_H register ..... 159
Table 432. EXT_3BYTE_SENSITIVITY_H register description ..... 159
Table 433. EXT_3BYTE_OFFSET_XL register ..... 160
Table 434. EXT_3BYTE_OFFSET_XL register description ..... 160
Table 435. EXT_3BYTE_OFFSET_L register ..... 160
Table 436. EXT_3BYTE_OFFSET_L register description ..... 160
Table 437. EXT_3BYTE_OFFSET_H register ..... 160
Table 438. EXT_3BYTE_OFFSET_H register description ..... 160 

Table 439. Register address map - sensor hub registers. 161
Table 440. SENSOR_HUB_1 register. 162
Table 441. SENSOR_HUB_1 register description. 162
Table 442. SENSOR_HUB_2 register. 162
Table 443. SENSOR_HUB_2 register description. 162
Table 444. SENSOR_HUB_3 register. 162
Table 445. SENSOR_HUB_3 register description. 162
Table 446. SENSOR_HUB_4 register. 163
Table 447. SENSOR_HUB_4 register description. 163
Table 448. SENSOR_HUB_5 register. 163
Table 449. SENSOR_HUB_5 register description. 163
Table 450. SENSOR_HUB_6 register. 163
Table 451. SENSOR_HUB_6 register description. 163
Table 452. SENSOR_HUB_7 register. 164
Table 453. SENSOR_HUB_7 register description. 164
Table 454. SENSOR_HUB_8 register. 164
Table 455. SENSOR_HUB_8 register description. 164
Table 456. SENSOR_HUB_9 register. 164
Table 457. SENSOR_HUB_9 register description. 164
Table 458. SENSOR_HUB_10 register. 165
Table 459. SENSOR_HUB_10 register description. 165
Table 460. SENSOR_HUB_11 register. 165
Table 461. SENSOR_HUB_11 register description. 165
Table 462. SENSOR_HUB_12 register. 165
Table 463. SENSOR_HUB_12 register description. 165
Table 464. SENSOR_HUB_13 register. 166
Table 465. SENSOR_HUB_13 register description. 166
Table 466. SENSOR_HUB_14 register. 166
Table 467. SENSOR_HUB_14 register description. 166
Table 468. SENSOR_HUB_15 register. 166
Table 469. SENSOR_HUB_15 register description. 166
Table 470. SENSOR_HUB_16 register. 167
Table 471. SENSOR_HUB_16 register description. 167
Table 472. SENSOR_HUB_17 register. 167
Table 473. SENSOR_HUB_17 register description. 167
Table 474. SENSOR_HUB_17 register. 167
Table 475. SENSOR_HUB_17 register description. 167
Table 476. MASTER_CONFIG register. 168
Table 477. MASTER_CONFIG register description. 168
Table 478. SLV0_ADD register . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
Table 479. SLV_ADD register description . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
Table 480. SLV0_SUBADD register . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
Table 481. SLV0_SUBADD register description. 169
Table 482. SLV0_CONFIG register. 169
Table 483. SLV0_CONFIG register description. 169
Table 484. SLV1_ADD register. 170
Table 485. SLV1_ADD register description. 170
Table 486. SLV1_SUBADD register. 170
Table 487. SLV1_SUBADD register description. 170
Table 488. SLV1_CONFIG register. 170
Table 489. SLV1_CONFIG register description. 170
Table 490. SLV2_ADD register. 171
Table 491. SLV2_ADD register description. 171
Table 492. SLV2_SUBADD register. 171
Table 493. SLV2_SUBADD register description. 171 

Table 494. SLV2_CONFIG register ..... 171
Table 495. SLV2_CONFIG register description ..... 171
Table 496. SLV3_ADD register ..... 172
Table 497. SLV3_ADD register description ..... 172
Table 498. SLV3_SUBADD register ..... 172
Table 499. SLV3_SUBADD register description ..... 172
Table 500. SLV3_CONFIG register ..... 172
Table 501. SLV3_CONFIG register description ..... 172
Table 502. DATAWRITE_SLV0 register..... 173
Table 503. DATAWRITE_SLV0 register description ..... 173
Table 504. STATUS_MASTER register..... 173
Table 505. STATUS_MASTER register description..... 173
Table 506. Reel dimensions for carrier tape of LGA-14 package ..... 177
Table 507. Document revision history..... 178 

## List of figures

Figure 1. Four-stage pedometer algorithm. 5  
Figure 2. Generic state machine. 6  
Figure 3. State machine in the LSM6DSV16X. 6  
Figure 4. Machine learning core in the LSM6DSV16X. 7  
Figure 5. Pin connections. 9  
Figure 6. LSM6DSV16X connection modes. 10  
Figure 7. SPI slave timing in mode 0. 16  
Figure 8. SPI slave timing in mode 3. 17  
Figure 9. I²C slave timing diagram. 18  
Figure 10. Read and write protocol (in mode 3). 24  
Figure 11. SPI read protocol (in mode 3). 25  
Figure 12. Multiple byte SPI read protocol (2-byte example) (in mode 3). 25  
Figure 13. SPI write protocol (in mode 3). 26  
Figure 14. Multiple byte SPI write protocol (2-byte example) (in mode 3). 26  
Figure 15. SPI read protocol in 3-wire mode (in mode 3). 26  
Figure 16. Single-channel mode (XL_DualC_EN = 0). 32  
Figure 17. Dual-channel mode (XL_DualC_EN = 1). 32  
Figure 18. Block diagram of filters. 35  
Figure 19. Accelerometer UI chain. 36  
Figure 20. Accelerometer composite filter. 36  
Figure 21. Accelerometer chain with mode 3 enabled. 37  
Figure 22. Gyroscope digital chain - mode 1 (UI/EIS) and mode 2. 38  
Figure 23. Gyroscope digital chain - mode 3 (OIS). 39  
Figure 24. LSM6DSV16X supports UI, enhanced EIS, and OIS processing simultaneously. 40  
Figure 25. Gyroscope enhanced EIS and UI block diagram. 40  
Figure 26. Auxiliary SPI full control. 42  
Figure 27. OIS Primary interface full control. 43  
Figure 28. LSM6DSV16X electrical connections in mode 1. 47  
Figure 29. Qvar external connections to pin 2, 3 (Qvar input). 47  
Figure 30. LSM6DSV16X electrical connections in mode 2. 48  
Figure 31. LSM6DSV16X electrical connections in mode 3 (auxiliary 3/4-wire SPI). 49  
Figure 32. Accelerometer block diagram. 73  
Figure 33. LGA-14L $2.5 \times 3.0 \times 0.86$ mm package outline and mechanical data. 175  
Figure 34. Carrier tape information for LGA-14 package. 176  
Figure 35. LGA-14 package orientation in carrier tape. 176  
Figure 36. Reel information for carrier tape of LGA-14 package. 177 

## IMPORTANT NOTICE – READ CAREFULLY

STMicroelectronics NV and its subsidiaries (“ST”) reserve the right to make changes, corrections, enhancements, modifications, and improvements to ST products and/or to this document at any time without notice. Purchasers should obtain the latest relevant information on ST products before placing orders. ST products are sold pursuant to ST’s terms and conditions of sale in place at the time of order acknowledgment. 

Purchasers are solely responsible for the choice, selection, and use of ST products and ST assumes no liability for application assistance or the design of purchasers’ products. 

No license, express or implied, to any intellectual property right is granted by ST herein. 

Resale of ST products with provisions different from the information set forth herein shall void any warranty granted by ST for such product. 

ST and the ST logo are trademarks of ST. For additional information about ST trademarks, refer to www.st.com/trademarks. All other product or service names are the property of their respective owners. 

Information in this document supersedes and replaces information previously supplied in any prior versions of this document 

© 2023 STMicroelectronics – All rights reserved 