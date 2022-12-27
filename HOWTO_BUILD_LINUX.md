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
$ patch -p1 < EBTKS_FW/patches/ehci.cpp.patch
$ patch -p1 < EBTKS_FW/patches/HardwareSerial.cpp.patch
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

## Building on Unix with VSCode

### Prerequisites

Git and Python3 need to be installed on your system.  Use your distribution's package installer (e.g. apt, yum, dnf) to do this.

### Installing Visual Studio Code and PlatformIO

Instructions for installing Visual Studio Code on a number of different Linux distributions can be found [here](https://code.visualstudio.com/docs/setup/linux).  After installing, start the application by running the command `code` from a terminal.  (You may also be able to launch VSCode by clicking an icon on your desktop's Applications menu.)  Within the application, click on the "Extensions" icon on the left hand side (or type Ctrl+Shift+X) then type "PlatformIO" into the search box.  Once the PlatformIO extension appears, click on the "Install" button.  You will see various dialog boxes pop up as dependencies are downloaded and installed.  Once the process has finished, you may be asked to reload the extension.  If so, click on the "Reload Now" button.  After installing PlatformIO, exit the VSCode application.

### Downloading the EBTKS F/W Source

The EBTKS firmware source is located in a Git repository.  To clone the repository to directory EBTKW_FW in your home directory, enter the following commands:
```console
$ mkdir Documents/PlatformIO
$ mkdir Documents/PlatformIO/Projects
$ git clone https://github.com/Fliptron/T41_EBTKS_FW_1.0.git Documents/PlatformIO/Projects/EBTKS_FW
```
By default, the VSCode PlatformIO extension stores projects in a directory `~/Documents/PlatformIO/Projects`.  If you wish the code to be downloaded to a different location, modify the 2nd parameter of the "git clone" command accordingly.

Now we must download the various libraries and packages used by the source code.  Launch VSCode and click on the "Open Folder" button.  Navigate to the folder where you have downloaded the F/W source and answer "Yes" to the dialog box about trusting the authors of the code.  VSCode will detect automatically that the folder you have selected is a PlatformIO project and proceed to download all the libraries and packages required by the project.  This may take some time – wait until any spinning wheels at the bottom of the VSCode screen have disappeared and then exit VSCode.

### Applying Patches required by the EBTKS F/W

The EBTKS firmware requires some patches to be applied to the files downloaded in the previous step.  Patch files are provided in the "patches" folder of the project to automate this step.  To apply the patches, execute the following commands:
```console
$ patch -p1 < Documents/PlatformIO/Projects/EBTKS_FW/patches/usb.c.patch
$ patch -p1 < Documents/PlatformIO/Projects/EBTKS_FW/patches/ehci.c.patch
$ patch -p1 < Documents/PlatformIO/Projects/EBTKS_FW/patches/HardwareSerial.c.patch
$ patch -p1 < Documents/PlatformIO/Projects/EBTKS_FW/patches/imxrt1062_t41.ld.patch
$ cd Documents/PlatformIO/Projects/EBTKS_FW
$ patch -p1 < patches/SdFatConfig.h.patch
$ patch -p1 < patches/Base64.cpp.patch
```
If you have chosen a different directory in which to store the f/w source, modify the cd commands accordingly.

The final patch required is to rename the file `~/.platformio/packages/framework-arduinoteensy/libraries/Time/Time.h` to `~/.platformio/packages/framework-arduinoteensy/libraries/Time/Time.h___DISABLED` to prevent it being included during the compile process.
```console
$ mv ~/.platformio/packages/framework-arduinoteensy/libraries/Time/Time.h ~/.platformio/packages/framework-arduinoteensy/libraries/Time/Time.h___DISABLED
```

### Building the EBTKS F/W

We are now ready to build the EBTKS firmware.  Launch VSCode and click on the PlatformIO icon on the left hand side of the screen.  This should display a menu of Project Tasks.  Click on the "Build" task and, with luck, the project will be successfully compiled and built.  The resulting firmware is in file `~/Documents/PlatformIO/Projects/EBTKS_FW/.pio/build/teensy41/firmware.hex` and can be loaded onto the Teensy board on the EBTKS using the procedure described [here](http://www.fliptronics.com/EBTKS/Updating_the_EBTKS_Firmware.html#updating-the-ebtks-firmware).

### Possible Gotchas

If you have previously used VSCode and PlatformIO for Teensy code development, you may have multiple versions of the framework-arduinoteensy package in your `~/.platformio/packages` directory.  If your build is failing with compile errors, look for a directory `~/.platformio/packages/framework-arduinoteensy@1.153.0` and modify the patch files to patch the files in that directory.
