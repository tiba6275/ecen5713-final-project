#! /bin/sh

case "$1" in
    start)
        echo "load modules"
        modprobe rfcomm
        modprobe cmac
        modprobe algif_hash
        modprobe aes_arm_bs
        modprobe crypto_simd
        modprobe cryptd
        modprobe algif_skcipher
        modprobe af_alg
        modprobe bnep
        modprobe hci_uart
        modprobe btbcm
        modprobe bluetooth
        modprobe ecdh_generic
        modprobe ecc
        modprobe imx219
        modprobe 8021q
        modprobe garp
        modprobe stp
        modprobe llc
        modprobe joydev
        modprobe vc4
        modprobe brcmfmac
        modprobe snd_soc_hdmi_codec
        modprobe drm_display_handler
        modprobe cec
        modprobe drm_dma_helper
        modprobe brcmutil
        modprobe drm_kms_helper
        modprobe snd_soc_core
        modprobe sha256_generic
        modprobe cfg80211
        modprobe raspberrypi_hwmon
        modprobe i2c_mux_pinctrl
        modprobe snd_compress
        modprobe bcm2835_unicam
        modprobe i2c_mux
        modprobe snd_pcm_dmaengine
        modprobe syscopyarea
        modprobe sysfillrect
        modprobe sysimgblt
        modprobe fb_sys_fops
        modprobe v4l2_dv_timings
        modprobe rfkill
        modprobe v4l2_fwnode
        modprobe v4l2_async
        modprobe bcm2835_codec
        modprobe bcm2835_v4l2
        modprobe snd_bcm2835
        modprobe v4l2_mem2mem
        modprobe snd_pcm
        modprobe bcm2835_isp
        modprobe snd_timer
        modprobe videobuf2_vmalloc
        modprobe bcm2835_mmal_vchiq
        modprobe videobuf2_dma_contig
        modprobe videobuf2_memops
        modprobe i2c_bcm2835
        modprobe videobuf2_v4l2
        modprobe snd
        modprobe videobuf2_common
        modprobe vc_sm_cma
        modprobe videodev
        modprobe mc
        modprobe fixed
        modprobe uio_pdrv_genirq
        modprobe uio
        modprobe drm
        modprobe i2c_dev
        modprobe fuse
        modprobe drm_panel_orientation_quirks
        modprobe backlight
        modprobe ip_tables
        modprobe x_tables
        modprobe ipv6
        ;;
    stop)
        echo "Stopping"

        ;;
    *)
        echo "Usage: $0 {start|stop}"
        exit 1
        ;;
esac

exit 0

