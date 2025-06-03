PN = "flaskapp_systemd"

LICENSE = "MIT"
LIC_FILES_CHKSUM = "file://${COREBASE}/meta/files/common-licenses/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302"

SUMMARY = "Flask mqtt app run"
DESCRIPTION = "Runs mqtt-flask.service app using a systemd service"

inherit systemd

RDEPENDS:${PN}  = "python3-flask python3 python3-paho-mqtt"

SYSTEMD_AUTO_ENABLE = "enable"
SYSTEMD_SERVICE:${PN} = "mqtt-flask.service"

do_install() {
    install -d ${D}${bindir}
    
    install -d ${D}/${sysconfdir}/systemd/system
    install -m 0644 ${WORKDIR}/mqtt-flask.service ${D}/${sysconfdir}/systemd/system
}
