
target jtag jtag://127.0.0.1:1025
reset
lo

b updata_bootloader
#b flash_update_done
c
restore flash_download_file.bin binary 0x1400000
#restore firmware_moudleI_20210521.bin binary 0x1400000
b main.c:232
c


