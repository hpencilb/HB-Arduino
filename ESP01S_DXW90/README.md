# ESP01S_DXW90

This is an update version of the [DS1302_DXW90](../DS1302_DXW90/README.md). Since the ESP01s can connect to the Internet, there is no need to have a local RTS module.

Connecting the DXW90 servo to HomeKit lets me be able to control it on my phone and setting up a NTP server on the ESP01s also lets the timer-set-off part still being functional.

> If there is no network in my dorm, the NTP timer will still do the work.
> If there is no electricity, well the whole MCU will be of no meaning, let alone hot water when I get back.

