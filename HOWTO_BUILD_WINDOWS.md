# Building the EBTKS Firmware

The EBTKS firmware has been developed using the PlatformIO IDE.  This can be run within the Visual Studio Code editor or directly on a Unix command line.  Instructions for installing the requisite tools and building the firmware to produce a hex file which can be downloaded to the Teensy board on the EBTKS are provided below.

## Building on Windows

### Prerequisites

PlaformIO requires Git and Python to be installed on your system.  (Although it downloads its own copy of Python during the build process, you may get an ERR_INVALID_ARG_TYPE message if you haven't already installed Python on your system.)

Git for Windows can be download from [here](https://git-scm.com/download/win).  The installation script presents you with a bewildering array of options – just select the defaults unless you really know what you are doing.

Python can be downloaded from [here](https://www.python.org/downloads/windows/).  When installing, tick the checkbox to select the option of including Python in your PATH variable.  If you are running on Windows 7, you will not be able to install Python 3.9 or later.  Instead, install Python 3.8.  The most recent release of that version for which a Windows installer is available is [3.8.10](https://www.python.org/ftp/python/3.8.10/python-3.8.10-amd64.exe).  

### Installing Visual Studio Code and PlatformIO

Visual Studio Code can be downloaded from [here](https://code.visualstudio.com/download).  After installing and opening the application, click on the "Extensions" icon on the left hand side (or type Ctrl+Shift+X) then type "PlatformIO" into the search box.  Once the PlatformIO IDE extension appears, click on the "Install" button.  You may see various dialog boxes pop up as dependencies (such as Python) are downloaded and installed.  Once the process has finished, you may be asked to reload the extension.  If so, click on the "Reload Now" button.  After installing PlatformIO, exit the VSCode application.

### Downloading the EBTKS F/W Source

The EBTKS firmware source is located in a Git repository.  Since we have already installed Git for Windows, we can use its GUI to copy the source to our local machine.  Launch the "Git GUI" application and click on "Clone an existing repository".  Fill in the dialog box as follows:

- Source Location: `https://github.com/Fliptron/T41_EBTKS_FW_1.0.git`
- Target Directory: Enter the location you would like to use as your project space.  The patch instructions later in this document assume the code will be download to a directory called `PlatformIO\Projects\EBTKS_FW` created within your "My Documents" directory.  If you prefer an alternative location, modify the patch commands accordingly.  Note that the target directory entered in the dialog box must not already exist otherwise the GUI will respond with an error.
- Clone Type: Leave options at default values

Click on the "Clone" button and exit the GUI after the code has been populated.

Now we must download the various libraries and packages used by the source code.  Launch VSCode and click on the "Open Folder" button.  Navigate to the folder where you have downloaded the F/W source and answer "Yes" to the dialog box about trusting the authors of the code.  VSCode will detect automatically that the folder you have selected is a PlatformIO project and proceed to download all the libraries and packages required by the project.  This may take some time – wait until any spinning wheels at the bottom of the VSCode screen have disappeared and then exit VSCode.

### Applying Patches required by the EBTKS F/W

The EBTKS firmware requires some patches to be applied to the files downloaded by VSCode in the previous step.  Patch files are provided in the "patches" folder of the project to automate this step.  They are written in the "unified diff" format popular on Unix platforms.  The Git for Windows software includes a utility than can read and apply patch files written in this format.

To apply the patches, open a command line interpreter (e.g. cmd.exe) and run the following:
```console
"c:\Program Files\Git\usr\bin\patch.exe" %userprofile%\.platformio\packages\framework-arduinoteensy\cores\teensy4\usb.c %userprofile%\Documents\PlatformIO\Projects\EBTKS_FW\patches\usb.c.patch
"c:\Program Files\Git\usr\bin\patch.exe" %userprofile%\.platformio\packages\framework-arduinoteensy\cores\teensy4\HardwareSerial.cpp %userprofile%\Documents\PlatformIO\Projects\EBTKS_FW\patches\HardwareSerial.cpp.patch
"c:\Program Files\Git\usr\bin\patch.exe" %userprofile%\.platformio\packages\framework-arduinoteensy\cores\teensy4\imxrt1062_t41.ld %userprofile%\Documents\PlatformIO\Projects\EBTKS_FW\patches\imxrt1062_t41.ld.patch
"c:\Program Files\Git\usr\bin\patch.exe" %userprofile%\.platformio\packages\framework-arduinoteensy\libraries\USBHost_t36\ehci.cpp %userprofile%\Documents\PlatformIO\Projects\EBTKS_FW\patches\ehci.cpp.patch
"c:\Program Files\Git\usr\bin\patch.exe" %userprofile%\Documents\PlatformIO\Projects\EBTKS_FW\.pio\libdeps\teensy41\SdFat\src\SdFatConfig.h %userprofile%\Documents\PlatformIO\Projects\EBTKS_FW\patches\SdFatConfig.h.patch
"c:\Program Files\Git\usr\bin\patch.exe" %userprofile%\Documents\PlatformIO\Projects\EBTKS_FW\.pio\libdeps\teensy41\Base64\src\Base64.cpp %userprofile%\Documents\PlatformIO\Projects\EBTKS_FW\patches\Base64.cpp.patch
```
Of course, if you have chosen a different directory in which to store the f/w source, modify the path names accordingly.

The final patch required is to rename the file `%userprofile%\.platformio\packages\framework-arduinoteensy\libraries\Time\Time.h` to `%userprofile%\.platformio\packages\framework-arduinoteensy\libraries\Time\Time.h___DISABLED` to prevent it being included during the compile process.

### Building the EBTKS F/W

We are now ready to build the EBTKS firmware.  Launch VSCode and click on the PlatformIO icon on the left hand side of the screen.  
This should display a menu of Project Tasks.  Click on the "Build" task and, with luck, the project will be successfully compiled and built.  The resulting firmware is in file `%userprofile%\Documents\PlatformIO\Projects\EBTKS_FW\.pio\build\teensy41\firmware.hex` and can be loaded onto the Teensy board on the EBTKS using the procedure described [here](http://www.fliptronics.com/EBTKS/Updating_the_EBTKS_Firmware.html#updating-the-ebtks-firmware).

### Possible Gotchas

If you have previously used VSCode and PlatformIO for Teensy code development, you may have multiple versions of the framework-arduinoteensy package in your `%userprofile%\.platformio\packages` directory.  If your build is failing with compile errors, look for a directory `%userprofile%\.platformio\packages\framework-arduinoteensy@1.153.0` and modify the patch commands to patch the files in that directory.

If your anti-virus software protects your "My Documents" folder against suspicious modification (e.g. by a ransomware encrypter), you may get "access denied" errors during the build.  Either add your EBTKS_FW directory to the anti-virus software's exception list or move the directory somewhere else in your filesystem.