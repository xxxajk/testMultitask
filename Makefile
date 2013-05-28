#
# These are set for a mega 1280 + quadram.
# If your board is a mega 2560 uncomment the following two lines
# BOARD = mega2560
# PROGRAMMER = wiring
# ...and then comment out the following two lines
BOARD = mega
PROGRAMMER = arduino

# set your Arduino tty port here
PORT = /dev/ttyUSB0

# Leave these alone.
EXTRA_FLAGS = -D _FS_TINY=0
EXTRA_FLAGS += -D _USE_LFN=1
EXTRA_FLAGS += -D USE_MULTIPLE_APP_API=16

# You should not need to change this, but I place it here if you want to play.
# These are the defaults for the optimization of the flash and ram
#OPT_FLAGS = -Os -fno-exceptions -ffunction-sections -fdata-sections -MMD

# The following are the libraries used.
LIB_DIRS =
LIB_DIRS += ../libraries/xmem

# And finally, the part that brings everything together for you.
include ../Arduino_Makefile_master/_Makefile.master
