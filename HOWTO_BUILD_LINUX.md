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

### Building the EBTKS F/W

We are now ready to build the EBTKS firmware.  Change to the directory where you have cloned the Git repository and run the PlatformIO make process:
```console
$ cd EBTKS_FW
$ ~/.platformio/penv/bin/pio run
```
With luck, the project will be successfully compiled and built.  The resulting firmware is in file `.pio/build/teensy41/firmware.hex` and can be loaded onto the Teensy board on the EBTKS using the procedure described [here](http://www.fliptronics.com/EBTKS/Updating_the_EBTKS_Firmware.html#updating-the-ebtks-firmware).

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

### Building the EBTKS F/W

We are now ready to build the EBTKS firmware.  Launch VSCode and click on the "Open Folder" button.  Navigate to the folder where you have downloaded the F/W source and answer "Yes" to the dialog box about trusting the authors of the code.  VSCode will detect automatically that the folder you have selected is a PlatformIO project and proceed to download all the libraries and packages required by the project.  This may take some time – wait until any spinning wheels at the bottom of the VSCode screen have disappeared.  Now click on the PlatformIO icon on the left hand side of the screen.  This should display a menu of Project Tasks.  Click on the "Build" task and, with luck, the project will be successfully compiled and built.  The resulting firmware is in file `~/Documents/PlatformIO/Projects/EBTKS_FW/.pio/build/teensy41/firmware.hex` and can be loaded onto the Teensy board on the EBTKS using the procedure described [here](http://www.fliptronics.com/EBTKS/Updating_the_EBTKS_Firmware.html#updating-the-ebtks-firmware).

### Possible Gotchas

If you have previously used VSCode and PlatformIO for Teensy code development, you may have multiple versions of the framework-arduinoteensy package in your `~/.platformio/packages` directory.  If your build is failing with compile errors, look for a directory `~/.platformio/packages/framework-arduinoteensy@1.153.0` and modify the patch files to patch the files in that directory.
