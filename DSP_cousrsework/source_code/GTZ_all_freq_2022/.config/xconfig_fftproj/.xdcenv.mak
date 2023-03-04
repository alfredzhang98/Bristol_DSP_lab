#
_XDCBUILDCOUNT = 
ifneq (,$(findstring path,$(_USEXDCENV_)))
override XDCPATH = C:/ti/ipc_3_00_02_26/packages;C:/ti/mathlib_c66x_3_0_2_0/packages;C:/ti/pdk_C6678_1_1_2_6/packages;C:/ti/bios_6_35_04_50/packages;C:/ti/uia_1_03_01_08/packages;C:/ti/syslib_3_00_00_03/packages;C:/ti/xdais_7_21_01_07/packages;C:/ti/xdais_7_21_01_07/examples;C:/ti/ccsv5/ccs_base;C:/ti/edma3_lld_02_11_09_08/packages;C:/ti/mcsdk_bios_3_00_01_12/demos;C:/Users/Scott/Dropbox/CCS5/FFTProj/.config
override XDCROOT = C:/ti/xdctools_3_25_03_72
override XDCBUILDCFG = ./config.bld
endif
ifneq (,$(findstring args,$(_USEXDCENV_)))
override XDCARGS = 
override XDCTARGETS = 
endif
#
ifeq (0,1)
PKGPATH = C:/ti/ipc_3_00_02_26/packages;C:/ti/mathlib_c66x_3_0_2_0/packages;C:/ti/pdk_C6678_1_1_2_6/packages;C:/ti/bios_6_35_04_50/packages;C:/ti/uia_1_03_01_08/packages;C:/ti/syslib_3_00_00_03/packages;C:/ti/xdais_7_21_01_07/packages;C:/ti/xdais_7_21_01_07/examples;C:/ti/ccsv5/ccs_base;C:/ti/edma3_lld_02_11_09_08/packages;C:/ti/mcsdk_bios_3_00_01_12/demos;C:/Users/Scott/Dropbox/CCS5/FFTProj/.config;C:/ti/xdctools_3_25_03_72/packages;..
HOSTOS = Windows
endif
