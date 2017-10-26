433Raspino
=============
#### Send reliable 433Mhz Signals from RPi to Power Outlets

## Intro

Sending 433Mhz Signals directly from a Raspberry Pi through commonly available [433Mhz Transmitters](https://www.amazon.com/Aukru-Wireless-Transmitter-Receiver-Raspberry/dp/B019SX6Y22/) has been proven quite unreliable.
This is mostly due to jitter introduced by the (non-realtime) Kernel on Raspberry Pi, which can get even worse under full load.
This solution offloads the transmission to an Arduino board connected to the Pi via USB and controlled through Serial.

By connecting the 433Mhz Transmitter to the Arduino a much higher precision is achieved. Commands are read via the Serial input and then passed along to [rc-switch](https://github.com/sui77/rc-switch) to handle the actual conversion and transmission.
With increased precision and less jitter, commands can be sent much faster than on the Raspberry Pi as less retransmissions are neccessary.

The sketch can be easily modified to make use of other APIs provided by rc-switch (as potentially needed for different power outlets with different chipsets).

## Use

Compile and load the Arduino Sketch onto an Arduino.  
Connect it to the Raspberry Pi.
Ensure that the user is part of the `dialout` group to access serial ports (`adduser user dialout`).
If the Arduino is using a different serial port other than `/dev/ttyAMC0`, the `sendscript` script needs to be modified accordingly.

The following arguments are passed to the script:
+ systemCode (usually the first few pins defining the group)
+ unitcode (e.g. A, B, C, D) and whether to switch the device off or on (0/1). The unitcode is mapped to monotonous increasing numbers starting with A=0, B=1...
+ device command (off=0, on=1)

`./sendscript.sh systemCode unitCode off/on`

### Example

```
./sendscript.sh11111 3 0
```