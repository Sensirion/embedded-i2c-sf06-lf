# Sensirion I2C SF06-LF embedded Library

This document explains how to set up a sensor of the SF06-LF sensor family to run on a embedded device
using the provided code.

<center><img src="images/sensor_SLF3C_1300F.png" width="300px"></center>

Click [here](https://sensirion.com/products/product-categories/liquid-flow/
) to learn more about the Sensirion SF06-LF sensor family.



Not all sensors of this driver family support all measurements.
In case a measurement is not supported by all sensors, the products that
support it are listed in the API description.


## Supported sensor types

   - SLF3C-1300F

   - SLF3S-1300F

   - SLF3S-0600F

   - SLF3S-4000B

   - LD20-0600L

   - LD20-2600B
The following instructions and examples use a *SLF3C-1300F*.Click [here](https://sensirion.com/media/documents/F3931025/621F8CCE/Sensirion_Liquid_Flow_Meters_SLF3C-1300F_Datasheet.pdf
) to download the datasheet.


## Setup Guide

### Connecting the Sensor

Your sensor has 4 different signals that need to be connected to your board: SDA, VDD, GND, SCL.
Use the following pins to connect your SF06-LF:

<img src="images/SLF3x_Pinout.png" width="300px">

| *Pin* | *Cable Color* | *Name* | *Description*  | *Comments* |
|-------|---------------|:------:|----------------|------------|
| 1 |  |NC | Do not connect | 
| 2 | green |SDA | I2C: Serial data input / output | 
| 3 | red |VDD | Supply Voltage | 3.2 to 3.8V
| 4 | black |GND | Ground | 
| 5 | yellow |SCL | I2C: Serial clock input | 
| 6 |  |NC | Do not connect | 



The recommended voltage is 3.3V.

### Configure the code

In order to use the provided code we need to adjust two files according to your platform.

### Edit `sensirion_i2c_hal.c`

This file contains the implementation of the sensor communication, which
depends on your hardware platform. We provide function stubs for your
hardware's own implementation.
Sample implementations are available for some platforms:
[`sample-implementations`](sample-implementations). For Linux based platforms
like Raspberry Pi you can just replace the unimplemented HAL template with the
implementation in `sample-implementations/linux_user_space/`:

```
cp sample-implementations/linux_user_space/sensirion_i2c_hal.c ./
```

### Edit `sensirion_config.h`

Skip this part for Linux based platforms since everything is already setup for
this case.

Otherwise you need to check if the libraries `<stdint.h>` and `<stdlib.h>` are
provided by your toolchain, compiler or system. If you have no idea on how to
do that you can skip this step for now and come back when you get errors
related to these names when compiling the driver.
The features we use from those libraries are type definitions for integer sizes
from `<stdint.h>` and `NULL` from `<stdlib.h>`. If they are not available you
need to specify the following integer types yourself:

* `int64_t` = signed 64bit integer
* `uint64_t` = unsigned 64bit integer
* `int32_t` = signed 32bit integer
* `uint32_t` = unsigned 32bit integer
* `int16_t` = signed 16bit integer
* `uint16_t` = unsigned 16bit integer
* `int8_t` = signed 8bit integer
* `uint8_t` = unsigned 8bit integer

In addition to that you will need to specify `NULL`. For both we have a
detailed template where you just need to fill in your system specific values.

## Choose the i2c address to use with your product

The current code is configured to run with the default address 0x08. In case you would like to use
a different one you will need to change the I2C address in `./sf06_lf_i2c_example_usage`
You find the list of supported I2C-addresses in the header `sf06_lf_i2c.h`.


Now we are ready to compile and run the example usage for your sensor.

## Compile and Run

Pass the source `.c` and header `.h` files in this folder into your C compiler
and run the resulting binary. This step may vary, depending on your platform.
Here we demonstrate the procedure for Linux based platforms:

1. Open up a terminal.
2. Navigate to the directory where this README is located.
3. Run `make` (this compiles the example code into one executable binary).
4. Run the compiled executable with `./sf06_lf_i2c_example_usage`
5. Now you should see the first measurement values appear in your terminal. As
   a next step you can adjust the example usage file or write your own main
   function to use the sensor.

# Background

## Files

### sensirion\_i2c.[ch]

In these files you can find the implementation of the I2C protocol used by
Sensirion sensors. The functions in these files are used by the embedded driver
to build the correct frame out of data to be sent to the sensor or receive a
frame of data from the sensor and convert it back to data readable by your
machine. The functions in here calculate and check CRCs, reorder bytes for
different byte orders and build the correct formatted frame for your sensor.

### sensirion\_i2c\_hal.[ch]

These files contain the implementation of the hardware abstraction layer used
by Sensirion's I2C embedded drivers. This part of the code is specific to the
underlying hardware platform. This is an unimplemented template for the user to
implement. In the `sample-implementations/` folder we provide implementations
for the most common platforms.

### sensirion\_config.h

In this file we keep all the included libraries for our drivers and global
defines. Next to `sensirion_i2c_hal.c` *it's the only file you should need to
edit to get your driver working.*

### sensirion\_common.[ch]

In these files you can find some helper functions used by Sensirion's embedded
drivers. It mostly contains byte order conversions for different variable
types. These functions are also used by the UART embedded drivers therefore
they are kept in their own file.

## Contributing

**Contributions are welcome!**

We develop and test this driver using our company internal tools (version
control, continuous integration, code review etc.) and automatically
synchronize the master branch with GitHub. But this doesn't mean that we don't
respond to issues or don't accept pull requests on GitHub. In fact, you're very
welcome to open issues or create pull requests :)

This Sensirion library uses
[`clang-format`](https://releases.llvm.org/download.html) to standardize the
formatting of all our `.c` and `.h` files. Make sure your contributions are
formatted accordingly:

The `-i` flag will apply the format changes to the files listed.

```bash
clang-format -i *.c *.h
```

Note that differences from this formatting will result in a failed build until
they are fixed.


# License

See [LICENSE](LICENSE).