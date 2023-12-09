#! /bin/sh

case "$1" in
    start)
        wpa_passphrase "Sacred Virus" "Pyngyp58#" > /etc/wpa_supplicant.conf
        wpa_supplicant -B -i wlan0 -c /etc/wpa_supplicant.conf
        ;;
    stop)
        ;;
    *)
        echo "Usage: $0 {start|stop}"
        exit 1
        ;;
esac

exit 0

