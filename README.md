# lab2B-part08
## TODO:

You can now actually measure the timings you modeled in the last lab. Add APDS9960 support to your sensor, then set your system up to capture the following timing info:

1. color packet delivered to PIO module
2. bit delivered to WS2812 (24x/packet)
3. full packet delivered to WS2812
4. brightness changed on APDS

Run this experiment in both dark and light room settings (record initial ambient brightness in each case). The Neopixel should start 'off' and the ADPS9960 should be initialized with your preferred sampling rate (you may want to try a few different rates). Run the experiment for at least 100 samples at brightness settings of 0%, 25%, 50%, 75%, 100% (making sure to give the ADPS reading enough time to 'settle' each time Neopixel is turned off).

Report the observed 'jitter' based on misalignment with the free-running PWM module on the WS2012.

## In order to reach these functions, we found something useful in the pico_example folder and we wrote these codes:
1. the main code [i2c_bus_scan.c](https://github.com/xcyxcyxcyxcy/lab2B-part08/blob/main/code/i2c_bus_scan.c)
2. the [pio_i2c.c](https://github.com/xcyxcyxcyxcy/lab2B-part08/blob/main/code/pio_i2c.c)

## Results:

a. screen: 
<div align=center><img width="500" height="350" src="https://github.com/xcyxcyxcyxcy/lab2B-part08/blob/main/proximity%20%26%20color.png"/></div>

b. color:
<div align=center><img width="500" height="350" src="https://github.com/xcyxcyxcyxcy/lab2B-part08/blob/main/proximity%20%26%20color.png"/></div>
<div align=center><img width="500" height="350" src="https://github.com/xcyxcyxcyxcy/lab2B-part08/blob/main/proximity%20%26%20color.png"/></div>
<div align=center><img width="500" height="350" src="https://github.com/xcyxcyxcyxcy/lab2B-part08/blob/main/proximity%20%26%20color.png"/></div>

