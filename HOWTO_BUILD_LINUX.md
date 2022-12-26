# Building the EBTKS Firmware

The EBTKS firmware has been developed using the PlatformIO IDE.  This can be run within the Visual Studio Code editor or directly on a Unix command line.  Instructions for installing the requisite tools and building the firmware to produce a hex file which can be downloaded to the Teensy board on the EBTKS are provided below.

## Building on Unix – Command line method

### Prerequisites

Git and Python3 need to be installed on your system.  Use your distribution's package installer (e.g. apt, yum, dnf) to do this.

### Installing PlatformIO

When not using PlatformIO within a Visual Studio Code environment, it is installed using [this Python script](https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py).  Download and install it into your Python environment with these commands:
```console
$ wget https://raw.githubusercontent.com/platformio/platformio-core-installer/master/get-platformio.py -O ~/Downloads/get-platformio.py
$ python3 ~/Downloads/get-platformio.py
```
### Downloading the EBTKS F/W Source

The EBTKS firmware source is located in a Git repository.  To clone the repository to directory EBTKW_FW in your home directory, enter the following command:
```console
$ git clone https://github.com/Fliptron/T41_EBTKS_FW_1.0.git EBTKS_FW
```
If you wish the code to be downloaded to a different location, modify the 2nd parameter of the "git clone" command accordingly.

### Dummy F/W Build

The EBTKS F/W will not build cleanly without applying some patches to certain files in the Teensy4.1 libraries and packages.  In order to download these, we perform a build of the EBTKS F/W project, fully expecting it to fail at this stage.  Execute the following commands:
```console
$ cd EBTKS_FW
$ ~/.platformio/penv/bin/pio run
```
and ignore the errors which result.  (Of course, if you have downloaded the source to a different directory, cd to that.)

### Applying Patches required by the EBTKS F/W

The EBTKS firmware requires some patches to be applied to the files downloaded in the previous step.  Patch files are provided in the "patches" folder of the project to automate this step.  To apply the patches, execute the following commands:
```console
$ pushd ~
$ patch -p1 < EBTKS_FW/patches/usb.c.patch
$ patch -p1 < EBTKS_FW/patches/ehci.c.patch
$ patch -p1 < EBTKS_FW/patches/HardwareSerial.c.patch
$ patch -p1 < EBTKS_FW/patches/imxrt1062_t41.ld.patch
$ popd
$ patch -p1 < patches/SdFatConfig.h.patch
$ patch -p1 < patches/Base64.cpp.patch
```
If you have chosen a different directory in which to store the f/w source, modify the cd commands and the path to the patch files in the first four patch commands accordingly.

The final patch required is to rename the file `~/.platformio/packages/framework-arduinoteensy/libraries/Time/Time.h` to `~/.platformio/packages/framework-arduinoteensy/libraries/Time/Time.h___DISABLED` to prevent it being included during the compile process.
```console
$ mv ~/.platformio/packages/framework-arduinoteensy/libraries/Time/Time.h ~/.platformio/packages/framework-arduinoteensy/libraries/Time/Time.h___DISABLED
```

### Building the EBTKS F/W

We are now ready to build the EBTKS firmware.  Rerun
```console
$ ~/.platformio/penv/bin/pio run
```
and, with luck, the project will be successfully compiled and built.  The resulting firmware is in file `.pio/build/teensy41/firmware.hex` and can be loaded onto the Teensy board on the EBTKS using the procedure described [here](http://www.fliptronics.com/EBTKS/Updating_the_EBTKS_Firmware.html#updating-the-ebtks-firmware).

### Possible Gotchas

If you have previously used VSCode and PlatformIO for Teensy code development, you may have multiple versions of the framework-arduinoteensy package in your `~/.platformio/packages` directory.  If your build is failing with compile errors, look for a directory `~/.platformio/packages/framework-arduinoteensy@1.153.0` and modify the patch files to patch the files in that directory.