Image -i ALGO_v1.5_R05W15_210514.elf -c monocular_lock_combine_1P5M.ini -o flash_download_file.bin
#del ck805_ddr.bin
#del ck805_dtcm.bin
#csky-elfabiv2-gdb.exe TX216_EVB_Bootldr.elf -x ck804_load.gdbinit
::del flash_download_file.bin

#pause