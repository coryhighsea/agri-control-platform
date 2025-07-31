SUMMARY = "Core control application for agricultural machinery"
DESCRIPTION = "Manages sensors, actuators, and network communication via MQTT."
LICENSE = "MIT"
# The path to the LICENSE file is now relative to the source directory (S)
LIC_FILES_CHKSUM = "file://LICENSE;md5=734a82b45bc7a0586a844b24d42cb9d4"

DEPENDS += "mosquitto"

# --- IMPORTANT CHANGE HERE ---
# Point to the application source code three levels up from the recipe's directory.
# (${THISDIR} is the directory of the recipe itself)
SRC_URI = "file://${THISDIR}/../../../../apps/machine-control-unit"

# Set the source directory 'S' to where the files are copied.
S = "${WORKDIR}"

inherit cmake

TARGET_LDFLAGS += "-lpthread"
