#
# These are set for a mega 1280 + quadram.
# If your board is a mega 2560 uncomment the following two lines
#BOARD = mega2560
#PROGRAMMER = wiring
#GCS = -Wl,--gc-sections
# ...and then comment out the following two lines
BOARD = teensypp2

# set your Arduino tty port here
#PORT = /dev/ttyUSB0
PORT = /dev/ttyACM0

# You should not need to change this, but I place it here if you want to play.
# These are the defaults for the optimization of the flash and ram
#OPT_FLAGS = -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD

EXTRA_FLAGS = -D USE_MULTIPLE_APP_API=16

# And finally, the part that brings everything together for you.
include ../Arduino_Makefile_master/_Makefile.master
