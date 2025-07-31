SUMMARY = "Core control application for agricultural machinery"
DESCRIPTION = "Manages sensors, actuators, and network communication via MQTT."
LICENSE = "MIT"
# The path to the LICENSE file is now relative to the source directory (S)
LIC_FILES_CHKSUM = "file://LICENSE;md5=b04d53957d471b392348b4334a2df854"

DEPENDS += "mosquitto"

# --- IMPORTANT CHANGE HERE ---
# Point to the application source code three levels up from the recipe's directory.
# (${THISDIR} is the directory of the recipe itself)
SRC_URI = "file://${THISDIR}/../../../../apps/machine-control-unit"

# Set the source directory 'S' to where the files are copied.
S = "${WORKDIR}/machine-control-unit"

inherit cmake

TARGET_LDFLAGS += "-lpthread"