from os import getcwd, rename
from os.path import join, isfile
import subprocess

Import("env")

# So that we can run the same patch command in either Windows or Linux,
# we use a program patch.py from here: https://github.com/techtonik/python-patch
# Our copy is stored in the 'patches' subdirectory.
PATCH_PROG = join(getcwd(), "patches", "patch.py")

# Directories containing the files we want to patch
FRAMEWORK_DIR = env.PioPlatform().get_package_dir("framework-arduinoteensy")
TEENSY4_DIR = join(FRAMEWORK_DIR, "cores", "teensy4")
USBHOST_DIR = join(FRAMEWORK_DIR, "libraries", "USBHost_t36")
TIME_DIR    = join(FRAMEWORK_DIR, "libraries", "Time")
SDFAT_DIR   = join(FRAMEWORK_DIR, "libraries", "SdFat", "src")
#BASE64_DIR  = join(getcwd(), ".pio", "libdeps", "teensy41", "Base64", "src")

def _touch(path):
    with open(path, "w") as fp:
        fp.write("")

# For each file, only patch if not already done
# Each patch file requires us to cd to the directory containing the file to be
# patched before running patch.py.  We use subprocess.Popen() to do this.

# 1st patch - .platformio\packages\framework-arduinoteensy\cores\teensy4\usb.c
file_to_patch = join(TEENSY4_DIR, "usb.c")
patch_file    = join(getcwd(), "patches", "usb.c.patch")
doneflag_file = join(TEENSY4_DIR, "usb.c.patch-done")
if not isfile(doneflag_file):
    assert isfile(file_to_patch) and isfile(patch_file)
    p = subprocess.Popen(["python", PATCH_PROG, patch_file], cwd=TEENSY4_DIR)
    p.wait()
    env.Execute(lambda *args, **kwargs: _touch(doneflag_file))

# 2nd patch - .platformio\packages\framework-arduinoteensy\cores\teensy4\HardwareSerial.cpp
file_to_patch = join(TEENSY4_DIR, "HardwareSerial.cpp")
patch_file    = join(getcwd(), "patches", "HardwareSerial.cpp.patch")
doneflag_file = join(TEENSY4_DIR, "HardwareSerial.cpp.patch-done")
if not isfile(doneflag_file):
    assert isfile(file_to_patch) and isfile(patch_file)
    p = subprocess.Popen(["python", PATCH_PROG, patch_file], cwd=TEENSY4_DIR)
    p.wait()
    env.Execute(lambda *args, **kwargs: _touch(doneflag_file))

# 3rd patch - .platformio\packages\framework-arduinoteensy\cores\teensy4\imxrt1062_t41.ld
file_to_patch = join(TEENSY4_DIR, "imxrt1062_t41.ld")
patch_file    = join(getcwd(), "patches", "imxrt1062_t41.ld.patch")
doneflag_file = join(TEENSY4_DIR, "imxrt1062_t41.ld.patch-done")
if not isfile(doneflag_file):
    assert isfile(file_to_patch) and isfile(patch_file)
    p = subprocess.Popen(["python", PATCH_PROG, patch_file], cwd=TEENSY4_DIR)
    p.wait()
    env.Execute(lambda *args, **kwargs: _touch(doneflag_file))

# 4th patch - .platformio\packages\framework-arduinoteensy\libraries\USBHost_t36\ehci.cpp
file_to_patch = join(USBHOST_DIR, "ehci.cpp")
patch_file    = join(getcwd(), "patches", "ehci.cpp.patch")
doneflag_file = join(USBHOST_DIR, "ehci.cpp.patch-done")
if not isfile(doneflag_file):
    assert isfile(file_to_patch) and isfile(patch_file)
    p = subprocess.Popen(["python", PATCH_PROG, patch_file], cwd=USBHOST_DIR)
    p.wait()
    env.Execute(lambda *args, **kwargs: _touch(doneflag_file))

# 5th patch - .platformio\packages\framework-arduinoteensy\libraries\SdFat\src\SdFatConfig.h
file_to_patch = join(SDFAT_DIR, "SdFatConfig.h")
patch_file    = join(getcwd(), "patches", "SdFatConfig.h.patch")
doneflag_file = join(SDFAT_DIR, "SdFatConfig.h.patch-done")
if not isfile(doneflag_file):
    assert isfile(file_to_patch) and isfile(patch_file)
    p = subprocess.Popen(["python", PATCH_PROG, patch_file], cwd=SDFAT_DIR)
    p.wait()
    env.Execute(lambda *args, **kwargs: _touch(doneflag_file))
