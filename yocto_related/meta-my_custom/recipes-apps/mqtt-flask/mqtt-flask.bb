SUMMARY = "MQTT broker Flask App"
DESCRIPTION = "A Flask-based MQTT Application on Raspberry Pi 4b for ESP32 nodes"
LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

# GitHub Repository Source
SRC_URI = "git://github.com/decryptec/rpi4-mqtt-esp32.git;protocol=https;branch=main"

SRCREV = "7d46e951ae3fae0f886eefe9530fb840efda4218"

S = "${WORKDIR}/git/source"

# Dependencies required for the Flask MQTT App
RDEPENDS:${PN} = "mosquitto python3 python3-flask python3-paho-mqtt"

# Install application files and systemd service
do_install() {
    install -d ${D}${libdir}/mqtt-flask
    install -m 0755 ${S}/app.py ${D}${libdir}/mqtt-flask/app.py

    install -d ${D}${libdir}/mqtt-flask/templates
    cp -r ${S}/templates/* ${D}${libdir}/mqtt-flask/templates/
}


# Ensure installed files are included in the package
FILES:${PN} += "${libdir}/mqtt-flask/app.py ${datadir}/mqtt-flask/templates/*"
